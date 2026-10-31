/*
   Kara's C Course

   Example 7         © Kara Ottewell 1998-2018

   Purpose:
            Demonstrate file input and output
*/
/*---- File IO Example ("fileio.c") ------------------------------------------*/

/*---- Put all #include files here -------------------------------------------*/
/* ANSI Headers */
#include <ctype.h>    /* Character macros */
#include <errno.h>    /* errno error codes */
#include <stdio.h>    /* Standard I/O */
#include <stdlib.h>   /* Standard Library */
#include <string.h>   /* String Library */
#include <time.h>     /* Time Library */

/*---- Put all #define statements here ---------------------------------------*/
#define PROGRAM_VERSION "1.6"
#define TYPE_OF_FILE "TEST_DATA"
#define NDATA_POINTS 10

/*---- Put all structure definitions here ------------------------------------*/
/* Following structures MUST be packed tightly i.e. no member alignment ------*/
#ifdef __DECC
# pragma member_alignment save
# pragma nomember_alignment
#endif

struct file_header_s {
  char type[32];
  char version[8];
  char creator[20];
  time_t time;
};
struct data_s {
  short x;
  short y;
  char name[8];
};

#ifdef __DECC
# pragma member_alignment restore
#endif

int main(int argc, char *argv[])
{
    struct data_s *dataPoints = NULL;
    struct file_header_s fileHeader;
    FILE *outputFile = NULL;
    FILE *inputFile = NULL;
    int i = 0, gotAnswer = 0;
    char answer[8] = "N", yesNo[4], nodeAndUser[20];
    char fileName[FILENAME_MAX] = {'\0'};
    char *characterPointer = NULL;
    char *nodeName = NULL, *userName = NULL;
    long int dataCount = 0;
    size_t itemsTransferred = 0;
/*  End of declarations ... */

/*  Set up a default name in case user hasn't specified one */
    if (argc < 2)
    {
      strncpy(fileName,"MYDATA.DAT",sizeof(fileName)/sizeof(fileName[0]) - 1);
    } else {
      strncpy(fileName,argv[1],sizeof(fileName)/sizeof(fileName[0]) - 1);
    }

/*  Get node name and user name. getenv returns NULL for a name that is not */
/*  defined, and sprintf must never be handed NULL for a %s, so substitute "" */
#if !defined( _WIN32 )
    nodeName = getenv("SYS$NODE");                                    /* VMS */
    userName = getenv("USER");
#else
    nodeName = getenv("COMPUTERNAME");
    userName = getenv("USERNAME");
#endif
    if ( nodeName == NULL ) nodeName = "";
    if ( userName == NULL ) userName = "";
/*  The precision in each %.Ns limits how many characters of that string are */
/*  copied, so the result always fits in nodeAndUser (19 characters + '\0') */
#if !defined( _WIN32 )
    sprintf( nodeAndUser, "%.9s%.10s", nodeName, userName );
#else
    sprintf( nodeAndUser, "\\\\%.7s\\%.9s", nodeName, userName );
#endif
/*  Convert to uppercase. The cast matters: toupper (which lives in <ctype.h>) */
/*  is only defined for values of unsigned char, and plain char may be signed */
    characterPointer = nodeAndUser;
    while ( (*characterPointer = toupper( (unsigned char)*characterPointer )) != '\0' ) {
      ++characterPointer;
    }

/*  Allocate data space and initialize it */
    dataPoints = (struct data_s *)malloc( sizeof(struct data_s)*NDATA_POINTS );
    if ( dataPoints )
    {
      dataCount = NDATA_POINTS;
      for ( i = 0; i < dataCount; i++) {
        dataPoints[i].x = dataPoints[i].y = i;
        sprintf(dataPoints[i].name, "%3.3d,%3.3d", dataPoints[i].x, dataPoints[i].y );
      }

/*    Open the file for writing in binary mode */
      outputFile = fopen(fileName,"wb");
      if ( outputFile != NULL ) {

/*      Set up the header */
        strcpy(fileHeader.type,TYPE_OF_FILE);
        strcpy(fileHeader.version,PROGRAM_VERSION);
        sprintf(fileHeader.creator,"%s",nodeAndUser);
        (void)time(&fileHeader.time);

        printf("Writing out the header\n");

/*   Items written                Data pointer  Size in bytes  No. items stream*/
/*        |                           |             |               |    |     */
/*        v                           v             v               v    v     */
        itemsTransferred = fwrite( &fileHeader, sizeof(fileHeader), 1, outputFile);
        if ( ferror(outputFile) ) {
          fprintf(stderr,"Error writing file 'header':\n%s",strerror(errno));
        }

        printf("Writing out the number of data items, %ld\n", dataCount);
        itemsTransferred = fwrite( &dataCount, sizeof(dataCount), 1, outputFile);
        if ( ferror(outputFile) ) {
          fprintf(stderr,"Error writing number of data items:\n%s",
                  strerror(errno));
        }

        printf("Writing out the actual data all in one chunk\n");
        itemsTransferred = fwrite( dataPoints, sizeof(struct data_s)*dataCount, 1, outputFile);
        if ( ferror(outputFile) ) {
          fprintf(stderr,"Error writing data:\n%s",strerror(errno));
        }

        printf("Closing output file\n");
        fclose(outputFile);

      } else {
        fprintf(stderr,"Error creating data file %s:\n%s", fileName,
                strerror(errno));
      }
    } else {
      fprintf(stderr, "Couldn't allocate space for %d data structures\n", NDATA_POINTS);
      exit(EXIT_FAILURE);
    }

/*  Now optionally read the data back in and format */

    do {
      printf("\nRead data back in ? [Y/N]: ");
      if ( fgets( yesNo, sizeof(yesNo) , stdin) == NULL ) { /* Reads in sizeof(yesNo)-1 chars */
        break; /* End of input, so leave answer as "N" */
      }
      gotAnswer = sscanf( yesNo, "%[YyNnTtFf]", answer);
    } while ( gotAnswer != 1 );

    if ( answer[0] == 'Y' || answer[0] == 'y' ||
         answer[0] == 'T' || answer[0] == 't' ) {
      printf( "Here we go ..\n" );

/*    Zero out the structures just to show there's no cheating */
      dataCount = 0;
      memset( &fileHeader, 0 , sizeof( fileHeader ) );
      memset( dataPoints, 0 , sizeof(struct data_s)*NDATA_POINTS );

/*    Open the file for reading in binary mode */
      inputFile = fopen(fileName,"rb");
      if ( inputFile != NULL ) {

        printf("Reading in the header\n");
        itemsTransferred = fread(&fileHeader,sizeof(fileHeader),1,inputFile);
        if ( ferror(inputFile) ) {
          fprintf(stderr,"Error reading file 'header':\n%s",strerror(errno));
        }

        printf("Header information:  file type %s\n", fileHeader.type );
        printf("                       version %s\n", fileHeader.version );
        printf("                    created by %s\n", fileHeader.creator );
        printf("                            on %s\n", ctime( &fileHeader.time ) );

        itemsTransferred = fread( &dataCount, sizeof(dataCount), 1, inputFile);
        printf("Read in the number of data items, %ld\n", dataCount);
        if ( ferror(inputFile) ) {
          fprintf(stderr,"Error reading number of data items:\n%s",
                  strerror(errno));
        }

/*      Never trust a count read from a file - a bad one would make the */
/*      next fread write past the end of the dataPoints array           */
        if ( dataCount < 0 || dataCount > NDATA_POINTS ) {
          fprintf(stderr,"File claims %ld data items, but there is only room for %d\n",
                  dataCount, NDATA_POINTS);
          dataCount = 0;
        }

        printf("Reading in the actual data all in one chunk\n");
        itemsTransferred = fread( dataPoints, sizeof(struct data_s)*dataCount, 1, inputFile);
        if ( ferror(inputFile) ) {
          fprintf(stderr,"Error reading data:\n%s",strerror(errno));
        }

        printf("Closing input file\n\n");
        fclose(inputFile);

        printf("Read in %ld data items\n", dataCount);
        for ( i = 0; i < dataCount; i++) {
          printf("%3d) x:%3d, y:%3d, Label: %s\n",
                 i, dataPoints[i].x, dataPoints[i].y, dataPoints[i].name );
        }

      } else {
        fprintf(stderr,"Error opening data file %s:\n%s", fileName,
                strerror(errno));
      }

    } else {
      printf( "OK - be like that\n" );
    }

    free( dataPoints );
    dataPoints = NULL;

    exit(EXIT_SUCCESS);
}
