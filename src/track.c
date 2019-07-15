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

/* TRACK.C
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
*  TRACKING ROUTINES                                                     *
*                                                                        *
*  Written by Tim Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose: Contains contour tracking routines for Falcon Contour Map.   *
*                                                                        *
*  Routines Included                                                     *
*  -----------------                                                     *
*  Generate_contours                                                     *
*  Track_contour                                                         *
*************************************************************************/

/*************************************************************************
*                       INCLUDE HEADER FILES                             *
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
*                      GLOBAL VARIABLE DECLARATIONS                      *
*************************************************************************/

extern TIN_EDGE edges[MAX_EDGES+1];     /* array of TIN edges */
extern INDEX first_edge;                /* index to first TIN edge */
extern INDEX last_edge;		        /* index to last TIN edge */
extern TIN_POINT points[MAX_POINTS+1];  /* array of TIN points */
extern INDEX first_pt_id;               /* index to first TIN point */
extern INDEX last_pt_id;                /* index to last TIN point */
extern POINT contour[MAX_CONT_PTS];     /* (x,y,z) pts for a contour */
extern INDEX start_seg_one,             /* start of first line segment */
	     end_seg_one;               /* end of first line segment */
extern INDEX start_seg_two,             /* start of second line segment */
	     end_seg_two;               /* end of second line segment */


/*************************************************************************
*                    START OF FALCON TRACKING ROUTINES                   *
*************************************************************************/

void Generate_contours( REAL lower_contour, REAL upper_contour,
		        REAL contour_interval, BOOLEAN save_cont,
                        FILE *cont_file, REAL adjust , REAL sample )
/*************************************************************************
*  Function: Generate_contours                                           *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Generates contours on the TIN within the given contour range by       *
*  tracking each contour separately.                                     *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  loop through the contour interval specified by the user               *
*           find a starting edge crossed by the contour height           *
*           check if a starting edge was found                           *
*              track the contour through the TIN                         *
*              display the contour to the screen                         *
*              save the contour to a data file if required               *
*      reset flags on edges that have been used by this contour height   *
*      goto next contour level                                           *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global: contour - contains the list of (x,y,z) contour points         *
*  Parameter: lower_contour, upper_contour - contour range               *
*             contour_interval - vertical distance between contours      *
*             save_cont - whether contour data is saved to a data file   *
*             cont_file - pointer to contour data file                   *
*             adjust - percentage by which edge cuts are adjusted        *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  Find_starting_edge                                                    *
*  Track_contour                                                         *
*  Display_contour                                                       *
*  Save_contour                                                          *
*  Reset_edge_flags                                                      *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  displays contours to the monitor                                      *
*************************************************************************/
{

REAL contour_height;         /* current contour height */
BOOLEAN found_edge;          /* whether edge has been found */
TIN_EDGE starting_edge;      /* starting edge for current contour */
BOOLEAN degenerate_contour;  /* whether contour is degenerate */


/* loop through the contour interval specified by the user */
contour_height = lower_contour;
while (contour_height <= upper_contour) {

    found_edge = TRUE;
    while (found_edge) {

	 /* find a starting edge crossed by the contour height */
	 starting_edge = Find_starting_edge(contour_height, &found_edge);

	 /* check if a starting edge was found */
	 if (found_edge) {
	    /* track the contour through the TIN */
	    Track_contour(starting_edge, contour_height, adjust, sample,
			  &degenerate_contour );
	    /* check if contour is not degenerate */
	    if ( !degenerate_contour ) {
		/* display contour to screen */
		Display_contour();
		/* save the contour to a data file if required */
		if ( save_cont == YES )
		   Save_contour(cont_file);
	    } /* end if */
	 } /* end if */

    } /* end while */

    /* reset flags on edges that have been used by this contour height */
    Reset_edge_flags(contour_height);

    /* goto next contour level */
    contour_height = contour_height + contour_interval;

} /* end while */

} /* -- END OF FUNCTION -- */


void Track_contour( TIN_EDGE starting_edge, REAL contour_height,
		    REAL adjust, REAL sample,
		    BOOLEAN *degenerate_contour )
/*************************************************************************
*  Function: Track_contour                                               *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Tracks (or follows) a single contour through the TIN.                 *
*  A contour can be closed (i.e. contains a single line segment)         *
*  or open (i.e two line segments originating at the same edge but       *
*  tracked clockwise and anti-clockwise respectively).                   *
*                                                                        *
*  Algorithm                                                             *
*  ----------                                                            *
*  initialise                                                            *
*  while contour is not closed, open or degenerate                       *
*	initialise                                                       *
*	get entry edge for first triangle crossed by contour             *
*	interpolate entry point on entry edge                            *
*	while contour has not reached TIN boudary and                    *
*	 not returned to its starting edge and is not degenerate         *
*	      find the 3rd vertex which completes the triangle           *
*	      if vertex points outside TIN then contour reached boundary *
*	      otherwise track contour using sub-point & reference-point  *
*		 if vertex is above contour change reference point       *
*		 otherwise if vertex is below contour change sub-point   *
*		 check if contour crossed to an active edge              *
*		    check if contour formed a closed loop                *
*		       flag contour closed                               *
*		       closed contours are not degenerate                *
*		 otherwise flag present edge active                      *
*		 check if contour is not degenerate                      *
*		    get edge through which contour exits triangle        *
*		    interpolate exit point on exit edge                  *
*		    check if smoothing the contour                       *
*		       adjust contour entry and exit points in triangle  *
*		       check if starting a new line segment              *
*			 check if tracking forwards                      *
*			   store adjusted entry,exit points in contour   *
*			   save first entry,exit points for line segment *
*			 otherwise                                       *
*			    check if any points in first segment         *
*				sample spline between line segments      *
*				store adjusted entry point in contour    *
*			   new segment has been started                  *
*		      otherwise                                          *
*			  sample spline across triangle boundaries       *
*		    previous entry/exit points = new entry/exit points   *
*		    otherwise there is no smoothing required             *
*			 store triangle entry and exit points in contour *
*		 entry edge,point for next triangle =                    *
*		  exit edge,point of current triangle                    *
*	<end while loop>                                                 *
*	check if contour is degenerate                                   *
*	otherwise contour is closed or open                              *
*	    check if contour is closed                                   *
*	       check if smoothing                                        *
*		   store last point of closed contour                    *
*		   sample spline between end and start of closed contour *
*	       last point in a closed contour = first point              *
*	    otherwise contour is open                                    *
*	       check if currently tracking forwards                      *
*		  change tracking direction                              *
*		  check if no points were created for first segment      *
*		     store the entry point for triangle in contour       *
*		     set segment indices                                 *
*		  otherwise points were created                          *
*			set segment indices                              *
*			store exit point for triangle in contour         *
*	       otherwise currently tracking backwards                    *
*		  flag contour as finished                               *
*		  check if no points were created for second segment     *
*		     get segment indices                                 *
*		     store entry point for triangle in contour           *
*		  otherwise points were created                          *
*			set segment indices                              *
*			store exit point for triangle in contour         *
*   <end while loop>                                                     *
*                                                                        *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global: edges - array containing TIN edges                            *
*          points - array containing TIN points                          *
*  Parameter: starting_edge - edge where tracking starts                 *
*             contour_height - height of contour to be tracked and       *
*                              interpolated                              *
*             adjust - percentage by which edge cuts are adjusted        *
*             sample - sampling interval for bi-cubic spline             *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  Interpolate_edge_cuts                                                 *
*  Find_vertex                                                           *
*  Adjust_edge_cuts                                                      *
*  Sample_spline                                                         *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Global: contour - array containing interpolated (x,y,z) points for a  *
*		     contour                                             *
*          start_seg_one - start of first line segment                   *
*          end_seg_one   - end of first line segment                     *
*          start_seg_two - start of second line segment                  *
*          end_seg_two   - end of second line segment                    *
*                                                                        *
*  Notes                                                                 *
*  -----                                                                 *
*  vertex 1 (v1) of present_edge is used as the sub-point (SP)           *
*  vertex 2 (v2) of present_edge is used as the reference-point (RP)     *
*                                                                        *
*  A degenerate contour is one which tries to cross to an edge already   *
*  used by another contour at the same height. If the present edge is    *
*  already in use by another contour at the same height then it is       *
*  terminated (i.e. tracking stops).                                     *
*                                                                        *
*  A closed contour has only only line segment, whereas an open contour  *
*  has two line segments (one from tracking forwards and one from        *
*  tracking backwards). This results in testing the contour to determine *
*  the start and end of each line segment within the contour array.      *
*                                                                        *
*  Smoothing during the tracking is more efficient than smoothing after  *
*  which is why it has been included in this module.                     *
*************************************************************************/
{

BOOLEAN open_contour;          /* whether contour is open */
BOOLEAN reached_boundary;      /* whether contour reached boundary */
BOOLEAN closed_contour;        /* whether contour is closed */
TIN_VERTEX vertex;             /* 3rd vertex completing a triangle */
TIN_EDGE present_edge;         /* present edge during tracking */
TIN_EDGE entry_edge;           /* edge where contour enters triangle */
POINT entry_point;             /* entry point on entry edge */
POINT adj_entry_point;         /* adjusted entry point */
TIN_EDGE exit_edge;            /* edge where contour exits triangle */
POINT exit_point;              /* exit point on exit edge */
POINT adj_exit_point;          /* adjusted exit point */
POINT prev_entry_point;        /* entry point from previous triangle */
POINT prev_exit_point;         /* exit point from previous triangle */
POINT first_entry_point;       /* first entry point for a segment */
POINT first_exit_point;        /* first exit point for a segment */
INDEX edge_pos;                /* position of edge in edge list */
char direction;                /* direction of tracking */
BOOLEAN found_edge;            /* whether edge was found */
BOOLEAN starting_new_segment;  /* whether starting a new line segment */
INDEX end_cont;                /* index to end of contour */


/* initialise */
closed_contour = FALSE;
open_contour = FALSE;
*degenerate_contour = FALSE;
direction = FORWARDS;
end_cont = 0;
start_seg_one = 0;
end_seg_one = start_seg_one;
start_seg_two = NO_SEGMENT;
end_seg_two = start_seg_two;

/* while contour is not closed, open or degenerate */
while ( !closed_contour && !open_contour && !*degenerate_contour ) {

      /* initialise */
      reached_boundary = FALSE;
      starting_new_segment = TRUE;
      present_edge = starting_edge;
      /* get entry edge for first triangle crossed by contour */
      entry_edge = starting_edge;
      /* interpolate entry point on first triangle */
      entry_point = Interpolate_edge_cut( entry_edge.v1.coord,
					  entry_edge.v2.coord,
					  contour_height );

      /* while contour has not reached TIN boudary and
	 not returned to its starting edge and is not degenerate */
      while ( !reached_boundary && !closed_contour &&
	      !*degenerate_contour ) {

	    /* find the 3rd vertex which completes the triangle */
	    vertex = Find_vertex(present_edge, direction);
	    /* if vertex outside TIN then contour reached boundary */
	    if (vertex.id == OUTSIDE_TIN)
	       reached_boundary = TRUE;

	    /* otherwise track contour using sub-point,reference point */
	    else {
	       /* if vertex is above contour change reference point */
	       if ( vertex.coord.z >= contour_height )
		   present_edge.v2 = vertex;
	       /* otherwise if vertex is below contour change sub-point */
	       else
		  if ( vertex.coord.z <= contour_height )
		       present_edge.v1 = vertex;

	       /* check if contour crossed to an active edge */
	       edge_pos = Find_edge(present_edge,&found_edge);
	       if (edges[edge_pos].active) {
		  *degenerate_contour = TRUE;
		  /* check if contour formed a closed loop */
		  if (present_edge.v1.id == starting_edge.v1.id &&
		      present_edge.v2.id == starting_edge.v2.id) {
		     /* flag contour closed */
		     closed_contour = TRUE;
		     /* closed contours are not degenerate */
		     *degenerate_contour = FALSE;
		     }
		  }
	       /* otherwise flag present edge active so it cannot be
		  used by another contour at this height */
	       else
		   edges[edge_pos].active = TRUE;

	       /* check if contour is not degenerate */
	       if ( !*degenerate_contour ) {

		  /* get edge through which contour exits triangle */
		  exit_edge = present_edge;
		  /* interpolate exit point on exit edge */
		  exit_point = Interpolate_edge_cut( exit_edge.v1.coord,
						     exit_edge.v2.coord,
						     contour_height );

		  /* check if smoothing the contour */
		  if ( adjust > 0 ) {
		     /* adjust contour entry, exit points in triangle */
		     Adjust_edge_cuts( adjust, entry_point, exit_point,
				      &adj_entry_point, &adj_exit_point );
		     /* check if starting a new line segment */
		     if ( starting_new_segment ) {
			 /* check if tracking forwards */
			 if ( direction == FORWARDS ) {
			    /* store new triangle entry and exit points in
			       contour */
			    contour[end_cont] = adj_entry_point;
			    end_cont = end_cont + 1;
			    contour[end_cont] = adj_exit_point;
			    end_cont = end_cont + 1;
			    /* save the first entry and exit points for
			       this line segment */
			    first_entry_point = adj_entry_point;
			    first_exit_point = adj_exit_point;
			    }
			 /* otherwise sample points along a spline
			    between the first and second segments */
			 else {
			    /* check if any points in first segment */
			    if ( end_seg_one > 0 ) {
			      /* sample points along a spline between
				 first and second line segments */
			      Sample_spline (
				 first_exit_point.x, first_exit_point.y,
				 first_entry_point.x, first_entry_point.y,
				 adj_entry_point.x, adj_entry_point.y,
				 adj_exit_point.x, adj_exit_point.y,
				 contour_height, sample, &end_cont );
			      /* store adjusted entry point in contour */
			      contour[end_cont] = adj_entry_point;
			      end_cont = end_cont + 1;
			      }
			    }
			 /* new segment has been started */
			 starting_new_segment = FALSE;
		     }
		    /* otherwise interpolate across triangle boundaries */
		    else {
			/* sample points along a spline between
			   triangles */
			Sample_spline (
				 prev_entry_point.x, prev_entry_point.y,
				 prev_exit_point.x, prev_exit_point.y,
				 adj_entry_point.x, adj_entry_point.y,
				 adj_exit_point.x, adj_exit_point.y,
				 contour_height, sample, &end_cont );
			contour[end_cont] = adj_entry_point;
			end_cont = end_cont + 1;
			}
		  /* previous entry/exit points = new entry/exit points */
		  prev_entry_point = adj_entry_point;
		  prev_exit_point = adj_exit_point;
		  } /* end if smoothing required */

		  /* otherwise there is no smoothing required */
		  else {
		       /* store triangle entry, exit points in contour */
		       contour[end_cont] = entry_point;
		       end_cont++;
		  }

	       /* entry edge and point for next triangle is the exit edge
		  and point of current triangle */
	       entry_edge = exit_edge;
	       entry_point = exit_point;

	       } /* end if */

	    } /* end if-else */

      } /* end while */

      /* check if contour is degenerate */
      if ( *degenerate_contour ) {
	   end_seg_one = 0;
	   start_seg_two = NO_SEGMENT;
	   end_seg_two = NO_SEGMENT;
      } /* end if contour is degenerate */

      /* otherwise contour is closed or open */
      else {
	  /* check if contour is closed */
	  if ( closed_contour ) {
	     /* check if smoothing */
	     if ( adjust > 0 ) {
		 /* store last point of the closed contour */
		 contour[end_cont] = adj_exit_point;
		 end_cont = end_cont + 1;
		 /* sample points along a spline between the end and
		    start of the closed contour */
		 Sample_spline(
			 adj_entry_point.x, adj_entry_point.y,
			 adj_exit_point.x, adj_exit_point.y,
			 first_entry_point.x, first_entry_point.y,
			 first_exit_point.x, first_exit_point.y,
			 contour_height, sample, &end_cont);
	     } /* end if check for smoothing */
	     /* last point in a closed contour = first point */
	     contour[end_cont] = contour[start_seg_one];
	     end_seg_one = end_cont;
	  } /* end if contour is closed */

	  /* otherwise contour is open */
	  else {
	     /* check if currently tracking forwards */
	     if ( direction == FORWARDS ) {
		/* change tracking direction */
		direction = BACKWARDS;
		/* check if no points were created for first segment */
		if ( end_cont == 0 ) {
		   /* store the entry point for triangle in contour */
		   contour[start_seg_one] = entry_point;
		   /* set segment indices */
		   end_seg_one = start_seg_one;
		   start_seg_two = end_seg_one + 1;
		   end_seg_two = start_seg_two;
		}
		/* otherwise points were created */
		else {
		      /* set segment indices */
		      end_seg_one = end_cont;
		      start_seg_two = end_seg_one+1;
		      end_seg_two = start_seg_two;
		      /* store exit point for triangle in contour */
		      contour[end_seg_one] = exit_point;
		      end_cont++;
		 }
	     } /* end if direction is forwards */

	     /* otherwise currently tracking backwards */
	     else  { /* direction == BACKWARDS */
		/* flag contour as finished */
		open_contour = TRUE;
		/* check if no points were created for second segment */
		if ( end_cont == start_seg_two ) {
		   /* get segment indices */
		   end_seg_two = start_seg_two;
		   /* store entry point for triangle in contour */
		   contour[end_seg_two] = entry_point;
		}
		/* otherwise points were created */
		else {
		      /* set segment indices */
		      end_seg_two = end_cont;
		      /* store exit point for triangle in contour */
		      contour[end_seg_two] = exit_point;
		}
	     } /* end else direction is backwards */

	  } /* end else contour is open */

      } /* end else contour is closed or open */

} /* end while contour is not closed, open or degenerate */

} /* -- END OF FUNCTION -- */

/*************************************************************************
*                     END OF FALCON TRACKING ROUTINES                    *
*************************************************************************/

