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

/* PC_DRV.H
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
*  PC GRAPHICS DRIVER HEADER                                             *
*                                                                        *
*  Written by TIm Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose: Contains the function prototypes for the device dependent    *
*	    display routines in PC_DRV.C                                 *
*************************************************************************/

/*************************************************************************
*      START OF DEVICE DEPENDENT FUNCTION PROTOTYPES FOR THE IBM PC      *
*************************************************************************/

void PC_Activate_graphics( void );
void PC_Deactivate_graphics( void );

void PC_Draw_border( void );
void PC_Draw_text( int x, int y, char string[] );
void PC_Draw_to( double x, double y );
void PC_Graphics_pause( void );
void PC_Move_to( double x, double y );
void PC_Set_colour( int col );
void PC_Set_linestyle( int line_type );

/* INCLUDE THE TURBO C GRAPHICS LIBRARY HEADER */
#include <graphics.h>

/*************************************************************************
*       END OF DEVICE DEPENDENT FUNCTION PROTOTYPES FOR THE IBM PC       *
*************************************************************************/

