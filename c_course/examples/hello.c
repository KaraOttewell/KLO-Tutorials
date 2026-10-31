/*
   Kara's C Course

   Example 1         © Kara Ottewell 1998-2018

   Purpose:
            Usual "hello world" first program
*/
/*---- Hello World C Example ("hello.c") -------------------------------------*/

/* ANSI C Headers */
#include <stdio.h>
#include <stdlib.h>

/* Main Program starts here */
int main( int argc, char *argv[] )
{
    int i = 0;
/*  End of declarations ... */

    for ( i = 0; i < 10; i++ )
    {
      printf("%d Hello World !\n",i);
    }

    exit(EXIT_SUCCESS);
}
