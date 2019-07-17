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

/* TOPOLOGY.C
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
*  TOPOLOGY ROUTINES                                                     *
*                                                                        *
*  Written by Tim Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose: Contains routines for setting up and manipulating the TIN    *
*           point topology in memory.                                    *
*                                                                        *
*  Routines Included                                                     *
*  -----------------                                                     *
*  Add_nbr_to_pt                                                         *
*  Add_pt_to_tin                                                         *
*  Create_edges                                                          *
*  Free_memory                                                           *
*  New_nbr                                                               *
*  Setup_tin                                                             *
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
*                          GLOBAL VARIABLE DECLARATIONS                  *
*************************************************************************/

extern TIN_EDGE edges[MAX_EDGES+1];     /* array of TIN edges */
extern INDEX first_edge;                /* index to first TIN edge */
extern INDEX last_edge;		        /* index to last TIN edge */
extern TIN_POINT points[MAX_POINTS+1];  /* array of TIN points */
extern INDEX first_pt_id;               /* index to first TIN point */
extern INDEX last_pt_id;                /* index to last TIN point */


/*************************************************************************
*                       START OF FALCON TOPOLOGY ROUTINES                *
*************************************************************************/

void Add_nbr_to_pt( INDEX pt_id, INDEX nbr_id )
/*************************************************************************
*  Function: Add_nbr_to_pt                                               *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Adds a neigbour to the specified TIN point.                           *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  if neighbour list is empty then create a new neighbour for            *
*    this point                                                          *
*  otherwise create new neighbour and add it to the neighbour list       *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global:    points - array containing TIN points                       *
*  Parameter: pt_id  - id of TIN point where nbr info is to be added     *
*             nbr_id - id of neighbour to be added                       *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  New_nbr                                                               *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Global:   points - array containing TIN points                        *
*************************************************************************/
{

TIN_NBR_PTR new_nbr;       /* new neighbour */
TIN_NBR_PTR last_nbr;      /* pointer to last neighbour */

/* if neighbour list is empty then create a new neighbour for point */
if (points[pt_id].first_nbr == NULL) {
  new_nbr = New_nbr();
  new_nbr->nbrid = nbr_id;
  new_nbr->next = NULL;
  points[pt_id].first_nbr = new_nbr;
  points[pt_id].last_nbr = points[pt_id].first_nbr;
  }
/* otherwise create new neighbour and add it to the neighbour list */
else {
  last_nbr = points[pt_id].last_nbr;
  new_nbr = New_nbr();
  new_nbr->nbrid = nbr_id;
  last_nbr->next = new_nbr;
  new_nbr->next = NULL;
  points[pt_id].last_nbr = new_nbr;
  }

 } /* -- END OF FUNCTION -- */


void Add_pt_to_tin( INDEX pt_id, REAL x, REAL y, REAL z )
/*************************************************************************
*  Function: Add_pt_to_tin                                               *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Adds a point to the TIN array at the index given by its point id.     *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  insert TIN point into array at the position determined by its id      *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global:    points - array containing TIN points                       *
*  Parameter: pt_id - point id                                           *
*             x,y,z - coordinate of point in world coordinates (WC)      *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Global: points - array containing TIN points                          *
*************************************************************************/
{

/* insert TIN point into array at the position determined by its id */
points[pt_id].coord.x = x;
points[pt_id].coord.y = y;
points[pt_id].coord.z = z;
points[pt_id].first_nbr = NULL;
points[pt_id].last_nbr = NULL;
points[pt_id].visited = FALSE;

} /* -- END OF FUNCTION -- */


void Create_edges( void )
/*************************************************************************
*  Function: Create_edges                                                *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Creates a list of edges from the TIN point topology.                  *
*                                                                        *
*  Algorithm                                                             *
*  ----------                                                            *
*  initialise                                                            *
*  while not at end of points create edges                               *
*    get first vertex on edge                                            *
*    get first neighbour for point                                       *
*    while not at end of neighbour list create edges for point           *
*      check if nbr is not outside TIN                                   *
*         check if height of neighbour is >= height of point             *
*            get second vertex of edge                                   *
*            add edge to edges                                           *
*      goto next neighbour                                               *
*    goto next point in TIN array                                        *
*  decrement index to last edge                                          *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global: points - array containing TIN points                          *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Global: edges - array containing TIN edges                            *
*          first_edge, last_edge - indices to first and last TIN edges   *
*************************************************************************/
{

INDEX i;           /* index for edge array */
INDEX pt_id;       /* current point's id */
INDEX nbr_id;      /* current neighbour's id */
TIN_NBR_PTR nbr;   /* pointer to current neighbour */
TIN_EDGE edge;     /* temp. edge */


/* initialise */
i = 0;
first_edge = 0;
pt_id = first_pt_id;

/* while not at end of points create edges */
while (pt_id <= last_pt_id) {

   /* get first vertex on edge */
   edge.v1.id = pt_id;
   edge.v1.coord = points[pt_id].coord;
   /* get first neighbour for point */
   nbr = points[pt_id].first_nbr;

   /* while not at end of neighbour list create edges for
      current point */
   while (nbr != NULL) {

         /* check if nbr is not outside TIN */
         nbr_id = nbr->nbrid;
         if (nbr_id != OUTSIDE_TIN)
            /* check if height of neighbour is >= height of point */
            if ( points[nbr_id].coord.z >= points[pt_id].coord.z ) {
               /* get second vertex of edge */
               edge.v2.id = nbr_id;
               edge.v2.coord = points[nbr_id].coord;
               edge.active = FALSE;
               /* add edge to edges */
               edges[i] = edge;
               i = i + 1;
            } /* end if */
         /* goto next neighbour */
         nbr = nbr->next;

         } /* end while */

  /* goto next point in TIN array */
  pt_id++;

} /* end while */

/* decrement index to last edge */
last_edge = i-1;

} /* -- END OF FUNCTION -- */


void Free_memory( void )
/*************************************************************************
*  Function: Free_memory                                                 *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Frees the dynamic memory allocated to neighbour lists.                *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  get the id of first pt                                                *
*  while not at end of points free neighbour lists                       *
*     get the first neighbour for this point                             *
*     loop through all neighbours for this point and delete them         *
*     goto next point in array                                           *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global: points - array containing TIN points                          *
*          first_pt_id, last_pt_id - index of first and last TIN points  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  free                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Global: points - array containing TIN points                          *
*************************************************************************/
{

INDEX pt_id;            /* current point's id */
TIN_NBR_PTR nbr;        /* current neighbour */
TIN_NBR_PTR temp_nbr;   /* temp neighbour */


/* get the id of first pt */
pt_id = first_pt_id;

/* while not at end of points free neighbour lists */
while ( pt_id <= last_pt_id ) {

     /* get the first neighbour for this point */
     nbr = points[pt_id].first_nbr;
     /* loop through all neighbours for this point and delete them */
     do {
          temp_nbr = nbr->next;
          free(nbr);
          nbr = temp_nbr;
     } while ( temp_nbr != NULL );

     /* goto next point in array */
     pt_id = pt_id + 1;

} /* end while */

} /* -- END OF FUNCTION -- */


TIN_NBR_PTR New_nbr( void )
/*************************************************************************
*  Function: New_nbr                                                     *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Creates a new neighbour and returns a pointer to it.                  *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  allocate memory for a neighbour record and return its address         *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  none                                                                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  malloc                                                                *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Retunrs: pointer to new neighbour structure                           *
*************************************************************************/
{

/* allocate memory for a neighbour record and return its address */
return (TIN_NBR_PTR) malloc(sizeof(TIN_NBR));

} /* -- END OF FUNCTION -- */


void Setup_tin( FILE *tin_file, REAL *wxmin, REAL *wymin,
		REAL *wxmax, REAL *wymax, REAL *zmin, REAL *zmax )
/*************************************************************************
*  Function: Setup_tin                                                   *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Reads the TIN data file and creates the TIN point topology in memory. *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  initialise                                                            *
*  while not at end of file add points to TIN                            *
*       read line of point & nbr info from the data file                 *
*       get the point's id                                               *
*       check if point id read from file <> last id read from file       *
*        (i.e. prevent point being inserted in topology twice)           *
*           set the last id to the current id                            *
*           get the point's coordinates                                  *
*           add point to the TIN                                         *
*           increment index to last point in TIN                         *
*           check if window and contour bounds need initialising         *
*               initialise minimum and maximum window bounds             *
*               initialise minimum and maximum contour bounds            *
*           otherwise modify window and contour bounds if required       *
*           get the point's neighbours                                   *
*             get neighbour                                              *
*             add neighbour to the point                                 *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: tin_file - pointer to TIN data file                        *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  Add_pt_to_tin                                                         *
*  Add_nbr_to_pt                                                         *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Parameter: wxmin, wymin, wxmax, wymax - World coordinates of world    *
*                                          window                        *
*             zmin, zmax - min and max and contours                      *
*************************************************************************/
{

char buffer[132];               /* buffer for a line of the TIN file */
char *tok;                      /* pointer to character token in buffer */
INDEX pt_id, nbr_id;            /* point id, neighbour id */
INDEX last_pt_added;            /* id of last point added */
REAL x, y, z;                   /* coordinates of point */
BOOLEAN inserting_first_point;  /* whether first point is being inserted */


/* initialise */
first_pt_id = 1;
last_pt_id = first_pt_id;
inserting_first_point = TRUE;
last_pt_added = OUTSIDE_TIN;

/* while not at end of file add points to TIN */
while(!feof(tin_file))
{
    /* read line of point & nbr info from the data file */
    fgets(buffer, 132, tin_file);
    /* get the point's id */
    tok = strtok(buffer," ");
    pt_id = atoi(tok);

    /* check if point id read from file <> last id read from file
       (i.e. prevent point being inserted in topology twice) */
    if ( pt_id != last_pt_added ) {

        /* set the last id to the current id */
        last_pt_added = pt_id;
        /* get the point's coordinates */
        tok = strtok(NULL," ");
        x = atof(tok);
        tok = strtok(NULL," ");
        y = atof(tok);
        tok = strtok(NULL," ");
        z = atof(tok);
        /* add point to TIN topology */
        Add_pt_to_tin(pt_id,x,y,z);
        /* increment index to last point in TIN */
        last_pt_id++;

        /* check if window and contour bounds need initialising */
        if ( inserting_first_point ) {
            /* initialise minimum and maximum window bounds */
            *wxmin = x;
            *wymin = y;
            *wxmax = x;
            *wymax = y;
            /* initialise minimum and maximum contour bounds */
            *zmin = z;
            *zmax = z;
            inserting_first_point = FALSE;
            }
        /* otherwise modify window and contour bounds if required */
        else {
            if (x < *wxmin) *wxmin = x;
            if (x > *wxmax) *wxmax = x;
            if (y < *wymin) *wymin = y;
            if (y > *wymax) *wymax = y;
            if (z < *zmin) *zmin = z;
            if (z > *zmax) *zmax = z;
            }

        /* get the point's neighbours */
        while((tok=strtok(NULL," ")) != NULL)
        {
          /* get neighbour */
          nbr_id = atoi(tok);
          /* add neighbour to the point */
          Add_nbr_to_pt(pt_id,nbr_id);
        } /* end while */

   } /* end if check for last_pt_added */

} /* end while */

/* decrement index to last point in TIN */
last_pt_id--;

} /* -- END OF FUNCTION -- */

/*************************************************************************
*                      END OF FALCON TOPOLOGY ROUTINES                   *
*************************************************************************/

