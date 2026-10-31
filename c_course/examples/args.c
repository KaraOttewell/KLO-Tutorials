/*
   Kara's C Course

   Example 9         © Kara Ottewell 1998-2018

   Purpose:
            Getting command line arguments
*/
/*---- Getting Command Line Arguments C Example ("args.c") -------------------*/

/* ANSI C Headers */
#include <stdio.h>    /* Standard I/O */
#include <stdlib.h>   /* Standard Library */

/* Main Program starts here */
int main( int argc, char *argv[] )
{
    int i;
/*  End of declarations ... */

    for ( i = 0; i < argc; i++ ) {
      printf("Argument %d = \"%s\"\n", i, argv[i] );
    }

    printf("Press <RETURN> to exit\n");
    getchar();
    exit(EXIT_SUCCESS);
}
