r"""
MakeExamplesZip.py

Purpose:
    Build KarasCTutorial.zip, the download index.html (the course page) links
    to, from the
    examples folder beside this script. Only the files needed to build the
    examples go in: the C sources and headers, make.com for VMS, the Visual
    Studio solution and one project per example. Anything Visual Studio
    creates when it builds (bin, obj, .vs, *.user) or a program writes when it
    runs (fileio's MYDATA.DAT) is left out, because only the listed file types
    are ever added.

    Everything goes under a top-level KarasCTutorial folder in the zip. Each
    file is flagged as text inside the zip, so "unzip -a" (as the course
    tells VMS users to type) converts the line endings for the system it is
    unpacked on.

    Note: index.html also offers a detached, ASCII-armoured PGP signature,
    KarasCTutorial.zip.asc. Rebuilding the zip invalidates the old signature,
    so sign the new zip again before publishing it.

Usage (cmd, from this c_course folder):
    python -I MakeExamplesZip.py
"""

import os
import sys
import zipfile

HERE = os.path.dirname(os.path.abspath(__file__))
EXAMPLES_FOLDER = os.path.join(HERE, 'examples')
ZIP_PATH = os.path.join(HERE, 'KarasCTutorial.zip')
TOP_FOLDER = 'KarasCTutorial'

# File types needed to build the examples, in the examples folder itself...
TOP_LEVEL_TYPES = {'.c', '.h', '.com', '.sln'}
# ...and in each project subfolder.
PROJECT_TYPES = {'.vcxproj'}
GENERATED_FOLDERS = {'bin', 'obj', '.vs'}


def files_to_zip():
    chosen = []
    for entry in sorted(os.listdir(EXAMPLES_FOLDER), key=str.lower):
        path = os.path.join(EXAMPLES_FOLDER, entry)
        if os.path.isfile(path) and os.path.splitext(entry)[1].lower() in TOP_LEVEL_TYPES:
            chosen.append(entry)
        elif os.path.isdir(path) and entry not in GENERATED_FOLDERS:
            for project_file in sorted(os.listdir(path), key=str.lower):
                if os.path.splitext(project_file)[1].lower() in PROJECT_TYPES:
                    chosen.append(entry + '/' + project_file)
    return chosen


def main():
    chosen = files_to_zip()
    if not chosen:
        sys.exit('refusing: found nothing to zip in %s' % EXAMPLES_FOLDER)
    with zipfile.ZipFile(ZIP_PATH, 'w', compression=zipfile.ZIP_DEFLATED, compresslevel=9) as archive:
        for relative_path in chosen:
            full_path = os.path.join(EXAMPLES_FOLDER, *relative_path.split('/'))
            info = zipfile.ZipInfo.from_file(full_path, TOP_FOLDER + '/' + relative_path)
            info.compress_type = zipfile.ZIP_DEFLATED
            info.internal_attr = 1   # text file, so unzip -a converts line endings
            with open(full_path, 'rb') as source_file:
                archive.writestr(info, source_file.read())
    print('wrote %s: %d files, %d bytes' % (ZIP_PATH, len(chosen), os.path.getsize(ZIP_PATH)))


if __name__ == '__main__':
    main()
