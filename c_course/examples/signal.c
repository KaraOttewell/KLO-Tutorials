/*
   Kara's C Course

   Example 13        © Kara Ottewell 1998-2018

   Purpose:
            Demonstrate signal trapping and setjmp/longjmp
*/
/*---- Signal and longjmp Example ("signal.c") -------------------------------*/

/* ANSI C Headers */
#include <setjmp.h>   /* Provide "non-local jumps" */
#include <signal.h>   /* Handle signals reported during program execution, */
                      /* from exceptions or notifications */
#include <stdio.h>    /* Standard I/O */
#include <stdlib.h>   /* Standard Library */

/* Non-standard headers that declare the sleep function on each system */
#if defined( _WIN32 )
# include <windows.h>
#elif defined( __VMS )
# include <unixlib.h>
#else
# include <unistd.h>
#endif

/* Defines and macros */
#define MAX_COUNT 5

/* Global variables */
jmp_buf savedPosition;

/* Function prototypes */
void CtrlCHandler( int signalCode );

/* Main Program starts here */
int main( int argc, char *argv[] )
{
    int loopCount;
/*  End of declarations ... */

    loopCount = 0;

    signal( SIGINT, CtrlCHandler );

    if ( !setjmp(savedPosition) ) {
      for ( ; loopCount < MAX_COUNT; ++loopCount ) {
        printf("At main line - looping #%d - enter Ctrl/C\n", loopCount);
#if !defined( _WIN32 )
        sleep( 10 );
#else
        Sleep( 10000 );
#endif
      }
    } else {
      printf("Returned from Ctrl C handler - exiting early\n");
    }

    exit(EXIT_SUCCESS);
}

void CtrlCHandler( int signalCode )
{
/*  End of declarations ... */

    if ( signalCode == SIGINT ) {
      printf("Handling Ctrl C - return to position saved by setjmp()\n");
      longjmp( savedPosition, 1 ); /* Use any non-zero number */
    } else {
      printf("Strange - Ctrl C handler called with wrong signal code !\n");
    }
}
