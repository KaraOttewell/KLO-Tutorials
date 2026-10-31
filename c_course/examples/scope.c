/*
   Kara's C Course

   Example 2         © Kara Ottewell 1998-2018

   Purpose:
            Demonstrate scope of variable names
*/
/*---- Variable Scope Example ( "scope.c" ) ----------------------------------*/
/* ANSI C Headers */
#include <stdio.h>
#include <stdlib.h>

/* Global variables, visible externally too (i.e. to things linked */
/* against this) Generally they should be avoided as far as */
/* possible, because it can be very difficult to discover which */
/* routine changes their value, and they introduce "hidden" dependencies */
int someCounter;
double doubleResult;

/* Function prototypes */
void SetDoubleResult(void);

/* Main Program starts here */
int main( int argc, char *argv[] )
{
    int j;
    int localVariable; /* .. local to main */
/*  End of declarations ... */

    localVariable = 1;
    printf("localVariable = %d (in main)\n\n", localVariable );

    for ( j = 0; j < 10; j++ ) {
      int localVariable; /* .. local to this loop - Not necessarily a good */
                         /* idea because it can cause confusion as to which */
                         /* variable we actually want to access */
      localVariable = j;
      printf("localVariable = %d (inside loop)\n", localVariable );
    }

    printf("\nlocalVariable = %d (in main)\n\n", localVariable );

    /* Now let's look at the default initialization values of the globals */
    printf("someCounter = %d (in main)\n", someCounter);
    printf("doubleResult = %f (in main)\n\n", doubleResult);

    /* Call a function that changes the global variables .. */
    SetDoubleResult();

    /* .. and look at them again */
    printf("someCounter = %d (in main)\n", someCounter);
    printf("doubleResult = %f (in main)\n", doubleResult);

    exit(EXIT_SUCCESS);
}

void SetDoubleResult(void)
{
    ++someCounter;
    doubleResult = 3.141;
    printf("someCounter = %d (in SetDoubleResult)\n", someCounter);
    printf("doubleResult = %f (in SetDoubleResult)\n\n", doubleResult);
}
