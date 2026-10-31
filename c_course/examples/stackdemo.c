/*
   Kara's C Course

   Example 15        © Kara Ottewell 2026

   Purpose:
            Main program that uses the stack in stack.c, knowing only what
            stack.h tells it
*/
/*---- Using a stack from another file ("stackdemo.c") ------------------------*/

/* ANSI C Headers */
#include <stdio.h>
#include <stdlib.h>

/* Our own header */
#include "stack.h"

/* Main Program starts here */
int main( int argc, char *argv[] )
{
    int value;
/*  End of declarations ... */

    for ( value = 1; value <= 5; value++ ) {
      printf("Pushing %d\n", value * value);
      Push( value * value );
    }

    while ( !StackIsEmpty() ) {
      printf("Popped %d\n", Pop());
    }

    exit(EXIT_SUCCESS);
}
