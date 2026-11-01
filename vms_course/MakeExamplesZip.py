r"""
MakeExamplesZip.py

Purpose:
    Build KarasVMSTutorial.zip, the download index.html (the VMS course page)
    links to, from the examples folder beside this script. This is the VMS
    course's copy of the C and STL courses' scripts of the same name.

    Only the example files the exercises use go in: the Fortran sources, the
    DCL command file and the EDT startup file, plus the Intel Fortran Visual
    Studio solution (KarasVMSTutorial.slnx) and one project file (.vfproj)
    from each project subfolder. Anything Visual Studio creates when it
    builds (the x64 and Win32 output folders, .vs, the per-user .u2d files)
    is left out, because only the listed file types are ever added and the
    generated folders are never looked in.

    Everything goes under a top-level KarasVMSTutorial folder in the zip.
    Each file is flagged as text inside the zip, so "unzip -a" (as the course
    tells VMS users to type) converts the line endings for the system it is
    unpacked on.

    Note: index.html also offers a detached, ASCII-armoured PGP signature,
    KarasVMSTutorial.zip.asc. Rebuilding the zip invalidates the old
    signature, so sign the new zip again before publishing it.

Usage (cmd, from this vms_course folder):
    python -I MakeExamplesZip.py
"""

import os
import sys
import zipfile

HERE = os.path.dirname(os.path.abspath(__file__))
EXAMPLES_FOLDER = os.path.join(HERE, 'examples')
ZIP_PATH = os.path.join(HERE, 'KarasVMSTutorial.zip')
TOP_FOLDER = 'KarasVMSTutorial'

# File types the exercises use, and the solution, in the examples folder itself...
TOP_LEVEL_TYPES = {'.for', '.com', '.edt', '.slnx'}
# ...and in each project subfolder
PROJECT_TYPES = {'.vfproj'}
# Folders Visual Studio creates, which are never looked in
GENERATED_FOLDERS = {'.vs', 'x64', 'Win32', 'Debug', 'Release'}
# Files the page tells readers to use, so the zip is refused without them
REQUIRED_FILES = {'tut.for', 'sdeb.for', 'libtest1.for', 'libtest2.for', 'fortclg.com', 'edtini.edt',
                  'KarasVMSTutorial.slnx', 'tut/tut.vfproj', 'sdeb/sdeb.vfproj', 'libtest1/libtest1.vfproj'}


def files_to_zip():
    chosen = []
    for entry in sorted(os.listdir(EXAMPLES_FOLDER), key=str.lower):
        path = os.path.join(EXAMPLES_FOLDER, entry)
        if os.path.isfile(path):
            if os.path.splitext(entry)[1].lower() in TOP_LEVEL_TYPES:
                chosen.append(entry)
        elif os.path.isdir(path) and entry not in GENERATED_FOLDERS:
            for project_file in sorted(os.listdir(path), key=str.lower):
                if os.path.splitext(project_file)[1].lower() in PROJECT_TYPES:
                    chosen.append(entry + '/' + project_file)
    return chosen


def main():
    chosen = files_to_zip()
    missing = REQUIRED_FILES - set(chosen)
    if missing:
        sys.exit('refusing: %s missing from %s' % (', '.join(sorted(missing)), EXAMPLES_FOLDER))
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
