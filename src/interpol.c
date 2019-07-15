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

/* INTERPOL.C
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
*  INTERPOLATION ROUTINES                                                *
*                                                                        *
*  Written by Tim Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose: Contains interpolation routines for Falcon Contour Map.      *
*                                                                        *
*  Routines Included                                                     *
*  -----------------                                                     *
*  Adjust_edge_cuts                                                      *
*  Distance                                                              *
*  Interpolate_edge_cut                                                  *
*  Sample_spline                                                         *
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

extern POINT contour[MAX_CONT_PTS];     /* (x,y,z) pts for a contour */


/*************************************************************************
*                  START OF FALCON INTERPOLATION ROUTINES                *
*************************************************************************/

void Adjust_edge_cuts( REAL adjust, POINT p, POINT q,
		       POINT *adj_p, POINT *adj_q )
/*************************************************************************
*  Function: Adjust_edge_cuts                                            *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Adjusts (displaces) the entry and exit points (edge cuts) on a        *
*  triangle (edge cuts) so that the sudden change of direction visible   *
*  when passing a straight line through linear interpolated points is    *
*  removed.                                                              *
*  To do this, a vector is considered to pass between the entry and exit *
*  points in the triangle.                                               *
*  The entry point is displaced by (length*adjust) from start of the     *
*  vector.                                                               *
*  The exit point is displaced by (length*(1-adjust)) from start of      *
*  vector.                                                               *
*  which is the same as (length*adjust) from end of vector.              *
*  'adjust' is simply a percentage of the vector's length by which the   *
*  edge cuts are displaced.                                              *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  calculate vector pq coefficients                                      *
*  get coordinates of first point (i.e. start of vector)                 *
*  calculate adjusted position of point p from start of vector           *
*  calculate adjusted position of point q from start of vector           *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: adjust - percentage by which edge cuts are displaced       *
*             p      - point where contour enters triangle               *
*             q      - point where contour exits triangle                *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Parameter: adj_p, adj_q  - points p and q after adjusting             *
*************************************************************************/
{

REAL a, b;        /* coefficients of vector pq */
REAL x1,y1;	  /* starting point of vector pq */

/* calculate vector pq coefficients */
a = q.x - p.x;
b = q.y - p.y;

/* get coordinates of first point (i.e. start of vector) */
x1 = p.x;
y1 = p.y;

/* calculate adjusted position of point p from start of vector */
adj_p->x = x1 + ( a * adjust );
adj_p->y = y1 + ( b * adjust );
adj_p->z = p.z;

/* calculate adjusted position of point q from start of vector */
adj_q->x = x1 + ( a * (1-adjust) );
adj_q->y = y1 + ( b * (1-adjust) );
adj_q->z = q.z;

} /* -- END OF FUNCTION -- */


REAL Distance( REAL x1, REAL y1, REAL x2, REAL y2 )
/*************************************************************************
*  Function :  Distance                                                  *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Calculates the distance between two points.                           *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: x1,y1 - coordinate of first point                          *
*             x2,y2 - coordinate of second point                         *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Returns: distance between (x1,y1) and (x2,y2)                         *
*************************************************************************/
{

return sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );

} /* -- END OF FUNCTION -- */


POINT Interpolate_edge_cut( POINT p, POINT q, REAL height )
/*************************************************************************
*  Function: Interpolate_edge_cut                                        *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Interpolate the (x,y) position on an edge for a given z (height).     *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  calculate vector pq coefficients                                      *
*  get coordinates of first point                                        *
*  calculate parametric term (t)                                         *
*  check if p and q have the same height                                 *
*     let point p become the interpolated point                          *
*  otherwise p and q have differing heights                              *
*     calculate term t for the parametric equation                       *
*     interpolate point by using the value of t to determine x and y     *
*  return the interpolated point                                         *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: p,q    - starting and ending points of edge                *
*             height - contour height which is used to determing (x,y)   *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Returns: interpolated point                                           *
*                                                                        *
*  Note                                                                  *
*  ----                                                                  *
*  The edge is treated as a parametric equation.                         *
*                                                                        *
*      xp = x1 + a*t                                                     *
*      yp = y1 + b*t                                                     *
*      zp = z1 + c*t                                                     *
*                                                                        *
*      where xp,yp,zp are the x,y,z in parametric form                   *
*            x1,y1,z1 are the starting points of the vector pq           *
*            a,b,c are the i,j,k coefficients of the vector pq           *
*            and t is the parametric term used to define displacement    *
*             along vector pq                                            *
*                                                                        *
*      The vector pq is represented as                                   *
*                                                                        *
*      ai + bj + ck = 0                                                  *
*                                                                        *
*      where a,b,c are the coefficients of i,j,k and                     *
*            i,j,k are the axes (ie. x,y,z)                              *
*************************************************************************/
{

REAL a, b, c;       /* coefficients of vector pq */
REAL x1,y1,z1;	/* starting point of vector pq */
REAL t;		/* parametric term */
POINT inter_pt;       /* interpolated point */

/* calculate vector pq coefficients */
a = q.x - p.x;
b = q.y - p.y;
c = q.z - p.z;

/* get coordinates of first point */
x1 = p.x;
y1 = p.y;
z1 = p.z;

/* calculate parametric term (t)
  Note: If two points have same z value (height) then a divide by zero
	error could occur. One way of getting around this is by
	checking if points p and q have the same z value (height) and
	if so assigning point p as the interpolated point */

/* check if p and q have the same height */
if ( c == 0 ) {
  /* let point p become the interpolated point */
  inter_pt.x = p.x;
  inter_pt.y = p.y;
  inter_pt.z = height;
  }
/* otherwise p and q have differing heights */
else {
  /* calculate term t for the parametric equation */
  t = (height - z1) / c;
  /* interpolate point by using the value of t to determine x and y */
  inter_pt.x = x1 + (a*t);
  inter_pt.y = y1 + (b*t);
  inter_pt.z = height;
  }

/* return the interpolated point */
return inter_pt;

} /* -- END OF FUNCTION -- */


void Sample_spline( REAL i0, REAL j0, REAL i1, REAL j1,
		    REAL i2, REAL j2, REAL i3, REAL j3,
		    REAL height, REAL sample, INDEX *end_cont )
/**************************************************************************
*  Function : Sample_spline                                               *
*                                                                         *
*  Purpose                                                                *
*  -------                                                                *
*  This routine samplesates points along on a bicubic spline which passes *
*  through two end points. The points either side of the end points are   *
*  used as control points. A weighting factor is used to change the       *
*  amount of curvature on the spline.                                     *
*                                                                         *
*  For futher information see:                                            *
*                                                                         *
*  Lauzzana, R.G. and D.E.M. Penrose (1990) Implementing bicubic splines. *
*      Dr. Dobb's Journal, August 1990: 48-59,118-119                     *
*                                                                         *
*  Algorithm                                                              *
*  ---------                                                              *
*     calculate distance between end points                               *
*     if sampling increment < distance bewtween points then interpolate   *
*      points along the bi-cubic spline                                   *
*        convert sampling rate to a function of t                         *
*        calculate the number of samples to be taken in a unit interval   *
*        interpolate points along the spline with the given interval      *
*           get parameter term t for spline                               *
*           get parametric term (1 - t) for spline                        *
*           interpolate a point on the bi-cubic spline                    *
*           add i,j to contour                                            *
*           increment position within contour                             *
*	    decrement counter                                             *
*                                                                         *
*  Inputs                                                                 *
*  ------                                                                 *
*  Global:    contour - contains interpolated contour points              *
*  Parameter: i0,j0 - coordinate of first control point                   *
*             i1,j1 - coordinate of first end point                       *
*             i2,j2 - coordinate of second end point                      *
*             i3,j3 - coordinate of second control point                  *
*             height - height of contour being smoothed                   *
*             sample - sampling interval for points on the spline         *
*             end_cont - index to end of contour                          *
*                                                                         *
*  Calls                                                                  *
*  -----                                                                  *
*  Distance                                                               *
*                                                                         *
*  Outputs                                                                *
*  -------                                                                *
*  Global:    contour  - contains interpolated contour points             *
*  Parameter: end_cont - index to end of contour                          *
**************************************************************************/
{

// REAL t0, t1, t2, t3, t5;  /* parametric terms */
REAL t1, t2, t3, t5;      /* parametric terms */
REAL dt;                  /* sampling rate as a function of t */
REAL dist;                /* distance between end points */
REAL W;                   /* curve weighting factor */
REAL i, j;                /* interpolated point on spline */
REAL i5, j5;
REAL count;               /* number of samples per unit interval */

/* set weighting on spline */
W = 0.4;

/* calculate distance between end points */
dist = Distance(i1,j1,i2,j2);

/* if sampling increment < distance bewtween points then interpolate
  points along the bi-cubic spline */
if ( sample < dist ) {
  i5 = i1-i0;
  j5 = j1-j0;
  i3 = i2-i3;
  j3 = j2-j3;
  /* convert sampling rate to a function of t */
  dt = sample/dist;
  /* get the number of samples to be taken in a unit interval */
  count = 1.0/dt - 1;

  /* interpolate points along the spline with the given interval */
  while ( count > 0 ) {
     /* get parameter term t for spline */
     t1 = dt*count;
     /* get parametric term (1 - t) for spline */
     t2 = 1.0 - t1;
     t5 = W*t1*t1*t2;
     t3 = W*t1*t2*t2;
     /* interpolate a point on the bi-cubic spline */
     i = i1*t1 + i2*t2 + t3*i3 + i5*t5;
     j = j1*t1 + j2*t2 + t3*j3 + j5*t5;
     /* add sampled (interpolated) point to contour */
     contour[*end_cont].x = i;
     contour[*end_cont].y = j;
     contour[*end_cont].z = height;
     /* increment position within contour */
     *end_cont = *end_cont + 1;
     /* decrement counter */
     count--;
  }

} /* end if */

} /* -- END OF FUNCTION -- */

/*************************************************************************
*                    END OF FALCON INTERPOLATION ROUTINES                *
*************************************************************************/

