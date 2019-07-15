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

/* SORT.C
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
*  SORTING ROUTINES                                                      *
*                                                                        *
*  Written by Tim Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose: Contains quicksort routines for Falcon contour map.          *
*                                                                        *
*  Routines Included                                                     *
*  -----------------                                                     *
*  Quicksort                                                             *
*  Swap                                                                  *
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

extern TIN_EDGE edges[MAX_EDGES+1]; /* array of TIN edges */
extern INDEX first_edge;            /* index of first TIN edge */
extern INDEX last_edge;		    /* index of last TIN edge */


/*************************************************************************
*                     START OF FALCON QUICKSORT ROUTINES                 *
*************************************************************************/

void Quicksort( TIN_EDGE *edge_start, INDEX left, INDEX right )
/*************************************************************************
*  Function: Quicksort                                                   *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Sorts TIN edges based on the first vertex using a quicksort algorithm.*
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: *edge_start - pointer to start of TIN edge array           *
*             left  - left most element in array to be sorted            *
*             right - right most element in array to be sorted           *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  Quicksort                                                             *
*  Swap                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  edges in ascending order based on first vertex                        *
*************************************************************************/
{

INDEX i,last;  /* array indices */

if (left >= right)
  return;
Swap(edge_start, left, (left+right)/2);
last = left;
for (i = left+1;i <= right; i++) {
   if ( (edge_start+i)->v1.coord.z < (edge_start+left)->v1.coord.z )
         Swap(edge_start, ++last, i);
   }
Swap(edge_start, left, last);
Quicksort(edge_start, left, last-1);
Quicksort(edge_start, last+1, right);

} /* -- END OF FUNCTION -- */


void Swap( TIN_EDGE *edge_start, INDEX i, INDEX j )
/*************************************************************************
*  Function: Swap                                                        *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Swaps element i with element j in the TIN edge array.                 *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  set temp = index i                                                    *
*  set index i = index j                                                 *
*  set index j = temp                                                    *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: edge_start - pointer to start of TIN edge array            *
*             i, j       - array indices to be swapped                   *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  swapped TIN edges at indices i, j                                     *
*************************************************************************/
{

TIN_EDGE temp;   /* temporary TIN edge */

/* set temp = index i */
temp = *(edge_start+i);
/* set index i = index j */
*(edge_start+i) = *(edge_start+j);
/* set index j = temp */
*(edge_start+j) = temp;

} /* -- END OF FUNCTION -- */

/*************************************************************************
*                        END OF FALCON QUICKSORT ROUTINES                *
*************************************************************************/

