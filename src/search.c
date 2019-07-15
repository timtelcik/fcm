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

/* SEARCH.C
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
*  SEARCH ROUTINES                                                       *
*                                                                        *
*  Written by Tim Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose: Contains searching routines for Falcon Contour Map.          *
*                                                                        *
*  Routines Included                                                     *
*  -----------------                                                     *
*  Find_edge                                                             *
*  Find_starting_edge                                                    *
*  Find_vertex                                                           *
*  Reset_edge_flags                                                      *
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

extern TIN_EDGE edges[MAX_EDGES+1];       /* array of TIN edges */
extern INDEX first_edge;                  /* index of first TIN edge */
extern INDEX last_edge;		          /* index of last TIN edge */
extern TIN_POINT points[MAX_POINTS+1];    /* array of TIN points */
extern INDEX first_pt_id;                 /* index to first TIN point */
extern INDEX last_pt_id;                  /* index to last TIN point */


/*************************************************************************
*                    START OF FALCON SEARCHING ROUTINES                  *
*************************************************************************/

INDEX Find_edge( TIN_EDGE edge, BOOLEAN *found )
/*************************************************************************
*  Function: Find_edge                                                   *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Locates an edge in the edge list.                                     *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  perform binary search until an edge with required height on first     *
*    vertex is found                                                     *
*  perform a linear search between the low and high array positions for  *
*   required edge                                                        *
*  return position of edge in edge list                                  *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global:    first_edge, last_edge - indices to first, last TIN edges   *
*  Parameter: edge - edge required to find                               *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Parameter: found - TRUE if edge found, otherwise false                *
*  Retunrs:   index position of located edge                             *
*************************************************************************/
{

INDEX i;               /* index for linear search */
INDEX low, mid, high;  /* index positions for binary search */
BOOLEAN exit;          /* exit flag */


/* perform binary search until an edge with required height on first
   vertex is found */
exit = FALSE;
low = first_edge;
high = last_edge;
while ( low <= high && !exit ) {
      mid = (low+high)/2;
      if ( edge.v1.coord.z < edges[mid].v1.coord.z )
         high = mid - 1;
      else if ( edge.v1.coord.z > edges[mid].v1.coord.z )
           low = mid + 1;
      else
           exit = TRUE;
      }

/* perform a linear search between the low and high array positions for
    required edge */
*found = FALSE;
i = low;
/* while not outside range and edge not found */
while ( i <= high && !*found ) {
      /* check if first and second vertices match */
      if ( edges[i].v1.id == edge.v1.id &&
           edges[i].v2.id == edge.v2.id )
            /* edge has been found */
        *found = TRUE;
      /* otherwise goto next edge */
      else
          i++;
}

/* return position of edge in edge list */
return i;

} /* -- END OF FUNCTION -- */


TIN_EDGE Find_starting_edge( REAL contour_height, BOOLEAN *found )
/*************************************************************************
*  Function: Find_starting_edge                                          *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Finds and returns an edge in the edge list which could be crossed by  *
*  the contour height and thus a possible starting edge.                 *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  initialise                                                            *
*  while not at end of edges search for an edge that could be crossed by *
*   contour height                                                       *
*      check if the edge is active                                       *
*          check if contour is <= second vertex of edge                  *
*	   use this edge and flag it active                              *
*      goto next edge                                                    *
*  return the starting edge                                              *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global:    edges          - array containing TIN edges                *
*  Parameter: contour_height - determines starting edge                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Parameter: found - TRUE if edge found, otherwise false                *
*  Returns:   edge crossed by contour                                    *
*************************************************************************/
{

INDEX i;   		     /* index to edges */
TIN_EDGE starting_edge;   /* starting edge for contour */


/* initialise */
i = first_edge;
*found = FALSE;
/* while not at end of edges search for an edge that could be crossed by
  contour height */
while ( i <= last_edge && !*found
        && edges[i].v1.coord.z <= contour_height) {

   /* check if the edge is active */
   if ( !edges[i].active )
      /* check if contour is <= second vertex of edge */
      if ( contour_height <= edges[i].v2.coord.z ) {
               /* use this edge and flag it active */
               edges[i].active = TRUE;
               starting_edge = edges[i];
               *found = TRUE;
             }
   /* goto next edge */
   i = i + 1;

} /* end while */

/* return the starting edge */
return starting_edge;

} /* -- END OF FUNCTION -- */


TIN_VERTEX Find_vertex( TIN_EDGE present_edge, char direction )
/*************************************************************************
*  Function: Find_vertex                                                 *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Finds the 3rd vertex which completes a triangle given the             *
*  two vertices found on the opposite edge. This also requires wrapping  *
*  around the neighbour list from end to start, and start to end.        *
*                                                                        *
*  Due to the clockwise ordering of neighbours for a point, the 3rd      *
*  vertex which completes a triangle will be the point after the         *
*  sub-point in the the reference-point's neighbours when tracking       *
*  forwards (or clockwise) and will be the point before the sub-point    *
*  in the reference-point's neighbours when tracking backwards           *
*  (or anti-clockwise).                                                  *
*  The 3rd vertex is required to determine through which edge a contour  *
*  exits the triangle using Thomas Poiker's sub-point (SP) reference     *
*  point (RP) tracking scheme.                                           *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  initialise                                                            *
*  if tracking direction is formwards then search forwards through       *
*    neighbour list                                                      *
*           check if neighbour's id = sub point on edge                  *
*              if neighbour = last neighbour then wrap around to start   *
*              otherwise go to next neighbour                            *
*              if the neighbour is outside the TIN then so is 3rd vertex *
*              otherwise vertex = current neighbour                      *
*           otherwise go to next neighbour                               *
*  otherwise tracking direction is backwards so search backwards through *
*   neighbour list                                                       *
*           check if neighbour = sub point on edge                       *
*              if neighbour = first neighbour then wrap around to end    *
*              otherwise neighbour = previous neighbour                  *
*              if the neighbour is outside the TIN then so is 3rd vertex *
*              otherwise vertex = current neighbour                      *
*           otherwise get previous neighbour and go to next neighbour    *
*  return the 3rd vertex in the triangle                                 *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: present_edge - contains sub point (v1)                     *
*                            and reference point (v2)                    *
*             direction    - direction that is contour is being tracked  *
*                            'f' represents forwards or clockwise and    *
*                            'b' represent backwards or anti-clockwise   *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Returns: 3rd vertex completing triangle                               *
*                                                                        *
*  Note regarding algorithm                                              *
*  ------------------------                                              *
*  Only a singly linked list of neighbours is used because all searching *
*  essentially occurs forwards. By keeping pointers to the start and end *
*  of the neighbours a doubly-linked list can be simulated.              *
*************************************************************************/
{

TIN_VERTEX vertex;           /* 3rd vertex in triangle */
int found_vertex;            /* flag for whether vertex was found */
TIN_NBR_PTR nbr;             /* pointer to current neighbour */
TIN_NBR_PTR first_nbr;       /* pointer to first neighbour */
TIN_NBR_PTR last_nbr;        /* pointer to last neighbour */
TIN_NBR_PTR prev_nbr;        /* pointer to previous neighbour */
INDEX pt_id;                 /* current point's id */
INDEX nbr_id;                /* current neighbour's id */


/* initialise */
pt_id = present_edge.v2.id;
first_nbr = points[pt_id].first_nbr;
last_nbr = points[pt_id].last_nbr;
nbr = first_nbr;
found_vertex = FALSE;

/* if tracking direction is formwards then search forwards through
   neighbour list */
if (direction == FORWARDS) {

   while ( !found_vertex ) {
         /* check if neighbour's id = sub point on edge */
         if (nbr->nbrid == present_edge.v1.id) {
            /* if neighbour = last neighbour then wrap around to start */
            if (nbr == last_nbr)
               nbr = first_nbr;
            /* otherwise go to next neighbour */
            else
               nbr = nbr->next;
            /* if the neighbour is outside the TIN then so is 3rd vertex */
            if (nbr->nbrid == OUTSIDE_TIN) {
               vertex.id = OUTSIDE_TIN;
               }
            /* otherwise vertex = current neighbour */
            else {
               nbr_id = nbr->nbrid;
               vertex.id = nbr_id;
               vertex.coord = points[nbr_id].coord;
               }
            found_vertex = TRUE;
         }
         /* otherwise go to next neighbour */
         else
            nbr = nbr->next;
   }

} /* end if */

/* otherwise tracking direction is backwards so search backwards through
  neighbour list */
else { /* direction == BACKWARDS */

   while ( !found_vertex ) {
         /* check if neighbour = sub point on edge */
         if (nbr->nbrid == present_edge.v1.id) {
            /* if neighbour = first neighbour then wrap around to end */
            if (nbr == first_nbr)
               nbr = last_nbr;
            /* otherwise neighbour = previous neighbour */
            else
               nbr = prev_nbr;
            /* if the neighbour is outside the TIN then so is 3rd vertex */
            if (nbr->nbrid == OUTSIDE_TIN) {
               vertex.id = OUTSIDE_TIN;
               }
            /* otherwise vertex = current neighbour */
            else {
               nbr_id = nbr->nbrid;
               vertex.id = nbr_id;
               vertex.coord = points[nbr_id].coord;
               }
            found_vertex = TRUE;
         }
         /* otherwise get previous neighbour and go to next neighbour */
         else {
            prev_nbr = nbr;
            nbr = nbr->next;
            }
   }

} /* end if */

/* return the 3rd vertex completing the triangle */
return vertex;

} /* end of function */


void Reset_edge_flags( REAL contour_height )
/*************************************************************************
*  Function: Reset_edge_flags                                            *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Resets the active flag on all edges that have been crossed by the     *
*  current contour (i.e. edge contains contour height)                   *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  initialise                                                            *
*  while not at last edge and first vertex <= contour height             *
*     check if contour height <= second vertex                           *
*	 flag edge inactive                                              *
*     goto next edge                                                     *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global:    edges - array of TIN edges                                 *
*  Parameter: contour_height - contour height crossing edges             *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Global: edges - array containing TIN edges                            *
*************************************************************************/
{

INDEX i;  /* index to edges */

/* initialise */
i = first_edge;
/* while not at last edge and first vertex <= contour height */
while ( i <= last_edge && edges[i].v1.coord.z <= contour_height ) {
   /* check if contour height <= second vertex */
   if ( contour_height <= edges[i].v2.coord.z ) {
      /* flag edge inactive */
      edges[i].active = FALSE;
      }
   /* goto next edge */
   i++;
} /* end while */

} /* -- END OF FUNCTION -- */

/*************************************************************************
*                       END OF FALCON SEARCHING ROUTINES                 *
*************************************************************************/

