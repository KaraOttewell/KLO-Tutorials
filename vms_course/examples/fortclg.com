$! Kara's VMS Tutorial - example file
$! (C) Kara Ottewell 1996-2026
$!
$! ---- FORTCLG.COM - compile, link and run a Fortran program ----
$!
$! Usage:   @FORTCLG [program]
$!
$! The program is looked for in your current default directory, with
$! file type .FOR. With no program named, it uses TUT. To make it use
$! a program of your own, change the line marked "<<< change".
$!
$ program = P1
$ IF program .EQS. "" THEN program = "TUT"               ! <<< change
$!
$! F$PARSE fills in the device, directory and the default file type,
$! and F$SEARCH returns an empty string if there is no such file
$ source = F$PARSE(program, ".FOR")
$ IF F$SEARCH(source) .EQS. ""
$ THEN
$     WRITE SYS$OUTPUT "FORTCLG: cannot find ", program, ".FOR"
$     EXIT
$ ENDIF
$ name = F$PARSE(source, , , "NAME")
$!
$! If any step fails, DCL stops the command procedure there, because
$! the default error action in a command procedure is ON ERROR THEN EXIT
$ WRITE SYS$OUTPUT "Compiling ", name, ".FOR"
$ FORTRAN/NOLIST 'source'
$ WRITE SYS$OUTPUT "Linking ", name, ".OBJ"
$ LINK 'name'
$ WRITE SYS$OUTPUT "Running ", name, ".EXE"
$ RUN 'name'
$ EXIT
