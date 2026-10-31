/*
   Kara's C Course

   Example 15        © Kara Ottewell 2026

   Purpose:
            A simple integer stack, compiled separately and linked with
            stackdemo.c to show a program built from more than one file
*/
/*---- Integer stack implementation ("stack.c") -------------------------------*/

/* ANSI C Headers */
#include <assert.h>

/* Our own header - quotes, not angle brackets */
#include "stack.h"

/* Defines and Macros */
#define STACK_SIZE 10

/* Global variables - static, so no other file can see or change them */
static int stackValues[STACK_SIZE];
static int stackDepth = 0;

/*---- Put a value on top of the stack ---------------------------------------*/
void Push( int value )
{
    assert( !StackIsFull() );
    stackValues[stackDepth++] = value;
}

/*---- Take the top value off the stack --------------------------------------*/
int Pop( void )
{
    assert( !StackIsEmpty() );
    return( stackValues[--stackDepth] );
}

/*---- Is there anything on the stack ? --------------------------------------*/
int StackIsEmpty( void )
{
    return( stackDepth == 0 );
}

/*---- Is there room for another value ? -------------------------------------*/
int StackIsFull( void )
{
    return( stackDepth == STACK_SIZE );
}
