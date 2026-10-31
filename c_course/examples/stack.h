/*
   Kara's C Course

   Example 15        © Kara Ottewell 2026

   Purpose:
            Header file for the integer stack in stack.c - everything another
            file needs to know to use the stack, and nothing more
*/
/*---- Integer stack interface ("stack.h") ------------------------------------*/
#if !defined( STACK_H )  /* Guard against being included twice */
#define STACK_H

/* Function prototypes - these are declarations, not definitions */
void Push( int value );
int Pop( void );
int StackIsEmpty( void );
int StackIsFull( void );

#endif /* STACK_H */
