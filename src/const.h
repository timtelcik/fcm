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

/* CONST.H
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
*  CONSTANTS HEADER                                                      *
*                                                                        *
*  Written by Tim Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose: Contains constants used in Falcon Contour Map.               *
*************************************************************************/

/*************************************************************************
*                  START OF FALCON CONSTANT DEFINITIONS                  *
*************************************************************************/

#define MAX_POINTS 120   /* maximum number of TIN points */
#define MAX_EDGES MAX_POINTS*5   /* maximum number of TIN edges */
#define MAX_CONT_PTS 500 /* maximum no. points in a contour */
#define DEBUG 0          /* set by the programmer when debugging topology
			    0 - debugging off
			    1 - debugging on  */

#define TRUE  1          /* Boolean true */
#define FALSE 0          /* Boolean false */
#define CR '\n'          /* carriage return */
#define OUTSIDE_TIN -1   /* neighbour which is outside the TIN */
#define NO_SEGMENT -1    /* used to show there is no line segment */
#define END_CONTOUR -1   /* end of contour marker */
#define vpxmin 0.15      /* lower left x coordinate of viewport in NDC  */
#define vpymin 0.15      /* lower left y cooridnate of viewport in NDC  */
#define vpxmax 0.85      /* upper right x cooridnate of viewport in NDC */
#define vpymax 0.85      /* upper right y cooridnate of viewport in NDC */
#define MAX_STRING 79    /* maximum size of a string */
#define FORWARDS 'f'     /* defines a tracking direction of forwards */
#define BACKWARDS 'b'    /* defines a tracking direction of backwards */
#define YES 'y'          /* a yes reply */
#define NO 'n'           /* a no reply */
#define MIN_CI 0.1       /* minimum contour interval */
#define MAX_CI 500       /* maximum contour interval */
#define MIN_ADJUST 0.0   /* minimum edge cut adjustment factor */
#define MAX_ADJUST 0.5   /* maximum edge cut adjustment factor */
#define MIN_SAMPLE 0.1   /* minimum spline sampling interval */
#define MAX_SAMPLE 10.0  /* maximum spline sampling interval */

/*************************************************************************
*                    END OF FALCON CONSTANT DEFINITIONS                  *
*************************************************************************/

