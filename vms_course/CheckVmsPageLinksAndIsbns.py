r"""
CheckVmsPageLinksAndIsbns.py

Purpose:
    Check the external links and ISBNs in the VMS course's pages (every .html
    file beside this script: index.html and rwast.html).

      1. Fetches every external (http/https) link once and prints its HTTP
         status. Amazon links are skipped, because Amazon answers automated
         requests with errors whatever the address. Some sites refuse or
         time out for Python but are fine in a browser (when last checked,
         PuTTY, Goatley, Process Software and the VSI forum), so check any
         failure in a browser before changing the page.
      2. Checks the check digit of every ISBN-10 written in the pages, and of
         every ISBN in an Amazon link, so a mistyped ISBN shows up as BAD.
      3. Reports external links that don't open in a new window
         (target="_blank"), which the courses' reference links all do.

Usage (cmd, from this vms_course folder):
    python -I CheckVmsPageLinksAndIsbns.py
"""
import glob
import os
import re
import urllib.error
import urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))


def isbn10_is_valid(isbn):
    digits = isbn.replace('-', '').upper()
    if not re.fullmatch(r'\d{9}[\dX]', digits):
        return False
    # Weights 10 down to 1; a valid ISBN-10's weighted sum is a multiple of 11
    total = sum((10 - position) * (10 if character == 'X' else int(character))
                for position, character in enumerate(digits))
    return total % 11 == 0


def status_of(url):
    request = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0 (link check)'})
    try:
        with urllib.request.urlopen(request, timeout=25) as response:
            return str(response.status)
    except urllib.error.HTTPError as error:
        return str(error.code)
    except Exception as error:
        return 'ERR %s' % type(error).__name__


def main():
    anchors = []
    text = ''
    for page in sorted(glob.glob(os.path.join(HERE, '*.html'))):
        with open(page, encoding='utf-8') as page_file:
            page_text = page_file.read()
        text += page_text
        for url, rest in re.findall(r'<a href="(https?://[^"]+)"([^>]*)>', page_text):
            anchors.append(url)
            if 'target="_blank"' not in rest:
                print('NOT NEW WINDOW %s in %s' % (url, os.path.basename(page)))

    for url in sorted(set(anchors)):
        if 'amazon.com' not in url:
            print(status_of(url), url)

    written = re.findall(r'ISBN (\d[\d-]{8,}[\dX])', text)
    linked = re.findall(r'ISBN=(\w{10})/', text)
    for isbn in written + linked:
        print('ISBN %-15s %s' % (isbn, 'ok' if isbn10_is_valid(isbn) else 'BAD CHECK DIGIT'))


if __name__ == '__main__':
    main()
