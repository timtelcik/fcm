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

#ifndef FCM_OPENGL_H_INCLUDED
#define FCM_OPENGL_H_INCLUDED

/* OPENGL_DRV.H
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
*  OPENGL GRAPHICS DRIVER HEADER                                         *
*                                                                        *
*  Written by TIm Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*  Last Update: 2nd November 2013                                        *
*                                                                        *
*  Purpose: Contains the function prototypes for the device dependent    *
*	        display routines in OPENGL_DRV.C                         *
*************************************************************************/

/*************************************************************************
*     START OF MACHINE DEPENDENT FUNCTION PROTOTYPES FOR OPENGL
*************************************************************************/

void OPENGL_Activate_graphics( void );
void OPENGL_Deactivate_graphics( void );
void OPENGL_Move_to( REAL x, REAL y );
void OPENGL_Draw_border( void );
// void OPENGL_Draw_text( int x,int y,char string[] );
void OPENGL_Draw_text( REAL x,REAL y,char string[] );
void OPENGL_Draw_to( REAL x, REAL y );
void OPENGL_Graphics_pause( void );
void OPENGL_Set_colour( int col );
void OPENGL_Set_line_style( int line_type );
void OPENGL_Begin_line_style( void );
void OPENGL_End_line_style( void );
void OPENGL_Flush_graphics( void );
BOOLEAN OPENGL_Is_graphics_active( void );
void OPENGL_Poll_events( void );
void OPENGL_Begin_line_loop( void );
void OPENGL_Begin_line( void );
void OPENGL_Begin_line_strip( void );
void OPENGL_End_line_loop( void );
void OPENGL_End_line( void );
void OPENGL_End_line_strip( void );


/*************************************************************************
*     INCLUDES
*************************************************************************/

// INCLUDE OPENGL GRAPHICS LIBRARY HEADER
// #include <gl.h>
// #include <glu.h>
// #include <glut.h>

// INCLUDE MACOSX OPENGL GRAPHICS LIBRARY HEADER */
// see http://alumni.cs.ucsb.edu/~wombatty/tutorials/opengl_mac_osx.html
// see http://stackoverflow.com/questions/12229714/building-glew-for-mac-osx
// see http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/
// see http://msdn.microsoft.com/en-us/library/windows/desktop/dd374286%28v=vs.85%29.aspx
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

// INCLUDE GLFW HEADER
// see http://www.glfw.org
#include <GLFW/glfw3.h>

#include "gl_color.h"


/*************************************************************************
*       END OF MACHINE DEPENDENT FUNCTION PROTOTYPES FOR OPENGL          *
*************************************************************************/

#endif // FCM_OPENGL_H_INCLUDED

