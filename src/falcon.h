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

#ifndef FCM_FALCON_H_INCLUDED
#define FCM_FALCON_H_INCLUDED

/* FALCON.H
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
*  FUNCTION PROTOTYPES HEADER                                            *
*                                                                        *
*  Written by TIm Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose: Contains the function prototypes for Falcon Contour Map.     *
*************************************************************************/

/*************************************************************************
*                   START OF FALCON FUNCTION PROTOYPES                   *
*************************************************************************/

/* INPUT FUNCTION PROTOTYPES */

int Eoln( FILE *fp );
void Open_cont_file( FILE *(*cont_file) );
void Open_tin_file( FILE *(*tin_file) );
void Get_contour_info( REAL zmin, REAL zmax,
                       REAL *lower_contour, REAL *upper_contour,
                       REAL *contour_interval );
void Get_smoothing_info( REAL *adjust, REAL *sample );
void Prompt_reply(char prompt[MAX_STRING], BOOLEAN default_reply,
        BOOLEAN *reply);
void Prompt_value( char prompt[MAX_STRING], REAL *value,
            REAL min_value, REAL max_value );


/* INTERPOLATION FUNCTION PROTOTYPES */

void Adjust_edge_cuts( REAL adjust, POINT p, POINT q,
		       POINT *adj_p, POINT *adj_q );
REAL Distance( REAL x1, REAL y1, REAL x2, REAL y2 );
POINT Interpolate_edge_cut( POINT p, POINT q, REAL height );
void Sample_spline( REAL i0, REAL j0, REAL i1, REAL j1,
		    REAL i2, REAL j2, REAL i3, REAL j3,
		    REAL height, REAL sample, INDEX *end_cont );


/* OUTPUT FUNCTION PROTOTYPES */

void Display_contour(void);
void Display_network(void);
void Display_tin_topology(void);
void Display_tin_edges(void);
void Display_title(void);
void Save_contour( FILE *cont_file );


/* QUICKSORT FUNCTION PROTOTYPES */

void Quicksort( TIN_EDGE *edge_start, INDEX left, INDEX right );
void Swap( TIN_EDGE *edge_start, INDEX i, INDEX j );



/* SEARCHING FUNCTION PROTOTYPES */

INDEX Find_edge( TIN_EDGE edge, BOOLEAN *found );
TIN_EDGE Find_starting_edge( REAL contour_height, BOOLEAN *found );
TIN_VERTEX Find_vertex( TIN_EDGE present_edge, char direction );
void Reset_edge_flags( REAL contour_height );


/* TOPOLOGY FUNCTION PROTOTYPES */

void Add_nbr_to_pt( INDEX pt_id, INDEX nbr_id );
void Add_pt_to_tin( INDEX pt_id, REAL x, REAL y, REAL z );
void Create_edges(void);
void Free_memory(void);
TIN_NBR_PTR New_nbr(void);
void Setup_tin( FILE *tin_file, REAL *wxmin, REAL *wymin,
		REAL *wxmax, REAL *wymax, REAL *zmin, REAL *zmax );


/* TRACKING FUNCTION PROTOTYPES */

void Generate_contours( REAL lower_contour, REAL upper_contour,
                        REAL contour_interval, BOOLEAN save_cont,
			FILE *cont_file, REAL adjust, REAL sample );
void Track_contour( TIN_EDGE starting_edge, REAL contour_height,
		    REAL adjust, REAL sample,
		    BOOLEAN *degenerate_contour);

/*************************************************************************
*                    END OF FALCON FUNCTION PROTOYPES                    *
*************************************************************************/

#endif // FCM_FALCON_H_INCLUDED

