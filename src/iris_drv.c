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

/* IRIS_DRV.C
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
*  DEVICE DRIVERS FOR SILICON GRAPHICS PERSONAL IRIS                     *
*                                                                        *
*  Written by Tim Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Contains device dependent drivers for the Personal IRIS called from   *
*  routines in DISPLAY.C.                                                *
*  The Silicon Graphics library of graphics routines are used to         *
*  implement graphics routines on the Personal Iris ( See a Silicon      *
*  Graphics Reference manual for further information).                   *
*                                                                        *
*  Routines Included                                                     *
*  -----------------                                                     *
*  IRIS_Activate_graphics                                                *
*  IRIS_Deactivate_graphics                                              *
*  IRIS_Draw_border                                                      *
*  IRIS_Draw_text                                                        *
*  IRIS_Draw_to                                                          *
*  IRIS_Graphics_pause                                                   *
*  IRIS_Move_to                                                          *
*  IRIS_Set_colour                                                       *
*  IRIS_Set_linestyle                                                    *
*************************************************************************/

/*************************************************************************
*                        INCLUDE HEADER FILES                            *
*************************************************************************/

/* INCLUDE STANDARD HEADERS */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* INCLUDE FALCON CONSTANTS HEADER */
#include "const.h"

/* INCLUDE FALCON TYPES HEADER */
#include "types.h"

/* INCLUDE IRIS DEVICE DRIVERS HEADER */
#include "iris_drv.h"


/*************************************************************************
*                       DECLARE GLOBAL VARIABLES                         *
*************************************************************************/

extern int ScreenWidth,
           ScreenHeight; /* Dimensions of graphics screen */
long win_num;            /* Window number where graphics are displayed */


/*************************************************************************
*               START OF DEVICE DEPENDENT ROUTINES FOR THE IRIS          *
*************************************************************************/

void IRIS_Activate_graphics( void )
/*************************************************************************
*  Function: IRIS_Activate_graphics                                      *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Opens a graphics window.                                              *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  get screen dimensions                                                 *
*  set width and height of window                                        *
*  move window process to foreground                                     *
*  open window                                                           *
*  clear window                                                          *
*  select window                                                         *
*  pop window to the front                                               *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  none                                                                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  prefsize, foreground, winopen, clear, winset, winpop                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Global: ScreenWidth,ScreenHeight - dimensions of graphics screen      *
*          win_num                  - window number for graphics display *
*************************************************************************/
{

/* get screen dimensions (i.e. PAL format) */
ScreenWidth = 768;
ScreenHeight = 576;
/* set width and height of window */
prefsize(ScreenWidth, ScreenHeight);
/* move window process to foreground */
foreground();
/* open window */
win_num = winopen("FALCON 1.0");
/* clear window */
clear();
/* select window */
winset(win_num);
/* pop window to the front */
winpop();

} /* -- END OF FUNCTION -- */


void IRIS_Deactivate_graphics( void )
/*************************************************************************
*  Function: IRIS_Deactivate_graphics                                    *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Closes the graphics window.                                           *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global: win_num - window number where graphics is displayed           *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  winclose                                                              *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  none                                                                  *
*************************************************************************/
{

/* close the window */
winclose(win_num);

} /* -- END OF FUNCTION -- */


void IRIS_Draw_border( void )
/*************************************************************************
*  Function: IRIS_Draw_border                                            *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Draws a bounding box the size of the viewport on the graphics window. *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global: wxmin, wymin - lower left coordinates of bounding box         *
*          wxmax, wymax - upper right coordinates of bounding box        *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  rect                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  displays bounding box and bounding box coordinates                    *
*************************************************************************/
{

/* display a rectangle the dimensions of the viewport on the monitor */
rect( vpxmin*ScreenWidth, vpymin*ScreenHeight,
      vpymax*ScreenWidth, vpymax*ScreenHeight );

} /* -- END OF FUNCTION -- */


void IRIS_Draw_text(int x,int y,char string[])
/*************************************************************************
*  Function: IRIS_Draw_text                                              *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Draws a text string on the screen at the specified screen coordinate. *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: x,y    - screen coordinate                                 *
*             string - text string to be displayed                       *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  cmov2                                                                 *
*  charstr                                                               *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  string displayed on screen                                            *
*************************************************************************/
{

/* move to (x,y) coordinate in window */
cmov2(x,y);

/* draw string */
charstr(string);

} /* -- END OF FUNCTION -- */


void IRIS_Draw_to( REAL x, REAL y )
/*************************************************************************
*  Function: IRIS_Draw_to                                                *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Draws a line from the current screen coordinate to the new screen     *
*  coordinate.                                                           *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: x,y - new screen coord                                     *
*             ScreenWidth,ScreenHeight - dimensions of screen            *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  lineto                                                                *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  displays a line on screen in the current line style and colour        *
*************************************************************************/
{

int sx,sy;    /* screen x,y coordinate */

/* get screen coordinate */
sx = (int)(x*ScreenWidth);
sy = (int)(y*ScreenHeight);

/* draw a line to new screen coordinate */
draw2(sx,sy);

} /* -- END OF FUNCTION -- */


void IRIS_Graphics_pause( void )
/*************************************************************************
*  Function: IRIS_Graphics_pause                                         *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Pauses the graphics screen until the user decides to exit.            *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  repeat while the user has not pressed return (i.e. carriage return)   *
*     clear the keyboard buffer                                          *
*     get character from keyboard                                        *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  none                                                                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  fflush, getc                                                          *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  none                                                                  *
*                                                                        *
*  Note                                                                  *
*  ----                                                                  *
*  The focus (pointer) must be in the window which started Falcon when   *
*  <RETURN> is pressed.                                                  *
*************************************************************************/
{

int c;   /* character read from keyboard */

/* repeat while the user has not pressed return (Carriage Return) */
do {
  /* clear the keyboard buffer */
  fflush(stdin);
  c = getc(stdin);
} while (c != CR);

} /* -- END OF FUNCTION -- */


void IRIS_Move_to( REAL x, REAL y )
/*************************************************************************
*  Function: IRIS_Move_to                                                *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Moves to the graphics cursor to a new position on the screen.         *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: x,y - new screen coordinate                                *
*             ScreenWidth, ScreenHeight - dimensions of screen           *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  move2                                                                 *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  none                                                                  *
*************************************************************************/
{

int sx,sy;    /* screen x,y coordinate */

/* get screen coordinate */
sx = (int)(x*ScreenWidth);
sy = (int)(y*ScreenHeight);

/* move to screen coordinate */
move2(sx,sy);

} /* -- END OF FUNCTION -- */


void IRIS_Set_colour( int col )
/*************************************************************************
*  Function: IRIS_Set_colour                                             *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Sets the current drawing colour.                                      *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  col - colour to be used for output                                    *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  color                                                                 *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  new drawing colour                                                    *
*************************************************************************/
{

/* set the current drawing colour */
color(col);

} /* -- END OF FUNCTION -- */


void IRIS_Set_linestyle( int line_type )
/*************************************************************************
*  Function: IRIS_Set_linestyle                                          *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Sets the current line style for drawing lines.                        *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: line_type - the type of line to use                        *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  deflinestyle                                                          *
*  setlinestyle                                                          *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  new line style                                                        *
*************************************************************************/
{

/* select line style */
switch(line_type) {

 case 1 : /* dotted line */
	  deflinestyle(1, 3171);
	  setlinestyle(1);
	  break;
 case 2 : /* dashed line */
	  deflinestyle(2, 255);
	  setlinestyle(2);
	  break;
 case 3 : /* solid line */
	  deflinestyle(3, 65535);
	  setlinestyle(3);
	  break;
 case 4 : /* dashed-dotted line */
	  deflinestyle(4, 3135);
	  setlinestyle(4);
	  break;
 } /* end of cases */

} /* -- END OF FUNCTION -- */

/*************************************************************************
*                END OF DEVICE DEPENDENT DRIVERS FOR THE IRIS            *
*************************************************************************/

