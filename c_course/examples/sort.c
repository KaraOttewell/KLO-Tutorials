/*
   Kara's C Course

   Example 16        © Kara Ottewell 2026

   Purpose:
            Sorting and searching with the standard qsort and bsearch
            functions, which call a comparison function through a pointer
*/
/*---- Sorting and searching with qsort and bsearch ("sort.c") ----------------*/

/* ANSI C Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structures */
struct planet_s {
  char name[12];
  double distance;   /* average distance from the Sun, millions of km */
};

/* Function prototypes - comparison functions all have this shape */
int CompareIntegers( const void *first, const void *second );
int CompareByName( const void *first, const void *second );
int CompareByDistance( const void *first, const void *second );
void PrintPlanets( const struct planet_s planets[], size_t planetCount );

/* Main Program starts here */
int main( int argc, char *argv[] )
{
    int numbers[] = { 93, 27, 15, 47, -3, 0 };
    size_t numberCount = sizeof(numbers) / sizeof(numbers[0]);
    struct planet_s planets[] = { { "Venus",     108.2 }, { "Neptune", 4515.0 },
                                  { "Earth",     149.6 }, { "Mercury",   57.9 },
                                  { "Saturn",   1432.0 }, { "Mars",     228.0 },
                                  { "Uranus",   2867.0 }, { "Jupiter",  778.5 } };
    size_t planetCount = sizeof(planets) / sizeof(planets[0]);
    struct planet_s wanted;
    struct planet_s *found;
    size_t i;
/*  End of declarations ... */

/*  Sort an array of int */
    qsort( numbers, numberCount, sizeof(numbers[0]), CompareIntegers );
    printf("Sorted numbers:");
    for ( i = 0; i < numberCount; i++ ) {
      printf(" %d", numbers[i]);
    }
    printf("\n\n");

/*  Sort the planets alphabetically */
    qsort( planets, planetCount, sizeof(planets[0]), CompareByName );
    printf("By name:\n");
    PrintPlanets( planets, planetCount );

/*  bsearch needs the array sorted by the same comparison it searches with */
    strcpy( wanted.name, "Mars" );
    found = (struct planet_s *)bsearch( &wanted, planets, planetCount,
                                        sizeof(planets[0]), CompareByName );
    if ( found != NULL ) {
      printf("\nFound %s, %.1f million km from the Sun\n\n", found->name, found->distance);
    } else {
      printf("\n%s not found\n\n", wanted.name);
    }

/*  Same array, different comparison function, different order */
    qsort( planets, planetCount, sizeof(planets[0]), CompareByDistance );
    printf("By distance from the Sun:\n");
    PrintPlanets( planets, planetCount );

    exit(EXIT_SUCCESS);
}

/*---- Compare two ints for qsort: negative, zero or positive ---------------*/
int CompareIntegers( const void *first, const void *second )
{
    int firstValue = *(const int *)first;
    int secondValue = *(const int *)second;
/*  End of declarations ... */

/*  Not "return firstValue - secondValue;", which can overflow (see 13.1) */
    return( ( firstValue > secondValue ) - ( firstValue < secondValue ) );
}

/*---- Compare two planets by name ------------------------------------------*/
int CompareByName( const void *first, const void *second )
{
    const struct planet_s *firstPlanet = first;
    const struct planet_s *secondPlanet = second;
/*  End of declarations ... */

    return( strcmp( firstPlanet->name, secondPlanet->name ) );
}

/*---- Compare two planets by distance from the Sun -------------------------*/
int CompareByDistance( const void *first, const void *second )
{
    const struct planet_s *firstPlanet = first;
    const struct planet_s *secondPlanet = second;
/*  End of declarations ... */

    return( ( firstPlanet->distance > secondPlanet->distance ) -
            ( firstPlanet->distance < secondPlanet->distance ) );
}

/*---- Print the planets, one per line ---------------------------------------*/
void PrintPlanets( const struct planet_s planets[], size_t planetCount )
{
    size_t i;
/*  End of declarations ... */

    for ( i = 0; i < planetCount; i++ ) {
      printf("  %-8s %7.1f\n", planets[i].name, planets[i].distance);
    }
}
