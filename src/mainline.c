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

/* MAINLINE.C
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
*  MAINLINE                                                              *
*                                                                        *
*  Written by Tim Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Contains the mainline which drives the Falcon contour routines.       *
*  Falcon Contour Map generates contours over a Triangulated Irregular   *
*  Network (TIN), outputs the contours to a graphics terminal and can    *
*  save contour data to a file for further processing by different       *
*  mapping packages.                                                     *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  repeat contouring process until user decides to quit                  *
*     display title message                                              *
*     open the TIN file                                                  *
*     setup TIN topology in memory                                       *
*     close the TIN file                                                 *
*     create and sort the TIN edges                                      *
*     set window to min and max (x,y) coordinates of TIN                 *
*     set viewport to allow labelling around window                      *
*     display memory info. to screen                                     *
*     if debugging then display TIN topology and edges                   *
*     repeat while the user wants to contour the current TIN             *
*        get contour information                                         *
*        get smoothing factor from user                                  *
*        prompt user to save contours to a data file                     *
*        open a contour file if required                                 *
*        prompt user to display TIN while contouring                     *
*        activate graphics mode                                          *
*        display border and border coordinates on screen                 *
*        display contour info. on screen                                 *
*        display the TIN on the screen if required                       *
*        get start time                                                  *
*        generate contours within contour bounds                         *
*        get ending time                                                 *
*        prompt and wait for user to exit contour display                *
*        deactivate graphics mode                                        *
*         check if contour file needs to be closed                       *
*         inform user of the time taken to contour TIN                   *
*         prompt user to contour the same TIN again                      *
*      free all memory used by neighbours in neighbour lists             *
*      prompt user to contour another TIN                                *
*   display exiting message                                              *
*                                                                        *
*   Calls                                                                *
*   -----                                                                *
*   Display_title                                                        *
*   Open_tin_file                                                        *
*   Setup_tin                                                            *
*   Create_edges                                                         *
*   Quicksort                                                            *
*   Set_window                                                           *
*   Set_viewport                                                         *
*   Display_tin_topology                                                 *
*   Display_tin_edges                                                    *
*   Get_contour_info                                                     *
*   Get_smoothing_factor                                                 *
*   Prompt_reply                                                         *
*   Open_cont_file                                                       *
*   Activate_graphics                                                    *
*   Set_colour                                                           *
*   Draw_border                                                          *
*   Draw_border_coords                                                   *
*   Draw_cont_info                                                       *
*   Display_network                                                      *
*   Generate_contours                                                    *
*   Graphics_pause                                                       *
*   Deactivate_graphics                                                  *
*   Free_memory                                                          *
*                                                                        *
*   Note                                                                 *
*   ----                                                                 *
*   A POINT topology is used to represent the TIN as seen below:         *
*                                                                        *
*          ID  COORD (X,Y,Z)          NEIGHBOURS                         *
*          -------------------------------------                         *
*          1  (  0.00, 10.00,105.00)  7 4 2 -1                           *
*          2  ( 35.00, 10.00,110.00)  4 5 3 1                            *
*          3  ( 80.00,  0.00,112.00)  6 2 -1 5                           *
*          .      .       .     .     . . .                              *
*          .      .       .     .     . . .                              *
*          .      .       .     .     . . .                              *
*          N   (xn,     yn,     zn)   . . .                              *
*                                                                        *
*   Every point has an identification number, an (x,y,z) coordinate and  *
*   a list of neighbours which are sorted clockwise starting from the    *
*   north.                                                               *
*   -1 represents a point on the edge of the TIN.                        *
*                                                                        *
*   The POINT topology is read from an ASCII data file.                  *
*   The file format is shown below:                                      *
*                                                                        *
*   id1 x1 y1 z1 nbr1 nbr2 ... nbrn<eoln>                                *
*   id2 x2 y2 z2 nbr1 nbr2 ... nbrn<eoln>                                *
*               .                                                        *
*               .                                                        *
*               .                                                        *
*   idn xn yn zn nbr1 nbr2 ... nbrn<eoln>                                *
*   <eof>                                                                *
*                                                                        *
*   where id    is the TIN point's id number                             *
*         x,y,z is the TIN point's spatial coordinate                    *
*         nbr   is the id number for a TIN point's neighbour             *
*                                                                        *
*  Important !!!                                                         *
*  -------------                                                         *
*  If the TIN point topology is wrong the following may happenn:         *
*  (a) the program will crash because of array overflows                 *
*  (b) the program will become stuck in an infinte loop                  *
*  (c) the contours will be utterly stuffed !                            *
*************************************************************************/

/*************************************************************************
*                           INCLUDE HEADER FILES                         *
*************************************************************************/

/* INCLUDE STANDARD HEADERS */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
// TODO: Review POSIX header usage
//       http://en.wikipedia.org/wiki/Unistd.h
#include <unistd.h>

/* INCLUDE FALCON CONSTANTS HEADER */
#include "const.h"

/* INCLUDE FALCON TYPES HEADER */
#include "types.h"

/* INCLUDE FALCON FUNCTION PROTOTYPES HEADER */
#include "falcon.h"

/* INCLUDE FALCON GRAPHICS DISPLAY HEADER */
#include "display.h"

#define VIEW_WAIT_DURATION 3
// #define VIEW_WAIT_DURATION 5
// #define VIEW_WAIT_DURATION 20


/*************************************************************************
*                          GLOBAL VARIABLE DECLARATIONS                  *
*************************************************************************/

TIN_EDGE edges[MAX_EDGES+1];       /* array of TIN edges */
INDEX first_edge;                  /* index to first TIN edge */
INDEX last_edge;		   /* index to last TIN edge */
TIN_POINT points[MAX_POINTS+1];    /* array of TIN points */
INDEX first_pt_id;                 /* index to first TIN point */
INDEX last_pt_id;                  /* index to last TIN point */
POINT contour[MAX_CONT_PTS+1];     /* (x,y,z) pts for a contour */
INDEX start_seg_one,               /* start of first line segment */
      end_seg_one;                 /* end of first line segment */
INDEX start_seg_two,               /* start of second line segment */
      end_seg_two;                 /* end of second line segment */


/*************************************************************************
*			  START OF FALCON MAINLINE                       *
*************************************************************************/

// void main()
// int main()
int main(int argc, const char * argv[])
{

double contour_interval;	 /* contour interval */
double lower_contour,        /* lower contour bound */
     upper_contour;        /* upper contour bound */
FILE *tin_file;              /* pointer to tin file */
FILE *cont_file;             /* pointer to contour file */
double wxmin,wymin;          /* lower left coords of world window */
double wxmax,wymax;          /* upper right coords of world window */
double zmin, zmax;           /* min, max of contour range */
double adjust;               /* edge cut adjustment factor */
double sample;               /* sampling interval for bicubic spline */
BOOLEAN display_tin;         /* whether to display TIN */
BOOLEAN save_cont;           /* whether to save contour data */
BOOLEAN same_tin;            /* whether to contour the same tin */
BOOLEAN another_tin;         /* whether to contour another TIN */
long start_time, end_time;   /* starting, ending time for contouring */
long time_taken;             /* time taken for contouring */


/* repeat contouring process until user decides to quit */
do {

 // display title message
 Display_title();

 // open the TIN file
 Open_tin_file(&tin_file);

 // setup TIN topology in memory
 printf("\nSetting up the TIN point topology ...\n");
 Setup_tin(tin_file,&wxmin,&wymin,&wxmax,&wymax,&zmin,&zmax);

 // close the TIN file
 fclose(tin_file);

 // create and sort the TIN edges
 printf("\nCreating and sorting the TIN edges ...\n\n");
 Create_edges();
 Quicksort(&edges[0],0,last_edge);

 // set window to min and max (x,y) coordinates of TIN
 Set_window(wxmin,wymin,wxmax,wymax);
 // set viewport to allow labelling around window
 Set_viewport(vpxmin,vpymin,vpxmax,vpymax);

 // display memory info. to screen
 // printf("Available memory : %ul\n",coreleft());
 printf("Available memory : TODO \n");

 // if debugging then display TIN topology and edges
#if DEBUG
     Display_tin_topology();
     Display_tin_edges();
#endif

 // repeat while the user wants to contour the current TIN
 do {

    // get contour information
    Get_contour_info( zmin, zmax, &lower_contour, &upper_contour,
		      &contour_interval);

    // get smoothing information from the user
    Get_smoothing_info( &adjust, &sample );

    // prompt user to save contours to a data file
    Prompt_reply("Do you want to save the contours to a data file",
		 NO,&save_cont);

    // open a contour file if required
    if ( save_cont == YES ) {
       Open_cont_file(&cont_file);
    }

    // prompt user to display TIN while contouring
    Prompt_reply("Display the TIN while contouring",NO,&display_tin);

    //
    // begin render loop
    //

    // activate graphics mode
    Activate_graphics();

    /* display border and border coordinates on screen */
    // Set_colour(WHITE);
    Set_colour(BLUE);
    Draw_border();
    Draw_border_coords(wxmin,wymin,wxmax,wymax);

    /* display contour info. on screen */
    // Set_colour(WHITE);
    Set_colour(BLUE);
    Draw_cont_info(lower_contour, upper_contour, contour_interval);

    /* display the TIN on the screen if required */
    if ( display_tin == YES ) {
       Display_network();

       // flush graphics to screen
       // Flush_graphics();
    }

    /* get start time */
    time(&start_time);

    // TODO: generate contours before rendering to screen


    printf("BEGIN generate contours ... \n");

    /* generate contours within contour bounds */
    Generate_contours( lower_contour, upper_contour, contour_interval,
		       save_cont, cont_file, adjust, sample );

    printf("END generate contours \n");


    // flush graphics to screen
    Flush_graphics();


    /* get ending time */
    time(&end_time);


    printf("BEGIN polling loop ...");

    /* prompt and wait for user to exit contour display */
    // Set_colour(WHITE);
    Set_colour(CYAN);
	Draw_text( 0.1, 0.1, "** Contouring Finished. Press ESCape. **" );
    // Graphics_pause();
    while (Is_graphics_active()) {
        Poll_events();
    }

    printf("END polling loop ...");

    /* deactivate graphics mode */
    Deactivate_graphics();

    //
    // end render loop
    //

    /* check if contour file needs to be closed */
    if ( save_cont == YES ) {
       fclose(cont_file);
    }

    /* inform user of the time taken to contour TIN */
    time_taken=difftime(end_time,start_time);
    printf("\nTime taken to contour TIN : %ld seconds\n",time_taken);

    /* prompt user to contour the same TIN again */
    Prompt_reply("Do you want to contour this TIN again",NO,
		 &same_tin);

 } while ( same_tin == YES );

 /* free all memory used by neighbours in neighbour lists */
 printf("\nClearing memory ...\n");
 Free_memory();

 /* prompt user to contour another TIN */
 Prompt_reply("Do you want to contour another TIN",NO,&another_tin);

} while ( another_tin == YES );

/* display exiting message */
// printf("\n\nFalcon Contour Map 1.0\nEnd of processing.\n\n");
printf("\n\n%s\nEnd of processing.\n\n",FALCON_VERSION_LABEL);

}

/*************************************************************************
*			     END OF FALCON MAINLINE                      *
*************************************************************************/

