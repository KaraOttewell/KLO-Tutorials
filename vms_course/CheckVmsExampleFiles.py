r"""
CheckVmsExampleFiles.py

Purpose:
    Check the VMS course's example files (the examples folder beside this
    script) after editing them, before running UpdateListings.py and
    MakeExamplesZip.py.

      1. Converts every example file (.for, .com and .edt; the Visual Studio
         solution and project files are left alone) to CRLF line endings,
         which is what the zip should carry (an editor may have saved LF).
      2. Reports non-ASCII bytes and trailing spaces.
      3. Reports any Fortran line longer than 72 columns. VMS Fortran ignores
         everything past column 72 in fixed-form source, which would silently
         cut a statement short.
      4. Compiles and runs the Fortran examples with gfortran, in a temporary
         folder, and prints their output for comparison with the sample
         outputs in index.html (which are kept by hand). sdeb.for is built
         twice: once with the IEEE defaults, where its divide by zero gives
         Infinity, and once with divide-by-zero trapping, like VMS
         /IEEE_MODE=FAST, where it stops with a floating-point exception.
         Both are the expected behaviour for the debugger exercise.

    gfortran is not VMS Fortran, so this proves the programs are correct
    standard Fortran, not that they behave identically on VMS. The DCL
    command file fortclg.com is not run at all.

    gfortran must be on PATH. On this machine it comes with Strawberry Perl,
    in C:\Strawberry\c\bin.

Usage (cmd, from this vms_course folder):
    python -I CheckVmsExampleFiles.py

    Exit status is 1 if any problem was reported, 0 otherwise.
"""
import os
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
EXAMPLES_FOLDER = os.path.join(HERE, 'examples')
FORTRAN_OPTIONS = ['-ffixed-form', '-std=legacy', '-Wall', '-O0']
# Only the files the exercises use; the solution and projects belong to Visual Studio
EXAMPLE_TYPES = {'.for', '.com', '.edt'}


def normalise_and_check():
    problems = []
    for name in sorted(os.listdir(EXAMPLES_FOLDER)):
        path = os.path.join(EXAMPLES_FOLDER, name)
        if not os.path.isfile(path) or os.path.splitext(name)[1].lower() not in EXAMPLE_TYPES:
            continue
        with open(path, 'rb') as example_file:
            data = example_file.read()
        if any(byte > 127 for byte in data):
            problems.append('%s has non-ASCII bytes' % name)
        text = data.replace(b'\r\n', b'\n')
        for number, line in enumerate(text.split(b'\n'), start=1):
            if name.lower().endswith('.for') and len(line) > 72:
                problems.append('%s line %d is %d columns long' % (name, number, len(line)))
            if line != line.rstrip():
                problems.append('%s line %d has trailing spaces' % (name, number))
        crlf = text.replace(b'\n', b'\r\n')
        if crlf != data:
            with open(path, 'wb') as example_file:
                example_file.write(crlf)
            print('converted to CRLF:', name)
    return problems


def run(command, folder):
    result = subprocess.run(command, cwd=folder, capture_output=True, text=True)
    print('>', ' '.join(command))
    print((result.stdout + result.stderr).rstrip() or '(no output)')
    print('exit status', result.returncode)
    return result.returncode


def build_and_run(folder, program, sources, extra_options=()):
    sources = [os.path.join(EXAMPLES_FOLDER, source) for source in sources]
    executable = os.path.join(folder, program + '.exe')
    if run(['gfortran'] + FORTRAN_OPTIONS + list(extra_options) + ['-o', executable] + sources, folder) == 0:
        run([executable], folder)


def main():
    problems = normalise_and_check()
    for problem in problems:
        print('PROBLEM:', problem)
    folder = tempfile.mkdtemp(prefix='VmsExamples_')
    build_and_run(folder, 'tut', ['tut.for'])
    build_and_run(folder, 'libtest', ['libtest1.for', 'libtest2.for'])
    build_and_run(folder, 'sdeb', ['sdeb.for'])
    build_and_run(folder, 'sdebtrap', ['sdeb.for'], ['-ffpe-trap=zero', '-g'])
    if problems:
        sys.exit(1)


if __name__ == '__main__':
    main()
