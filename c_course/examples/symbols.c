/*
   Kara's C Course

   Example 11        © Kara Ottewell 1998-2018

   Purpose:
            Getting "environment variables" (symbols and logical names in VMS)
*/
/*---- Getting Symbols or Logical Names C Example ("symbols.c") --------------*/

/* ANSI C Headers */
#include <stdio.h>    /* Standard I/O */
#include <stdlib.h>   /* Standard Library */

/* Main Program starts here */
int main( int argc, char *argv[] )
{
    char *symbolValue;
/*  End of declarations ... */

    printf("MYSYM = \"%s\"\n", ( symbolValue = getenv("MYSYM")) ? symbolValue : "" );

    exit(EXIT_SUCCESS);
}
