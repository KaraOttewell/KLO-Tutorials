/*
   Kara's C Course

   Supplementary Example © Kara Ottewell 1998-2018

   Purpose:
            Demonstrate some standard string functions
*/
/*---- Using Strings C Example ("strings.c") --------------------------------*/

/* ANSI C Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Macros and Defines */
#define MAX_STRING_SIZE 80

/* Main Program starts here */
int main( int argc, char *argv[] )
{
    char string1[MAX_STRING_SIZE];
    char string2[MAX_STRING_SIZE];
/*  End of declarations ... */

    sprintf(string1,"Hello %d ", 1);  /* Write directly into character array */
    sprintf(string2,"World");

/*  This is unsafe concatenation - makes no check on length of string1 */
    strcat(string1,string2);
    printf("%s\n",string1);

/*  This is safer - checks length of string1 and allows for terminating \0 */
/*  Note that a null character is _always_ appended to the result of */
/*  strncat function. If strncat reaches the specified maximum, it */
/*  sets the next byte in its "output" argument to the null character, */
/*  hence the final -1 below */
    strncat(string1,
            " - here is a very long string that would probably cause an overflow if not shortened",
            sizeof(string1)-strlen(string1)-1 );
    printf("%s\n",string1);

    exit(EXIT_SUCCESS);
}
