/**
 * Falcon Contour Map
 *
 * Copyright (C) 1991-present Tim Telcik
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If
 * not, see <http://www.gnu.org/licenses/>.
 */

/* INPUT.C
**************************************************************************
*  FALCON CONTOUR MAP VERSION 1.0                     2nd Semester 1991  *
*  Copyright (c) 1991 Tim Telcik                                         *
*                                                                        *
*  Written by Tim Telcik (891892H)                                       *
*  School of Computing Science                                           *
*  Curtin University of Technology                                       *
*                                                                        *
*  For: Computing Project 394                                            *
*       Bachelor of Applied Science (Computing Science)                  *
**************************************************************************

**************************************************************************
*  FALCON CONTOUR MAP VERSION 1.0                                        *
*  INPUT ROUTINES                                                        *
*                                                                        *
*  Written by Tim Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose: Contains input routines for Falcon Contour Map.              *
*                                                                        *
*  Routines Included                                                     *
*  -----------------                                                     *
*  Eoln                                                                  *
*  Get_contour_info                                                      *
*  Get_smoothing_info                                                    *
*  Open_cont_file                                                        *
*  Open_tin_file                                                         *
*  Prompt_reply                                                          *
*  Prompt_value                                                          *
*************************************************************************/

/*************************************************************************
*                          INCLUDE HEADER FILES                          *
*************************************************************************/

/* INCLUDE STANDARD HEADERS */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

/* INCLUDE FALCON CONSTANTS HEADER */
#include "const.h"

/* INCLUDE FALCON TYPES HEADER */
#include "types.h"

/* INCLUDE FALCON FUNCTION PROTOTYPES HEADER */
#include "falcon.h"

/* INCLUDE FALCON GRAPHICS DISPLAY HEADER */
#include "display.h"


/*************************************************************************
*                       START OF FALCON INPUT ROUTINES                   *
*************************************************************************/

int Eoln( FILE *fp )
/*************************************************************************
*  Function: Eoln                                                        *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Checks for a carriage return (End Of LiNe)                            *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  get character from keyboard and wait until CR (\n)                    *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: fp - pointer to input device (i.e. keyboard)               *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Returns: character read from keyboard                                 *
*************************************************************************/
{

int c;    /* ASCII code for a character */

/* get char from keyboard and wait until CR (\n) */
c=getc(fp);
ungetc(c,fp);
return(c==CR);

} /* -- END OF FUNCTION -- */


void Get_contour_info( REAL zmin, REAL zmax,
		       REAL *lower_contour, REAL *upper_contour,
		       REAL *contour_interval )
/*************************************************************************
*  Function: Get_contour_info                                            *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Prompts the user to enter contour ranges and contour interval or use  *
*  the defaults.                                                         *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  initialise range of contours to be generated                          *
*  display current contour info.                                         *
*  get the new lower contour bound                                       *
*  get the new upper contour bound                                       *
*  get the new contour interval                                          *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: zmin - minimum z value of contour range                    *
*             zmax - maximum z value of contour range                    *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Parameter: lower_contour    - min. contour range                      *
*             upper_contour    - max. contour range                      *
*             contour_interval - vertical distance between contours      *
*************************************************************************/
{

/* initialise range of contours to be generated */
*lower_contour = zmin;
*upper_contour = zmax;
*contour_interval = 1;

/* display current contour info. */
printf("\nCurrent lower contour bound %.2f\n",*lower_contour);
printf("Current upper contour bound %.2f\n",*upper_contour);
printf("Current contour interval %.2f\n",*contour_interval);

/* get the new lower contour bound */
printf("\n");
Prompt_value("Please enter the new lower contour bound",
	     *(&lower_contour),*lower_contour,*upper_contour);

/* get the new upper contour bound */
Prompt_value("Please enter the new upper contour bound",
	     *(&upper_contour),*lower_contour,*upper_contour);

/* get the new contour interval */
Prompt_value("Please enter the new contour interval",
	     *(&contour_interval),MIN_CI,MAX_CI);

} /* -- END OF FUNCTION -- */


void Get_smoothing_info( REAL *adjust, REAL *sample )
/*************************************************************************
*  Function: Get_smoothing_info                                          *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Prompts the user to enter the smoothing information for contouring    *
*  (i.e. edge cut adjustment factor, and spline sampling interval )      *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  initialise default adjustment factor                                  *
*  prompt user for smoothing factor                                      *
*  check if adjustment factor > 0                                        *
*     initialise default sampling interval                               *
*     prompt user for spline sampling interval                           *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  none                                                                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Parameter: adjust - percentage by which contour cuts are adjusted     *
*             sample - sampling interval for the bi-cubic spline         *
*************************************************************************/
{

printf("\n");
/* initialise default adjustment factor */
*adjust = 0.12;
/* prompt user for adjustment factor */
Prompt_value("Please enter the edge cut adjustment factor (0.0 - 0.5)",
	    &(*adjust), MIN_ADJUST, MAX_ADJUST);

/* check if adjustment factor > 0 */
if ( *adjust > 0 ) {
  printf("\n");
  /* initialise default sampling interval */
  *sample = 3.0;
  /* prompt user for spline sampling interval */
  Prompt_value("Please enter the spline sampling interval (0.1 - 10.0)",
	       &(*sample), MIN_SAMPLE, MAX_SAMPLE);
  } /* end if */

} /* -- END OF FUNCTION -- */


void Open_cont_file( FILE *(*cont_file) )
/*************************************************************************
*  Function: Open_cont_file                                              *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Opens the contour file.                                               *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  initialise                                                            *
*  while the contour file exists request a new name                      *
*        define default contour data file name                           *
*        clear the keyboard buffer                                       *
*        prompt user to enter name of the contour data file              *
*        get name of the contour data file                               *
*        check if user has not added an extension to file name           *
*           add an extension to the file name                            *
*        check if contour file already exists                            *
*           if contour file exists prompt user to overwrite it           *
*        otherwise contour file does not exist so exit loop              *
*  open the contour data file                                            *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  none                                                                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  Eoln                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Parameter: cont_file - pointer to the contour file                    *
*************************************************************************/
{

char cont_filename[30];        /* name of contour data file */
BOOLEAN reply;                 /* user's reply to a query */
BOOLEAN request_again;         /* whether to request contour file
				  name again */

/* initialise */
request_again = TRUE;
/* while the contour file exists request a new name */
while ( request_again ) {
   /* define default contour data file name */
   strcpy(cont_filename,"tin.con");
   /* clear the keyboard buffer */
   fflush(stdin);
   /* prompt user to enter name of the contour data file */
   printf("\nPlease enter the contour file name (.con assumed) [%s] : ",
	  cont_filename);
   /* get name of the contour data file */
   if (!Eoln(stdin))
       fscanf(stdin,"%s",cont_filename);
   while(fgetc(stdin) != CR);
   /* check if user has not added an extension to file name */
   if ( strstr(cont_filename,".con") == NULL )
       /* add an extension to the file name */
       strcat(cont_filename,".con");
   /* check if contour file already exists */
   if ( fopen(cont_filename,"r") != NULL ) {
      /* if contour file exists prompt user to overwrite it */
      printf("\nThat contour file already exists.\n");
      Prompt_reply("Do you want to overwrite it",YES,&reply);
      if ( reply == YES )
	 request_again = FALSE;
      }
   /* otherwise contour file does not exist so exit loop */
   else
       request_again = FALSE;
} /* end while request again */

/* open the contour data file */
*cont_file = fopen(cont_filename,"w");

} /* -- END OF FUNCTION -- */


void Open_tin_file( FILE *(*tin_file) )
/*************************************************************************
*  Function: Open_tin_file                                               *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Opens the TIN data file.                                              *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  prompt user for name of TIN file until a TIN file is found            *
*     prompt user for name of TIN file                                   *
*     check if user has added an extension to the file name              *
	 add an extension to the file name                               *
*     open specified file                                                *
*     check if file does not exist                                       *
*       display error message and prompt user to try again               *
*       if reply is no then exit program                                 *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  none                                                                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  Prompt_reply                                                          *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Parameter: tin_file - pointer to TIN data file                        *
*************************************************************************/
{

char tin_filename[30];                /* name of TIN data file */
BOOLEAN reply;                        /* reply to query */

/* prompt user for name of TIN file until a TIN file is found */
do {
  /* prompt user for name of TIN file */
  printf("\nEnter name of TIN file (.dat assumed) : ");
  scanf("%s",tin_filename);
  /* check if user has not added an extension to the file name */
  if ( strstr(tin_filename,".dat") == NULL )
     /* add extension to file name */
     strcat(tin_filename,".dat");
  /* open specified file */
  *tin_file = fopen(tin_filename,"r");
  /* check if file does not exist */
  if (*tin_file == NULL) {
    /* display error message and prompt user to try again */
    printf("\nUnable to open a TIN file with that name.\n");
    Prompt_reply("Do you want to try a different name",YES,&reply);
    /* if reply is no then exit program */
    if ( reply == NO ) {
       printf("\n\nFalcon Contour Map 1.0\nEnd of processing.\n\n");
       exit(1);
       }
     }
} while ( *tin_file == NULL );

} /* -- END OF FUNCTION -- */


void Prompt_reply( char prompt[MAX_STRING], BOOLEAN default_reply,
		   BOOLEAN *reply )
/*************************************************************************
*  Function: Prompt_reply                                                *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Prompts the user to answer a query with a Y(es) N(o) reply.           *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  repeat while the user has not replied with Y(es) or N(o)              *
*      set temp. reply to default reply                                  *
*      clear the keyboard buffer                                         *
*      display prompt                                                    *
*      get temp. reply from keyboard and convert to upper case           *
*  get reply                                                             *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: prompt        -  message to use as a prompt                *
*             default_reply - reply that is used by default              *
*             reply         - reply to the prompt                        *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Parameter: reply - user's reply to prompt (Y or N)                    *
*************************************************************************/
{

BOOLEAN temp_reply;      /* temporary reply */

printf("\n");
/* repeat while the user has not replied with a YES (y) or NO (n) */
do {
   /* set temp. reply to default reply */
   temp_reply = default_reply;
   /* clear the keyboard buffer */
   fflush(stdin);
   /* display prompt */
   printf("%s [%c] ? ",prompt,temp_reply);
   /* get temp. reply from keyboard and convert to upper case */
   if (!Eoln(stdin)) {
       // temp_reply = tolower(getc(stdin));
       temp_reply = getc(stdin);
   } while(fgetc(stdin) != CR);
} while ( temp_reply != YES && temp_reply != NO );

/* get reply */
*reply = temp_reply;

} /* -- END OF FUNCTION -- */


void Prompt_value( char prompt[MAX_STRING], REAL *value,
		   REAL min_value, REAL max_value )
/*************************************************************************
*  Function: Prompt_value                                                *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Prompts the user to enter a value.                                    *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  clear the keyboard buffer                                             *
*  prompt the user to enter a value until value is inside range          *
*    initialise the temp. value                                          *
*    display prompt                                                      *
*    read temp. value from keyboard                                      *
*    if temp. value outside valid range then display error message       *
*    otherwise assign the temp. value to the input value                 *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: prompt  - message to use as a prompt                       *
*             value - default value                                      *
*             min_value - minimum value which can be entered             *
*             max_value - maximum value which can be entered             *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Parameter: value - value entered by user in response to prompt        *
*************************************************************************/
{

REAL temp_value;     /* temp. value used during input */

/* clear the keyboard buffer */
fflush(stdin);
/* prompt the user to enter a value until value is inside range */
do {
  /* initialise the temp. value */
  temp_value = *value;
  /* display prompt */
  fprintf(stdout,"%s [%.2f] : ",prompt,*value);
  /* read temp. value from keyboard */
  if (!Eoln(stdin))
      fscanf(stdin,"%lf",&temp_value);
  while(fgetc(stdin) != CR);
  /* if temp. value is outside valid range then display error message */
  if ( (temp_value < min_value) || (temp_value > max_value) )
     printf("Sorry, the value must be within the range %.2f to %.2f.\n",
	    min_value,max_value);
  /* otherwise assign the temp. value to the input value */
  else
     *value = temp_value;
} while ( (temp_value < min_value) || (temp_value > max_value) );

} /* -- END OF FUNCTION -- */

/*************************************************************************
*                       END OF FALCON INPUT ROUTINES                     *
*************************************************************************/

