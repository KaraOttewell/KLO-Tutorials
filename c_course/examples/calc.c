/*
   Kara's C Course

   Example 8         © Kara Ottewell 1998-2018

   Purpose:
            File i/o again, and expression parsing
*/
/*---- Calculator expression evaluator example ("calc.c") --------------------*/
/*
	History:
	Version		Name                    Date
	V01-001		Neill Clift             16-Mar-1995
			Initial version
*/

/* ANSI Headers */
#include <ctype.h>    /* Character macros */
#include <stdio.h>    /* Standard I/O */
#include <stdlib.h>   /* Standard Library */

/* Function prototypes */
int ParseExpression(void);
int ParseExpressionFactor(void);
int ParseExpressionTerm(void);
int ParseLiteral(void);
int GetNonWhite(void);
int MatchToken(int characterToMatch);

/* Start of main program */
int main( int argc, char *argv[])
{
  int value = 0;
/*  End of declarations ... */

  printf("Enter expression terminated by ;\n");
  printf("Calc> ");
  value = ParseExpression();
  if (MatchToken(';')) {
    printf("Result is %d\n", value);
  }
  else {
    printf("Expression seems bust\n");
  }

  printf("Press <CTRL/Z> and <RETURN> to exit\n");
  do {} while (getc(stdin) != EOF);
  exit(EXIT_SUCCESS);
}

/*---- Get the next character skipping white space ---------------------------*/
int GetNonWhite(void)
{
    int c;
/*  End of declarations ... */

    while (1) {
      c = getchar();
      if (c == EOF) {
        break;
      } else if (!isspace(c)) {
        break;
      }
    }
    return( c );
}

/*--- Match single character against next input char. If match then gobble ---*/
/*--- it up. If we don't match it then push it back for future matches -------*/
int MatchToken(int characterToMatch)
{
    int c;
/*  End of declarations ... */

    c = GetNonWhite();
    if (c == characterToMatch) {
      return( 1 );
    } else {
      ungetc(c,stdin); /* Put character back on input stream to be read again */
      return( 0 );
    }
}

/*---- Parse a single number from input +/- nnnnn  ---------------------------*/
int ParseLiteral(void)
{
    int result, itemsRead;
/*  End of declarations ... */

    result = 0;

    itemsRead = scanf("%d",&result);
    if (itemsRead == EOF) {
      printf("Hit EOF looking for literal\n");
    } else if (itemsRead == 0) {
      printf("Missing literal\n");
    }

    return( result );
}

/*---- Syntax is:   Literal    or:   (expression)  ---------------------------*/
int ParseExpressionFactor(void)
{
  int result;
/*  End of declarations ... */

  if (MatchToken('(')) {
    result = ParseExpression();
    if (!MatchToken(')')) {
      printf("Missing close bracket\n");
    }
  } else {
    result = ParseLiteral();
  }

  return( result );
}


/*---- Parse an expression term,  Syntax: <factor>{<multiplying_op><factor>} -*/
int ParseExpressionTerm(void)
{
  int product, factor, operation;
/*  End of declarations ... */

  product = ParseExpressionFactor();

  while (1) {
    if (MatchToken('*')) {
      operation = 1;
    } else if (MatchToken('/')) {
      operation = -1;
    } else {
      break;
    }

    factor = ParseExpressionFactor();
    if (operation == 1) {
      product = product * factor;
    } else if (factor == 0) {
      printf("Division by zero!\n");
    } else {
      product = product / factor;
    }
  }
  return( product );
}

/*---- Parse an expression, Syntax: [+/-]<term>{<adding_op><term>} -----------*/
int ParseExpression(void)
{
  int total, sign, term;
/*  End of declarations ... */

  /* Check for leading + or -. None means plus */

  if (MatchToken('+')) {
    sign = 1;
  } else if (MatchToken('-')) {
    sign = -1;
  } else {
    sign = 1;
  }

  total = ParseExpressionTerm();
  total = total * sign;

  while (1) {
    if (MatchToken('+')) {
      sign = 1;
    } else if (MatchToken('-')) {
      sign = -1;
    } else {
      break;
    }
    term = ParseExpressionTerm();
    total = total + sign * term;
  }

  return( total );
}
