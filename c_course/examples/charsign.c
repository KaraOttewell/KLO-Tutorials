/*
   Kara's C Course

   Example 5         © Kara Ottewell 1998-2018

   Purpose:
            Demonstrate function prototypes, and check if signed or unsigned
            is the default for char on your computer
*/
/*---- To sign or not to sign, that is the example ("charsign.c") ------------*/

/* ANSI C Headers */
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

/* Function prototypes */
int Power( int base, int exponent );

/* Main Program starts here */
int main( int argc, char *argv[] )
{
    char plainCharacter;
    unsigned char unsignedCharacter;
/*  End of declarations ... */

/*  Set the top bit of both characters */
    plainCharacter = Power( 2, (CHAR_BIT-1) );
    unsignedCharacter = Power( 2, (CHAR_BIT-1) );

/*  Shift them both right by one bit, >> is the right shift operator */
    plainCharacter >>= 1;
    unsignedCharacter >>= 1;
/*  Check for equality - check out the ? ternary operator ! */
    printf("Your computer has %ssigned char.\n",
           ( plainCharacter == unsignedCharacter ) ? "un" : "" );

    exit(EXIT_SUCCESS);
}

/*---- Function to raise integer to a power, nicked from K&R II, page 25 -----*/
int Power( int base, int exponent )
{
    int i, result;
/*  End of declarations ... */
    result = 1;
    for ( i = 1; i <= exponent; i++) {
      result = result * base;
    }

    return( result );
}
