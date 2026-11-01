/*
   Kara Ottewell's STL Course

   Example 1.1                  © Kara Ottewell 1997-2026

   Purpose:
            Simple vector and sort demonstration using ANSI C
*/
/*---- Expanding, sorted integer array in ANSI C ("example_1_1.c") ----------*/

/* ANSI C Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Typedef array type in case we need to change it */
typedef int array_type;

/* Function Prototypes */
int CompareValues( const void *first, const void *second );
array_type *GetArraySpace( int itemCount );

int main( void )
{
    int i;
    int itemCount = 0;
    array_type inputValue;
    array_type *values = NULL;
/*  End of declarations ... */

    printf( "Enter integers, <Enter> after each. To finish, type <Ctrl>Z <Enter>\n"
            "at the start of a line (<Ctrl>D on Unix). Windows sometimes wants\n"
            "<Ctrl>Z <Enter> more than once, but remember:\n\n"
            "No more. No less. Three shalt be the number thou shalt count,\n"
            "and the number of the counting shall be three.\n"
            "Four shalt thou not count, nor either count thou two,\n"
            "excepting that thou then proceed to three. Five is right out.\n\n" );

/*  scanf returns the number of items it converted, so this loop also stops
    at anything that isn't a number, instead of looping for ever */
    while ( scanf( "%d", &inputValue ) == 1 ) {
      values = GetArraySpace( itemCount + 1 );
      values[itemCount] = inputValue;
      printf( "%6d: %d\n", itemCount, values[itemCount] );
      ++itemCount;
    }

    if ( itemCount ) {
      qsort( values, itemCount, sizeof(array_type), CompareValues );
      for ( i = 0; i < itemCount; ++i )
        printf( "%d ", values[i] );
      printf( "\n" );
    }

    free( values );
    return( EXIT_SUCCESS );
}

/*---- Comparison func returns: -ve if a < b,  0 if a == b,  +ve if a > b ----*/
int CompareValues( const void *first, const void *second )
{
    const array_type *firstValue = (const array_type *)first;
    const array_type *secondValue = (const array_type *)second;
/*  End of declarations ... */

/*  Not "return *firstValue - *secondValue;", which overflows (undefined
    behaviour) for values far apart, such as INT_MAX and -1 */
    return( (*firstValue > *secondValue) - (*firstValue < *secondValue) );
}

/*---- Allocate space: n == 0 return pointer, n > 0 expand/realloc if needed -*/
array_type *GetArraySpace( int itemCount )
{
    const int extraSpace = 2;
    array_type *newSpace;
    static array_type *arraySpace;
    static int maximumItems;
/*  End of declarations ... */

    if ( itemCount > maximumItems ) {
      itemCount += extraSpace;
      if ( arraySpace ) {
        newSpace = (array_type *)realloc( arraySpace, sizeof(array_type) * itemCount );
        if ( newSpace ) {
/*        Successfully expanded the space */
          arraySpace = newSpace;
/*        Clear new storage space */
          memset( &arraySpace[maximumItems], 0, sizeof(array_type) * (itemCount - maximumItems) );
        } else {
/*        Couldn't allocate the space */
          exit( EXIT_FAILURE );
        }
      } else {
        arraySpace = (array_type *)calloc( itemCount, sizeof(array_type) );
        if ( !arraySpace ) {
/*        Couldn't allocate the space */
          exit( EXIT_FAILURE );
        }
      }
      maximumItems = itemCount;
    }
    return( arraySpace );
}
