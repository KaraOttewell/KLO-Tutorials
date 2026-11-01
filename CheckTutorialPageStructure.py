r"""
CheckTutorialPageStructure.py

Purpose:
    Check the structure of a tutorial page (any of the courses' index.html,
    or another page such as vms_course\rwast.html) before publishing it.

    Reports:
      - unbalanced tags (an end tag that doesn't match the open element, or
        an element never closed),
      - in-page links (#name) with no element of that id,
      - duplicate ids,
      - relative links (to another page, the zip, a picture or the theme
        script) whose target file does not exist on disk. Because the
        tutorials link to ../../KLO-Software, that check needs the
        KLO-Software repository checked out beside this one.

    It prints only the problems it finds, then a one-line summary, so a page
    with nothing wrong gives just the summary. External (http/https) links
    are not fetched; vms_course\CheckVmsPageLinksAndIsbns.py does that for the
    VMS pages.

Usage (cmd, from this KLO-Tutorials folder):
    python -I CheckTutorialPageStructure.py <page>

Example:
    python -I CheckTutorialPageStructure.py vms_course\index.html
"""
import os
import re
import sys
from html.parser import HTMLParser

# Elements that never have an end tag
VOID_ELEMENTS = {'meta', 'br', 'img', 'hr', 'link', 'input'}


class StructureChecker(HTMLParser):
    def __init__(self):
        super().__init__()
        self.open_tags = []
        self.problems = []
        self.ids = []
        self.links = []

    def handle_starttag(self, tag, attributes):
        attributes = dict(attributes)
        if 'id' in attributes:
            self.ids.append(attributes['id'])
        if tag == 'a' and 'href' in attributes:
            self.links.append(attributes['href'])
        if tag in ('script', 'img') and 'src' in attributes:
            self.links.append(attributes['src'])
        if tag not in VOID_ELEMENTS:
            self.open_tags.append((tag, self.getpos()[0]))

    def handle_endtag(self, tag):
        if tag in VOID_ELEMENTS:
            return
        if not self.open_tags or self.open_tags[-1][0] != tag:
            self.problems.append('line %d: </%s> but open is %s' % (self.getpos()[0], tag, self.open_tags[-1:] or None))
            # Recover by popping back to the matching open tag, if there is one,
            # so one mistake doesn't cascade into a report on every later tag
            for index in range(len(self.open_tags) - 1, -1, -1):
                if self.open_tags[index][0] == tag:
                    del self.open_tags[index:]
                    break
        else:
            self.open_tags.pop()


def main():
    if len(sys.argv) != 2:
        sys.exit('usage: python -I CheckTutorialPageStructure.py <page>')
    page_path = sys.argv[1]
    with open(page_path, encoding='utf-8') as page_file:
        text = page_file.read()
    checker = StructureChecker()
    checker.feed(text)
    for problem in checker.problems:
        print('TAG', problem)
    for tag, line in checker.open_tags:
        print('UNCLOSED <%s> from line %d' % (tag, line))
    ids = set(checker.ids)
    for duplicate in sorted({name for name in checker.ids if checker.ids.count(name) > 1}):
        print('DUPLICATE id', duplicate)
    folder = os.path.dirname(os.path.abspath(page_path))
    for link in checker.links:
        if link.startswith('#'):
            if link[1:] not in ids:
                print('MISSING anchor', link)
        elif not re.match(r'^[a-z]+:', link):
            target = os.path.normpath(os.path.join(folder, link.split('#')[0]))
            if link.endswith('/'):
                target = os.path.join(target, 'index.html')
            if not os.path.exists(target):
                print('MISSING file', link)
    print('checked %s: %d ids, %d links' % (page_path, len(ids), len(checker.links)))


if __name__ == '__main__':
    main()
