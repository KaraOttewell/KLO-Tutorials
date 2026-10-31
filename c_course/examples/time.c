/*
   Kara's C Course

   Example 12         © Kara Ottewell 1998-2018

   Purpose:
            Using standard functions for date and time manipulation
*/
/*---- Getting the time ("time.c") -------------------------------------------*/

/* ANSI C Headers */
#include <stdio.h>    /* Standard I/O */
#include <stdlib.h>   /* Standard Library */
#include <time.h>     /* Time routines */

/* Main Program starts here */
int main( int argc, char *argv[] )
{
    time_t currentTime;
    struct tm *timeComponents;
    char dayOfWeek[80];
/*  End of declarations ... */

/*  Get the current time */
    time(&currentTime); /* currentTime now contains seconds since January 1, 1970 */

/*  Convert this to a string using the ctime() function */
    printf("%s\n", ctime( &currentTime ) );

/*  Split the time into its components - hours, minutes, seconds etc. */
    timeComponents = localtime( &currentTime );

/*  Selectively copy day of week into string */
    strftime( dayOfWeek, sizeof(dayOfWeek), "Today is %A", timeComponents );

/*  Print out the day of the week */
    printf("%s\n", dayOfWeek );

    exit(EXIT_SUCCESS);
}
