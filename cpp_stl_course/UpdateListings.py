r"""
UpdateListings.py

Purpose:
    Keep the program listings and sample outputs in index.html identical to
    the example files and to what the programs really print.

    index.html marks each listing with a comment followed by a <pre> block:

        <!-- listing example_1_2.cpp -->
        <pre>...</pre>

    and each sample output with:

        <!-- output example_2_1 -->
        <pre class="output">...</pre>

    For a listing, the <pre> block is replaced by the example file's text
    from its "---- title ----" line on (the copyright header above that line
    stays out of the page), HTML-escaped and coloured as C or C++. A .dat
    file is shown whole and uncoloured.

    With --outputs, each output block is replaced by what the built program
    (examples\bin\x64\Release\<name>.exe) prints when run from the examples
    folder, with the arguments listed in PROGRAM_ARGUMENTS. Build the Release
    x64 configuration first. Without --outputs, output blocks are left alone.

    The page is rewritten only if something changed, keeping its UTF-8
    encoding and CRLF line endings. Example files are Windows-1252.

Usage (cmd, from this cpp_stl_course folder):
    python -I UpdateListings.py
    python -I UpdateListings.py --outputs
"""

import html
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
PAGE_PATH = os.path.join(HERE, 'index.html')
EXAMPLES_FOLDER = os.path.join(HERE, 'examples')
PROGRAMS_FOLDER = os.path.join(EXAMPLES_FOLDER, 'bin', 'x64', 'Release')

# Command line arguments for programs whose sample output needs some
PROGRAM_ARGUMENTS = {'example_5_2': ['me*c^2']}

# The page is matched with LF line endings (see main)
LISTING_PATTERN = re.compile(r'(<!-- listing (\S+) -->\n)<pre[^>]*>.*?</pre>', re.DOTALL)
OUTPUT_PATTERN = re.compile(r'(<!-- output (\S+) -->\n)<pre class="output">.*?</pre>', re.DOTALL)
TITLE_LINE = re.compile(r'^(/\*----|// ----)', re.MULTILINE)


def listing_block(file_name):
    path = os.path.join(EXAMPLES_FOLDER, file_name)
    if not os.path.exists(path):
        sys.exit('refusing: %s is missing' % file_name)
    with open(path, 'r', encoding='cp1252', newline='') as source_file:
        text = source_file.read().replace('\r\n', '\n')
    if file_name.endswith('.dat'):
        return '<pre>%s</pre>' % html.escape(text.rstrip('\n'), quote=False)
    title = TITLE_LINE.search(text)
    if not title:
        sys.exit('refusing: %s has no "----" title line' % file_name)
    css_class = 'c-code' if file_name.endswith('.c') else 'cplusplus'
    body = html.escape(text[title.start():].rstrip('\n'), quote=False)
    return '<pre><span class="%s">%s</span></pre>' % (css_class, body)


def output_block(program_name):
    program = os.path.join(PROGRAMS_FOLDER, program_name + '.exe')
    if not os.path.exists(program):
        sys.exit('refusing: %s is not built (build Release|x64 first)' % program)
    result = subprocess.run([program] + PROGRAM_ARGUMENTS.get(program_name, []),
                            cwd=EXAMPLES_FOLDER, stdin=subprocess.DEVNULL,
                            capture_output=True, timeout=30)
    text = result.stdout.decode('cp1252').replace('\r\n', '\n').rstrip('\n')
    return '<pre class="output">%s</pre>' % html.escape(text, quote=False)


def main():
    update_outputs = '--outputs' in sys.argv[1:]
    with open(PAGE_PATH, 'r', encoding='utf-8', newline='') as page_file:
        original = page_file.read()

    # Work in LF internally so the blocks are built the same way every time
    page = original.replace('\r\n', '\n')

    listing_count = len(LISTING_PATTERN.findall(page))
    page = LISTING_PATTERN.sub(lambda match: match.group(1) + listing_block(match.group(2)), page)
    output_count = len(OUTPUT_PATTERN.findall(page))
    if update_outputs:
        page = OUTPUT_PATTERN.sub(lambda match: match.group(1) + output_block(match.group(2)), page)

    updated = page.replace('\n', '\r\n')
    if updated == original:
        print('index.html unchanged: %d listings, %d outputs%s'
              % (listing_count, output_count, '' if update_outputs else ' (outputs not checked)'))
        return
    with open(PAGE_PATH, 'w', encoding='utf-8', newline='') as page_file:
        page_file.write(updated)
    print('index.html updated: %d listings, %d outputs%s'
          % (listing_count, output_count, '' if update_outputs else ' (outputs left alone)'))


if __name__ == '__main__':
    main()
