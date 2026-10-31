/*
   Kara's C Course

   Example 6         © Kara Ottewell 1998-2018

   Purpose:
            Show how to get input from the keyboard - this example is not a safe
            way to go about this because it has no length check on input string!
*/
/*---- Keyboard Input C Example ("input.c") ----------------------------------*/

/* ANSI C Headers */
#include <stdio.h>
#include <stdlib.h>

/* Main Program starts here */
int main( int argc, char *argv[] )
{
    int decimalNumber = 0;
    float realNumber = 0.0;
    char string[80] = {'\0'};
/*  End of declarations ... */

    printf("Enter a string, a decimal and a real number separated by spaces\n");
    scanf("%s %d %f", string, &decimalNumber, &realNumber); /* Not good - no string length check */
    printf("You entered \"%s\", %d and %f\n", string, decimalNumber, realNumber);

    exit(EXIT_SUCCESS);
}
