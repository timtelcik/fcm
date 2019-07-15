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

/* OUTPUT.C
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
*  OUTPUT ROUTINES                                                       *
*                                                                        *
*  Written by Tim Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose: Contains output routines for Falcon Contour Map.             *
*                                                                        *
*  Routines Included                                                     *
*  -----------------                                                     *
*  Display_contour                                                       *
*  Display_network                                                       *
*  Display_tin_edges                                                     *
*  Display_tin_topology                                                  *
*  Display_title                                                         *
*  Save_contour                                                          *
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

/* INCLUDE FALCON CONSTANTS HEADER */
#include "const.h"

/* INCLUDE FALCON TYPES HEADER */
#include "types.h"

/* INCLUDE FALCON FUNCTION PROTOTYPES HEADER */
#include "falcon.h"

/* INCLUDE FALCON GRAPHICS DISPLAY HEADER */
#include "display.h"


/*************************************************************************
*                        GLOBAL VARIABLE DECLARATIONS                    *
*************************************************************************/

extern TIN_EDGE edges[MAX_EDGES+1];     /* array of TIN edges */
extern INDEX first_edge;		/* index of last edge */
extern INDEX last_edge;		        /* index of last edge */
extern TIN_POINT points[MAX_POINTS+1];  /* array of TIN points */
extern INDEX first_pt_id;               /* index to first TIN point */
extern INDEX last_pt_id;                /* index to last TIN point */
extern POINT contour[MAX_CONT_PTS];     /* (x,y,z) pts for a contour */
extern INDEX start_seg_one,             /* start of first line segment */
	     end_seg_one;               /* end of second line segment */
extern INDEX start_seg_two,             /* start of second line segment */
	     end_seg_two;               /* end of second line segment */


/*************************************************************************
*                        START OF FALCON OUTPUT ROUTINES                 *
*************************************************************************/

void Display_contour( void )
/*************************************************************************
*  Function: Display_contour                                             *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Displays the current contour on the screen.                           *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  check if there are any points to draw                                 *
*     set contour line to solid                                          *
*     set contour colour to cyan                                         *
*     check if contour is closed                                         *
*        draw a single line segment                                      *
*     otherwise contour is open and contains two segments                *
*        draw second segment                                             *
*        draw first segment                                              *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global:    contour        - current contour                           *
*             start_seg_one  - start of first line segment in contour    *
*             end_seg_one    - end of first line segment in contour      *
*             start_seg_one  - start of second line segment in contour   *
*             end_seg_two    - end of second line segment in contour     *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  Transform, Move_to, Draw_to                                           *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  displays a single contour                                             *
*                                                                        *
*  Note                                                                  *
*  ----                                                                  *
*  If a contour is closed it will have one line segment, but an open     *
*  contour will have two line segments (one from tracking forwards and   *
*  one from tracking backwards).                                         *
*************************************************************************/
{

INDEX i;      /* index to contour */
REAL nx,ny;   /* normalized x,y */

/* set contour line to solid */
Set_linestyle(3);
/* set contour colour to cyan */
Set_colour(CYAN);

/* check if contour is closed */
if ( start_seg_two == NO_SEGMENT ) {
 /* draw a single line segment */
 Transform(contour[start_seg_one].x,contour[start_seg_one].y,&nx,&ny);
 Move_to(nx,ny);
 for (i = start_seg_one+1; i <= end_seg_one; i++) {
      Transform(contour[i].x,contour[i].y,&nx,&ny);
      Draw_to(nx,ny);
      }
}
/* otherwise contour is open and contains two line segments */
else
{
 /* draw second segment */
 Transform(contour[end_seg_two].x,contour[end_seg_two].y,&nx,&ny);
 Move_to(nx,ny);
 for (i = end_seg_two-1; i > end_seg_one; i--) {
      Transform(contour[i].x,contour[i].y,&nx,&ny);
      Draw_to(nx,ny);
      }
 /* draw first segment */
 for (i = start_seg_one; i <= end_seg_one; i++) {
      Transform(contour[i].x,contour[i].y,&nx,&ny);
      Draw_to(nx,ny);
      }

} /* end if-else */

} /* -- END OF FUNCTION -- */


void Display_network( void )
/*************************************************************************
*  Function: Display_network                                             *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Display the triangles composing the TIN. This also involved checking  *
*  which neighbours had already been visited so that a line was only     *
*  drawn once.                                                           *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  display edges with a dotted line                                      *
*  display TIN in light gray                                             *
*  initialise current tin point                                          *
*  while not at end of TIN points connect points with their neighbours   *
*        flag the current point as visited                               *
*        initialise neighbour pointer to first neighbour                 *
*        repeat while not at end of neighbour list                       *
*            get the neighbour's id                                      *
*            check if the neighbour point has not been visited and does  *
*             not point outside TIN                                      *
*                 current TIN point to its neighbour                     *
*               draw a line from the current point to its neighbour      *
*            goto next neighbour                                         *
*  goto next TIN point in array                                          *
*  reset visited flags on all TIN points                                 *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global:    first_pt_id - index of first point's id                    *
*             points      - array of TIN points                          *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  Transform, Move_to, Draw_to                                           *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  displays the TIN on the monitor                                       *
*************************************************************************/
{

REAL nx,ny;              /* normalized (x,y) point */
BOOLEAN found_pt,        /* flag for whether a point has been found */
       end_of_nbrs;      /* flag for whether at end of neighbour list */
INDEX pt_id;             /* current points's id */
INDEX nbr_id;            /* current neighbour's id */
TIN_NBR_PTR nbr;         /* pointer to current neighbour  */


/* display edges with a dotted line */
Set_linestyle(1);
/* display TIN in light gray */
Set_colour(WHITE);

/* initialise current tin point */
pt_id = first_pt_id;
/* while not at end of TIN points connect points with their neighbours */
while (pt_id <= last_pt_id) {

     /* flag the current point as visited */
     points[pt_id].visited = TRUE;
     /* initialise neighbour pointer to first neighbour */
     nbr = points[pt_id].first_nbr;
     /* repeat while not at end of neighbour list */
     do {
         /* get the neighbour's id */
         nbr_id = nbr->nbrid;
         /* check if the neighbour point has not been visited and does
               not point outside TIN */
         if (!points[nbr_id].visited && nbr_id != OUTSIDE_TIN) {

            /* draw a line from the current point to its neighbour */
            Transform(points[pt_id].coord.x, points[pt_id].coord.y,
                      &nx,&ny);
            Move_to(nx,ny);
            Transform(points[nbr_id].coord.x, points[nbr_id].coord.y,
                      &nx,&ny);
            Draw_to(nx,ny);

         } /* end if */
         /* goto next neighbour */
         nbr = nbr->next;
     } while (nbr != NULL);

/* goto next TIN point in array */
pt_id++;
} /* end while pt_id != NULL */

/* reset visited flags on all TIN points */
for (pt_id = first_pt_id; pt_id <= last_pt_id; pt_id++)
    points[pt_id].visited = FALSE;

} /* -- END OF FUNCTION -- */


/* IF DEBUG IS ON (i.e. DEBUG = 1) COMPILE THE FOLLOWING LINES */
#if DEBUG

void Display_tin_edges( void )
/*************************************************************************
*  Function: Display_tin_edges                                           *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Displays a list of TIN edges by showing the id and z coordinate of    *
*  the first (v1) and second (v2) vertex on the edge                     *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  loop through TIN edges                                                *
*       display edge vertex id's with heights and active flag            *
*                                                                        *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global: edges - array of TIN edges                                    *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  displays TIN edges to monitor                                         *
*************************************************************************/
{

INDEX i;   /* index for edges */

printf("\n\n TIN EDGES\n\n");
printf(" ID (Z)      ID (Z)      ACTIVE\n");
printf(" ----------------------------------------------------------\n");
/* loop through TIN edges */
for (i = 0; i <= last_edge; i++)
    /* display edge vertex id's with heights and active flag */
    printf(" %d (%6.2f)  %d (%6.2f)  %d\n",
           edges[i].v1.id,edges[i].v1.coord.z,
           edges[i].v2.id,edges[i].v2.coord.z,
           edges[i].active);

} /* -- END OF FUNCTION -- */


void Display_tin_topology( void )
/*************************************************************************
*  Function: Display_tin_topology                                        *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Displays a table of the TIN point topology listing for each point     *
*  an (x,y,z) coordinate and a list of neighbours                        *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  get the first point's id                                              *
*  display header info.                                                  *
*  while not at end of points display point and neighbour info.          *
*     display the point's id                                             *
*     display the point's coordinates                                    *
*     get the first neighbour for this point                             *
*     loop through all neighbours and display their id's                 *
*     goto next point in array                                           *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global: points      - array containing TIN points                     *
*          first_pt_id - index to id of first point                      *
*          last_pt_id  - index to id of last point                       *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  displays TIN topology to monitor                                      *
*************************************************************************/
{

INDEX pt_id;       /* id of point */
TIN_NBR_PTR nbr;   /* pointer to a neighbour */

printf("\n\n TOPOLOGY FOR TIN POINTS\n\n");
/* get the first point's id */
pt_id = first_pt_id;
/* display header info. */
printf(" ID  COORD (X,Y,Z)            NEIGHBOURS\n");
printf(" ----------------------------------------------------------\n");
/* while not at end of points display point and neighbour info. */
while (pt_id <= last_pt_id) {

     /* display the point's id */
     printf(" %d   ",pt_id);

     /* display the point's coordinates */
     printf("(%6.2f,%6.2f,%6.2f)  ",
             points[pt_id].coord.x,points[pt_id].coord.y,
             points[pt_id].coord.z);

     /* get the first neighbour for this point */
     nbr = points[pt_id].first_nbr;
     /* loop through all neighbours and display their id's */
     while (nbr != NULL) {
           printf(" %d ",nbr->nbrid);
           nbr = nbr->next;
     } /* end while */
     printf("\n");

     /* goto next point in array */
     pt_id++;

} /* end while */

} /* -- END OF FUNCTION -- */

#endif
/* END IF CHECK FOR DEBUGGING AND CONDITIONAL COMPILATION */


void Display_title( void )
/*************************************************************************
*  Function: Display_title                                               *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Displays the Falcon contour map title message.                        *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  clear the screen                                                      *
*  display title                                                         *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  none                                                                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  clrscr                                                                *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  displays title message                                                *
*************************************************************************/
{

/* clear the screen */
clrscr();
/* display title */
printf("\t\t\t================================\n");
printf("\t\t\t Falcon Contour Map Version 1.0 \n");
printf("\t\t\t Copyright (c) 1991  Tim Telcik \n");
printf("\t\t\t================================\n");

} /* -- END OF FUNCTION -- */


void Save_contour( FILE *cont_file )
/*************************************************************************
*  Function: Save_contour                                                *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Saves the contour's (x,y,z) data points to a file.                    *
*                                                                        *
*  The format of saved data is:                                          *
*                                                                        *
*    x1,y1,z                                                             *
*    x2,y2,z                                                             *
*       .                                                                *
*       .                                                                *
*       .                                                                *
*    xn,yn,z                                                             *
*    -1                                                                  *
*                                                                        *
*    where (x1,y1) to (xn,yn) are the points on a contour at height 'z'  *
*          -1                 is an end of contour marker                *
*                                                                        *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  check if there are any points to write                                *
*     check if contour defines a peak                                    *
*     otherwise contour is closed or open                                *
*         check if contour is closed                                     *
*            write a single line segment                                 *
*         otherwise contour is open and contains two line segments       *
*             write second line segment                                  *
*             write first line segment                                   *
*     output an end of contour marker                                    *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global:    contour        - current contour                           *
*             start_seg_one  - start of first line segment in contour    *
*             end_seg_one    - end of first line segment in contour      *
*             start_seg_one  - start of second line segment in contour   *
*             end_seg_two    - end of second line segment in contour     *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  saves contour data to a file                                          *
*                                                                        *
*  Note                                                                  *
*  ----                                                                  *
*  If a contour is closed it will have one line segment, but an open     *
*  contour will have two line segments (one from tracking forwards and   *
*  one from tracking backwards).                                         *
*************************************************************************/
{

INDEX i;         /* index for contour */

/* check if contour defines a peak */
if ( contour[0].x == contour[1].x &&
    contour[0].y == contour[1].y &&
    contour[0].z == contour[1].z )
   fprintf(cont_file,"%.2lf %.2lf %.2lf\n",
                     contour[0].x,contour[0].y,contour[0].z);
/* otherwise contour is closed or open */
else {
   /* check if contour is closed */
   if ( start_seg_two == NO_SEGMENT ) {
      /* write a single line segment */
      for (i = start_seg_one; i <= end_seg_one; i++)
           fprintf(cont_file,"%.2lf %.2lf %.2lf\n",
                      contour[i].x,contour[i].y,contour[i].z);
    }
    /* otherwise contour is open and contains two line segments */
    else
    {
       /* write second line segment */
       for (i = end_seg_two; i > end_seg_one; i--)
            fprintf(cont_file,"%.2lf %.2lf %.2lf\n",
                       contour[i].x,contour[i].y,contour[i].z);
       /* write first line segment */
       for (i = start_seg_one; i <= end_seg_one; i++)
            fprintf(cont_file,"%.2lf %.2lf %.2lf\n",
                       contour[i].x,contour[i].y,contour[i].z);
    } /* end if closed contour else open contour */
} /* end else contour is closed or open */

/* output an end of contour marker */
fprintf(cont_file,"%d\n",END_CONTOUR);

} /* -- END OF FUNCTION -- */

/*************************************************************************
*                        END OF FALCON OUTPUT ROUTINES                   *
*************************************************************************/

