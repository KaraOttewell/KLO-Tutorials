/*
   Kara's C Course

   Example 3         © Kara Ottewell 1998-2018

   Purpose:
            Demonstrate C loop constructs; for, while, do
*/
/*---- C Loops Example ("loops.c") -------------------------------------------*/

/* ANSI C Headers */
#include <stdio.h>
#include <stdlib.h>

/* Defines and Macros */
#define LMT 5

/* Main Program starts here */
int main( int argc, char *argv[] )
{
    int i;
/*  End of declarations ... */
    printf("LMT = %d\n", LMT);

    printf("\n'for' loop - for ( i = 1; i <= LMT; i++ ) {...}\n");
    for ( i = 1; i <= LMT; i++ ) { /* More usual in C would be i = 0; i < LMT; i++ */
      printf("%d\n", i );
    }

    printf("\ni = 0\n");
    printf("'while' loop - while ( i++ < LMT ) {...}\n");
    i = 0;
    while ( i++ < LMT )
    {
      printf("%d\n", i );
    }

    printf("\ni = LMT\n");
    printf("'do' loop - do {...} while ( ++i < LMT ); - always executes at least once\n");
    i = LMT;
    do
    {
      printf("%d\n", i );
    } while ( ++i < LMT );

    exit(EXIT_SUCCESS);
}
