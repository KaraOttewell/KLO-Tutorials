r"""
UpdateListings.py

Purpose:
    Keep the listings of the example files in index.html (the VMS course
    page) identical to the files in the examples folder. This is the VMS
    course's copy of the STL course's script of the same name, without the
    sample-output part: the VMS examples can't be run here, so their sample
    outputs in the page are kept by hand.

    index.html marks each listing with a comment followed by a <pre> block:

        <!-- listing sdeb.for -->
        <pre>...</pre>

    The <pre> block is replaced by the example file's text from its
    "---- title ----" line on (the copyright header above that line stays
    out of the page), HTML-escaped and coloured as Fortran (.for) or DCL
    (.com). The title line starts with "C----" in Fortran and "$! ----" in
    DCL.

    The page is rewritten only if something changed, with UTF-8 encoding and
    CRLF line endings. Example files are plain ASCII with CRLF line endings.

Usage (cmd, from this vms_course folder):
    python -I UpdateListings.py
"""

import html
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
PAGE_PATH = os.path.join(HERE, 'index.html')
EXAMPLES_FOLDER = os.path.join(HERE, 'examples')

# The colour class for each kind of example file
CSS_CLASS_FOR_TYPE = {'.for': 'fortran', '.com': 'dcl'}

# The page is matched with LF line endings (see main)
LISTING_PATTERN = re.compile(r'(<!-- listing (\S+) -->\n)<pre[^>]*>.*?</pre>', re.DOTALL)
TITLE_LINE = re.compile(r'^(C----|\$! ----)', re.MULTILINE)


def listing_block(file_name):
    path = os.path.join(EXAMPLES_FOLDER, file_name)
    if not os.path.exists(path):
        sys.exit('refusing: %s is missing' % file_name)
    css_class = CSS_CLASS_FOR_TYPE.get(os.path.splitext(file_name)[1].lower())
    if css_class is None:
        sys.exit('refusing: no colour is defined for %s' % file_name)
    with open(path, 'r', encoding='ascii', newline='') as example_file:
        text = example_file.read().replace('\r\n', '\n')
    title = TITLE_LINE.search(text)
    if not title:
        sys.exit('refusing: %s has no "----" title line' % file_name)
    body = html.escape(text[title.start():].rstrip('\n'), quote=False)
    return '<pre><span class="%s">%s</span></pre>' % (css_class, body)


def main():
    with open(PAGE_PATH, 'r', encoding='utf-8', newline='') as page_file:
        original = page_file.read()

    # Work in LF internally, whatever the page's line endings were
    page = original.replace('\r\n', '\n')
    listing_count = len(LISTING_PATTERN.findall(page))
    page = LISTING_PATTERN.sub(lambda match: match.group(1) + listing_block(match.group(2)), page)

    updated = page.replace('\n', '\r\n')
    if updated == original:
        print('index.html unchanged: %d listings' % listing_count)
        return
    with open(PAGE_PATH, 'w', encoding='utf-8', newline='') as page_file:
        page_file.write(updated)
    print('index.html updated: %d listings' % listing_count)


if __name__ == '__main__':
    main()
