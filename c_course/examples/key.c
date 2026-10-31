/*
   Kara's C Course

   Example 10        © Kara Ottewell 1998-2018

   Purpose:
            Reading VMS keyed indexed files from DEC C
*/
/*---- Keyed Index File C Demonstration Program ("key.c") --------------------*/
/*
	History:
	Version		Name                    Date
	V01-001		Neill Clift             09-Mar-1995
			Initial version
*/

/* ANSI Headers */
#include <ctype.h>    /* Character macros */
#include <stddef.h>   /* Numerous standard macro definitions */
#include <stdio.h>    /* Standard I/O */
#include <stdlib.h>   /* Standard Library */
#include <string.h>   /* String Library */

/* VMS Headers */
#include <rab.h>		/* RMS RAB */
#include <rms.h>		/* RMS access blocks etc */
#include <ssdef.h>		/* System service completion codes */
#include <starlet.h>
#include <lib$routines.h>

/* Defines and Macros */
#define NAME_SIZE  32        /* Size of person field */
#define PHONE_SIZE 20        /* Size of the phone number field */

/* Structure declarations */

struct phone_r {
/* Define the structure that will be the record of the keyed file. */
/* It is indexed with two keys for each of the structure's fields. */
   char name[NAME_SIZE];
   char phone[PHONE_SIZE];
};

/* Global Variables - not externally visible */
static struct FAB    fab;        /* FAB for file  */
static struct RAB    rab;        /* RAB for file */
static struct NAM    nam;        /* NAM block to report I/O errors nicely */
static struct XABKEY nameKey, phoneKey;    /* XABs to define the two keys */

static char expandedFileName[NAM$C_MAXRSS];   /* Expanded file name */
static char resultantFileName[NAM$C_MAXRSS];  /* Resultant file name */

static char nameKeyName[32] = "Person";  /* Name of first key */
static char phoneKeyName[32] = "Phone";  /* Name of second key */

/*---- Routine to close the RMS file -----------------------------------------*/
int ClosePhoneFile( void )
{
   long int status;
/* End of declarations ... */

   status = sys$close( &fab );
   return( status );
}

/*---- Open/Create the keyed index file --------------------------------------*/
int CreatePhoneFile( char *fileName )
{
   long int status, connectStatus;
/* End of declarations ... */

   fab = cc$rms_fab;                    /* initialise the FAB */
   fab.fab$l_alq = 100;			/* Preallocate space */
   fab.fab$w_deq = 100;
   fab.fab$b_fac = FAB$M_PUT|FAB$M_DEL|FAB$M_UPD;
   fab.fab$l_fop = FAB$M_DFW|FAB$M_CIF;
   fab.fab$b_org = FAB$C_IDX;
   fab.fab$b_rfm = FAB$C_VAR;
   fab.fab$l_fna = fileName;
   fab.fab$b_fns = strlen(fileName);
   fab.fab$b_rat = FAB$M_CR;
   fab.fab$l_xab = (char *) &nameKey;

   /* Init XABKEY to define key for name key */
   nameKey = cc$rms_xabkey;		/* Initialise XABKEY structure */
   nameKey.xab$b_bln  = XAB$C_KEYLEN;
   nameKey.xab$b_cod  = XAB$C_KEY;
   nameKey.xab$b_dtp  = XAB$C_STG;
   nameKey.xab$b_ref  = 0;              /* Key zero */
   nameKey.xab$l_knm  = (char *) &nameKeyName; /* Key name */
   nameKey.xab$l_nxt  = (char *) &phoneKey;    /* Next XAB in chain */
   /*
      The next two fields describe the section of the record that contains the
      key.
   */
   nameKey.xab$w_pos0 = offsetof(struct phone_r, name);
   nameKey.xab$b_siz0 = NAME_SIZE;

   /* Init XABKEY to define key for phone key */
   phoneKey = cc$rms_xabkey;		/* Initialise XABKEY structure */
   phoneKey.xab$b_bln  = XAB$C_KEYLEN;
   phoneKey.xab$b_cod  = XAB$C_KEY;
   phoneKey.xab$b_dtp  = XAB$C_STG;
   phoneKey.xab$b_ref  = 1;              /* Key one */
   phoneKey.xab$l_knm  = (char *) &phoneKeyName;
   phoneKey.xab$l_nxt  = 0;
   phoneKey.xab$w_pos0 = offsetof(struct phone_r, phone);
   phoneKey.xab$b_siz0 = PHONE_SIZE;


   /*
      Init NAM block just for good file I/O error reporting. We won't use it
      though!
   */

   nam = cc$rms_nam;
   fab.fab$l_nam = &nam;
   nam.nam$b_rss = sizeof( resultantFileName );
   nam.nam$l_rsa = (char *) &resultantFileName;
   nam.nam$b_ess = sizeof( expandedFileName );
   nam.nam$l_esa = (char *) &expandedFileName;
   status = sys$create( &fab );
   if (!(status&SS$_NORMAL))
      return( status );

   rab = cc$rms_rab;                    /* initialise the RAB */
   rab.rab$b_mbf = 127;
   rab.rab$b_mbc = 127;
   rab.rab$l_rop = RAB$M_WBH|RAB$M_RAH;
   rab.rab$l_fab = &fab;
   connectStatus = sys$connect( &rab );
   if (!(connectStatus&SS$_NORMAL)) {
      status = connectStatus;
      sys$close( &fab );
   }
   return( status );
}

/*---- Write a record to the file --------------------------------------------*/
int PutRecord( char *name, char *phone )
{
   long int status;
   struct phone_r phoneRecord;
/* End of declarations ... */

   strncpy( phoneRecord.name,  name,  sizeof(phoneRecord.name) );
   strncpy( phoneRecord.phone, phone, sizeof(phoneRecord.phone) );
   rab.rab$w_rsz = sizeof( phoneRecord );
   rab.rab$l_rbf = (char *) &phoneRecord;
   rab.rab$b_rac = RAB$C_KEY;
   rab.rab$l_rop |= RAB$M_UIF;

   status = sys$put( &rab );

   return( status );
}

/*---- Look a record up by name ----------------------------------------------*/
int GetRecord( char *name, struct phone_r *phoneRecord )
{
   long int status;
/* End of declarations ... */

   rab.rab$w_usz = sizeof( *phoneRecord );
   rab.rab$l_ubf = (char *) phoneRecord;
   rab.rab$b_ksz = strlen( name );
   rab.rab$l_kbf = (char *) name;
   rab.rab$b_krf = 0;
   rab.rab$b_rac = RAB$C_KEY;
   rab.rab$l_rop |= RAB$M_UIF;

   status = sys$get( &rab );

   return( status );
}

/*---- Main Program starts here ----------------------------------------------*/
int main( int argc, char *argv[] )
{
   long int status;
   struct phone_r phoneEntry;
/* End of declarations ... */

   printf("Creating phone.dat ...\n");
   status = CreatePhoneFile("phone.dat");
   if (!(status&SS$_NORMAL)) lib$signal( status );

   printf("Add record NEILL - 555 555 1417\n");
   status = PutRecord ("NEILL", "555 555 1417");
   if (!(status&SS$_NORMAL)) lib$signal( status );

   printf("Add record KARA - 555 555 6506\n");
   status = PutRecord ("KARA", "555 555 6506");
   if (!(status&SS$_NORMAL)) lib$signal( status );

   printf("Look up record for KARA\n");
   status = GetRecord ("KARA", &phoneEntry);
   if (!(status&SS$_NORMAL)) {
      lib$signal( status );
   } else {
      /* The fields are fixed width and need not end in a null character, */
      /* so limit how much of each one printf may read                     */
      printf("Found %.*s - %.*s\n",
             (int)sizeof(phoneEntry.name), phoneEntry.name,
             (int)sizeof(phoneEntry.phone), phoneEntry.phone );
   }

   status = ClosePhoneFile();
   if (!(status&SS$_NORMAL)) lib$signal (status);

   exit(EXIT_SUCCESS);
}
