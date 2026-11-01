$! 'F$VERIFY(0)    Compile CXX program given as parameter P1
$!
$! Use:
$!      @MAKE progname [D]
$!                      ^
$!                      |
$!                      Optional, indicates that debug image required
$!
$ SAY:=WRITE SYS$OUTPUT
$ ON ERROR THEN $ GOTO exit
$ ON CONTROL_Y THEN $ GOTO exit
$ source_spec = P1
$ source_type = F$PARSE(source_spec,,,"TYPE")
$ source_name = F$PARSE(source_spec,,,"NAME")
$ source_dir = F$PARSE(source_spec,,,"DIRECTORY")
$ source_dev = F$PARSE(source_spec,,,"DEVICE")
$!
$ IF source_type.EQS."."
$ THEN
$   source_type = ".CXX"
$   source_spec = source_dev+source_dir+source_name+source_type
$   IF F$SEARCH(source_spec).EQS.""
$   THEN
$     source_type = ".CPP"
$     source_spec = source_dev+source_dir+source_name+source_type
$     IF F$SEARCH(source_spec).EQS.""
$     THEN
$       source_type = ".C"
$       source_spec = source_dev+source_dir+source_name+source_type
$       IF F$SEARCH(source_spec).EQS.""
$       THEN
$         WRITE SYS$OUTPUT "Cannot find source file for ''source_name'"
$       ENDIF
$     ENDIF
$   ENDIF
$ ENDIF
$!
$ source_spec = source_dev+source_dir+source_name+source_type
$!
$ IF  source_type.EQS.".CXX" .OR. source_type.EQS.".CPP"
$ THEN
$   compile = "CXX/ASSUME=(NOHEADER_TYPE_DEFAULT)/EXCEPTIONS/TEMPLATE_DEFINE"
$   link_it = "CXXLINK"
$ ELSE
$   compile = "CC/PREFIX=ALL"
$   link_it = "LINK"
$ ENDIF
$!
$ source_spec = source_dev+source_dir+source_name+source_type
$!
$ is_alpha = F$GETSYI("NODE_HWTYPE").EQS."ALPH"
$ IF is_alpha
$ THEN
$   obj = "OBJ_ALPHA"
$   exe = "EXE_ALPHA"
$ ELSE
$   obj = "OBJ"
$   exe = "EXE"
$ ENDIF
$!
$! Check for debug
$!
$ IF P1.EQS."D" .OR. P2.EQS."D"
$ THEN
$   debug = " with /DEBUG"
$   cqual = "/NOOPTIMIZE/DEBUG"
$   lqual = "/TRACE/DEBUG"
$ ELSE
$   debug = ""
$   cqual = "/OPTIMIZE/NODEBUG"
$   lqual = "/NODEBUG"
$ ENDIF
$!
$ this_file = F$ENVIRONMENT("PROCEDURE")
$ this_dev = F$PARSE(this_file,,,"DEVICE")
$ this_dir = F$PARSE(this_file,,,"DIRECTORY")
$ orig_default = F$ENVIRONMENT("DEFAULT")
$ SET DEFAULT 'this_dev''this_dir'
$ SHOW DEFAULT
$!
$ base_priority = F$GETJPI("","PRIB")
$ SET PROCESS/PRIORITY=1
$ IF P1.EQS."L" .OR. P2.EQS."L" THEN $ GOTO link
$!
$! Compile
$!
$compile:
$ SAY "''compile' ''source_name'''source_type' ''debug' -> ''source_name'.''obj'"
$ 'compile''cqual'/OBJ=.'obj' 'source_name''source_type'
$!
$! Link
$!
$link:
$ SAY "''link_it' ''source_name' ''debug' -> ''source_name'.''exe'"
$ 'link_it''lqual'/EXE=.'exe' 'source_name'.'obj'
$!
$ DELETE/NOLOG 'source_name'.'obj';*
$!
$exit:
$ SAY "Exiting"
$ SET DEFAULT 'orig_default'
$ SET PROCESS/PRIORITY='base_priority'
$ EXIT
