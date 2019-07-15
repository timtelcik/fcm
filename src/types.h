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

#ifndef FCM_TYPES_H_INCLUDED
#define FCM_TYPES_H_INCLUDED

/* TYPES.H
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
*  DATA TYPES HEADER                                                     *
*                                                                        *
*  Written by Tim Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose: Contains data types used in Falcon Contour Map.              *
*************************************************************************/

/*************************************************************************
*                    START OF FALCON TYPE DEFINITIONS                    *
*************************************************************************/

/* define a Boolean data type
   (i.e. can assume values TRUE (1), FALSE (0) or YES (Y), NO (N) */
typedef int BOOLEAN;

/* define a real data type */
typedef double REAL;

/* define an index into an array */
typedef int INDEX;

/* define a 3D point */
typedef struct { REAL x, y, z; } POINT;

/* define a pointer to a TIN neighbour info. structure */
typedef struct TIN_NBR_INFO *TIN_NBR_PTR;

/* define a TIN neighbour info. structure */
typedef struct TIN_NBR_INFO {
			INDEX nbrid;      /* id of neighbour */
			TIN_NBR_PTR next; /* pointer to next neighbour */
                            } TIN_NBR;

/* define a TIN point info structure */
typedef struct TIN_POINT_INFO {
                        /* the id is the position within the array */
                        POINT coord;           /* x,y,z coord of pt */
                        TIN_NBR_PTR first_nbr; /* pointer to first nbr */
                        TIN_NBR_PTR last_nbr;  /* pointer to last nbr */
                        BOOLEAN visited;       /* whether point was visited */
                              } TIN_POINT;

/* define a TIN vertex */
typedef struct TIN_VERTEX_INFO {
                       INDEX id;       /* vertex id */
                       POINT coord;    /* coordinates of vertex */
                               } TIN_VERTEX;

/* define a TIN edge info. structure */
typedef struct TIN_EDGE_INFO {
                       TIN_VERTEX v1;   /* first vertex of edge */
                       TIN_VERTEX v2;   /* second vertex of edge */
                       BOOLEAN active;  /* whether edge is active */
                             } TIN_EDGE;

/* define a graphics window rectangle */
typedef struct {
                   REAL xmin,ymin,  /* coords of lower left vertex */
			xmax,ymax,  /* coords of upper right vertex */
			xwidth,     /* width of rectangle in x direction */
			ywidth;     /* width of rectangle in y direction */
               } RECTANGLE;

/*************************************************************************
*                     END OF FALCON TYPE DEFINITIONS                     *
*************************************************************************/

#endif // FCM_TYPES_H_INCLUDED

