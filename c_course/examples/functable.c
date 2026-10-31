/*
   Kara's C Course

   Supplementary Example © Kara Ottewell 1998-2018

   Purpose:
            Call a function chosen by name, using a table of function pointers
*/
/*---- C Example to "look up" a function by name ("functable.c") ------------*/

/* ANSI C Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Defines and macros */
#define SIG_LEN 3
/* #define I_WANT_A_COMPILATION_WARNING */  /* Uncomment if you do ! */

/* Function prototypes */
int AddIntegers( int first, int second );      /* returns first + second */
int SubtractIntegers( int first, int second ); /* returns first - second */
int NegateInteger( int only ); /* Negate - only has one argument */

/* Typedefs */
typedef int (*func_ptr_t)( int first, int second );

/* Structures */
struct func_table_s {
  func_ptr_t function;
  char *name;
};


/* Main Program starts here */
int main( int argc, char *argv[] )
{
    int i;
    int result = 0;
    int gotMatch;
    char answer[8] = {'\0'};
    struct func_table_s functionTable[] = { {AddIntegers,"Add"},      /* Set up table of */
                                            {SubtractIntegers,"Sub"}, /* named functions */
#ifdef I_WANT_A_COMPILATION_WARNING
                                            {NegateInteger,"Neg"},
#endif
                                            {NULL,NULL}             };
/*  End of declarations ... */

    printf("Function name to call with args 6 and 3 (Add/Sub): ");
    fgets( answer, sizeof(answer) , stdin);

    i = 0;
    gotMatch = 0;
    while ( functionTable[i].function ) {
/*    Check name against each function in table */
/*    Remember that strncmp returns 0 for a match ! */
      if ( !strncmp(answer,functionTable[i].name,SIG_LEN) ) {
        gotMatch = 1;
/*      Call appropriate function through the pointer */
        result = (*functionTable[i].function)( 6, 3 );
        break;
      }
      ++i;
    }

    if ( gotMatch ) {
      printf( "Called \"%s\" - Result was %d\n", functionTable[i].name, result );
    } else {
      printf( "Couldn't match name - %s\n", answer);
    }

    exit(EXIT_SUCCESS);
}

/*---- Rather pathetic function to add up some integers ----------------------*/
int AddIntegers( int first, int second )
{
/*  End of declarations ... */
    return( first + second );
}

/*---- Crap function to subtract some integers ------------------------------*/
int SubtractIntegers( int first, int second )
{
/*  End of declarations ... */
    return( first - second );
}

/*---- Worse function to negate integers -------------------------------------*/
int NegateInteger( int only )
{
/*  End of declarations ... */
    return( -only );
}
/*----------------------------------------------------------------------------*/
