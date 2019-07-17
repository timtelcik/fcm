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

#ifndef FCM_DISPLAY_H_INCLUDED
#define FCM_DISPLAY_H_INCLUDED

/* DISPLAY.H
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
*  DISPLAY FUNCTIONS PROTOTYPE HEADER                                    *
*                                                                        *
*  Written by TIm Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose: Contains the function prototypes for the display routines.   *
*************************************************************************/

/*************************************************************************
*                  START OF DISPLAY HEADER                               *
*************************************************************************/

//
// Display Prototypes
//

void Activate_graphics( void );
void Deactivate_graphics( void );
void Draw_to( REAL x, REAL y );
void Draw_text( REAL x, REAL y, char text[] );
void Draw_border( void );
void Draw_border_coords( REAL wxmin, REAL wymin, REAL wxmax, REAL wymax );
void Draw_cont_info( REAL lower_contour, REAL upper_contour, REAL contour_interval );
void Graphics_pause( void );
void Move_to( REAL x, REAL y );
void Set_colour( int col );
void Begin_line_style( void );
void End_line_style( void );
void Set_line_style( int line_type );
void Set_viewport( REAL xmin, REAL ymin, REAL xmax, REAL ymax );
void Set_window( REAL xmin, REAL ymin, REAL xmax, REAL ymax );
void Transform( REAL x, REAL y, REAL *nx, REAL *ny );
void Flush_graphics( void );
BOOLEAN Is_graphics_active( void );
void Poll_events( void );
void Begin_line_loop( void );
void Begin_line( void );
void Begin_line_strip( void );
void End_line_loop( void );
void End_line( void );
void End_line_strip( void );


//
// Graphics Driver Definitions
//

#define FCM_GRAPHICS_DRIVER_OPENGL "OPENGL"
#define FCM_GRAPHICS_DRIVER_BGI "BGI"
#define FCM_GRAPHICS_DRIVER_IRISGL "IRISGL"

// Define graphics drivers
#ifndef FCM_GRAPHICS_DRIVER
#define FCM_GRAPHICS_DRIVER FCM_GRAPHICS_DRIVER_OPENGL
#endif

// INCLUDE IBM PC DEVICE DRIVER HEADER
// #include "pc_drv.h"

// INCLUDE IRIS DEVICE DRIVER HEADER
// #include "iris_drv.h"


//
// Includes
//

// INCLUDE OPENGL DEVICE DRIVER HEADER
// #if FCM_GRAPHICS_DRIVER == FCM_GRAPHICS_DRIVER_OPENGL
#ifdef FCM_GRAPHICS_DRIVER_OPENGL
#include "gl_color.h"
#include "opengl_drv.h"
#endif

/*************************************************************************
*                  START OF GRAPHICS DRIVER DEFINITIONS                  *
*************************************************************************/


/*************************************************************************
*                  END OF DISPLAY FUNCTION PROTOTYPES                    *
*************************************************************************/

#endif // FCM_DISPLAY_H_INCLUDED

