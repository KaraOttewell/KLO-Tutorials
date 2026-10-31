/*
   Kara's C Course

   Example 14        © Kara Ottewell 1998-2018

   Purpose:
            Standard implementation of a function with variable arguments
*/
/*---- Variable Arguments C Example ("vargs.c") ------------------------------*/

/* ANSI C Headers */
#include <stdarg.h>   /* Variable argument handling */
#include <stdio.h>    /* Standard I/O */
#include <stdlib.h>   /* Standard Library */

/* Defines and macros */
#define END 0

/* Function prototypes */
int AddSomeIntegers( int first, ...);

/* Main Program starts here */
int main( int argc, char *argv[] )
{
    int total;
/*  End of declarations ... */

    total = AddSomeIntegers( 1, 2, 3, 4, END);

    printf("Total was %d\n", total );

    exit(EXIT_SUCCESS);
}

/*---- Rather pathetic function to add up some integers ----------------------*/
int AddSomeIntegers( int first, ...)
{
    va_list arguments; /* Use to point to each argument in turn */
    int nextValue, sum, count;
/*  End of declarations ... */

    count = 1;
    sum = first;
    va_start( arguments, first ); /* Use last named argument - first in this case */

/*  End of args is marked by END, which is zero */

    while ( (nextValue = va_arg( arguments, int )) != END ) { /* Second arg of va_arg is type */
      sum += nextValue;
      ++count;
    }
    va_end( arguments ); /* Tidy up */

    printf("AddSomeIntegers added %d integers\n", count );

    return( sum );
}
