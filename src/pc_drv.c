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

/* PC_DRV.C
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
*  DEVICE DRIVERS FOR THE IBM PC                                         *
*                                                                        *
*  Written by Tim Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Contains device dependent drivers for the IBM PC called from routines *
*  in DISPLAY.C.                                                         *
*  Borland's Turbo C graphics library is used to implement graphics      *
*  routines on the IBM PC ( See a Turbo C Reference Manual for further   *
*  information).                                                         *
*                                                                        *
*  Routines Included                                                     *
*  -----------------                                                     *
*  PC_Activate_graphics                                                  *
*  PC_Deactivate_graphics                                                *
*  PC_Draw_border                                                        *
*  PC_Draw_to                                                            *
*  PC_Draw_text                                                          *
*  PC_Graphics_pause                                                     *
*  PC_Move_to                                                            *
*  PC_Set_colour                                                         *
*  PC_Set_linestyle                                                      *
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

/* INCLUDE PC DEVICE DRIVERS HEADER */
#include "pc_drv.h"


/*************************************************************************
*                       DECLARE GLOBAL VARIABLES                         *
*************************************************************************/

int  GraphDriver;             /* Graphics device driver */
int  GraphMode;               /* Graphics mode value */
int  ErrorCode;               /* Reports any graphics errors */
extern int ScreenWidth,
           ScreenHeight;      /* Dimensions of graphics screen */


/*************************************************************************
*                START OF DEVICE DRIVERS FOR THE IBM PC                  *
*************************************************************************/

void PC_Activate_graphics( void )
/*************************************************************************
*  Function: PC_Activate_graphics                                        *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Activates the graphics system and reports any errors which occured.   *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  request auto-detection                                                *
*  read result of initialization                                         *
*  check if an error occured while initializing graphics                 *
*  get screen dimensions                                                 *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  none                                                                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  initgraph                                                             *
*  graphresult                                                           *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Global: ScreenWidth, ScreenHeight - dimensions of graphics screen     *
*  error message if an error occured                                     *
*************************************************************************/
{

/* request auto-detection  */
GraphDriver = DETECT;
initgraph( &GraphDriver, &GraphMode, "" );

/* read result of initialization */
ErrorCode = graphresult();

/* check if an error occured while initializing graphics */
if( ErrorCode != grOk ){
 printf(" Graphics System Error: %s\n", grapherrormsg( ErrorCode ) );
 exit( 1 );
}

/* get screen dimensions */
ScreenWidth = getmaxx();
ScreenHeight = getmaxy();

} /* -- END OF FUNCTION -- */


void PC_Deactivate_graphics( void )
/*************************************************************************
*  Function: PC_Deactivate_graphics                                      *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Closes the graphics system and returns screen to previous mode        *
*  (i.e. text)                                                           *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  none                                                                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  closegraph                                                            *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  none                                                                  *
*************************************************************************/
{

/* close the graphics system */
closegraph();

} /* -- END OF FUNCTION -- */


void PC_Draw_border( void )
/*************************************************************************
*  Function: PC_Draw_border                                              *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Draws a bounding box around the region to be contoured                *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global: wxmin, wymin - lower left coordinates of bounding box         *
*          wxmax, wymax - upper right coordinates of bounding box        *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  rectangle                                                             *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  displays bounding box and bounding box coordinates                    *
*************************************************************************/
{

/* draw a rectangle the dimensions of the viewport on the monitor */
rectangle( floor(vpxmin*ScreenWidth), ceil(vpymax*ScreenHeight),
           ceil(vpxmax*ScreenWidth),  floor(vpymin*ScreenHeight) );

} /* -- END OF FUNCTION -- */


void PC_Draw_to( REAL x, REAL y )
/*************************************************************************
*  Function: PC_Draw_to                                                  *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Draws a line from the current screen coordinate to the new screen     *
*  coordinate                                                            *
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

int sx,sy;    /* screen x,y coord */

/* get screen coords */
sx = (int)(x*ScreenWidth);
sy = (int)(y*ScreenHeight);

/* draw a line to screen coords */
lineto(sx,ScreenHeight-sy);

} /* -- END OF FUNCTION -- */


void PC_Draw_text( int x, int y, char string[] )
/*************************************************************************
*  Function: PC_Draw_text                                                *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Draws a text string on the screen at the specified screen coordinate  *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: x,y    - screen coordinate                                 *
*             string - text string to be displayed                       *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  settextstyle                                                          *
*  outtextstyle                                                          *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  string displayed on screen                                            *
*************************************************************************/
{

/* set the text style */
settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
/* output text at the screen coords */
outtextxy(x,ScreenHeight-y,string);

} /* -- END OF FUNCTION -- */


void PC_Graphics_pause( void )
/*************************************************************************
*  Function: PC_Graphics_pause                                           *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Pauses the graphics screen until the user decides to exit             *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  repeat while the user has not pressed return (Carriage Return)        *
*     clear the keyboard buffer                                          *
*     get character from keyboard                                        *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  none                                                                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  none                                                                  *
*************************************************************************/
{

int c;   /* character read from keyboard */

/* repeat while the user has not pressed return (Carriage Return) */
do {
  /* clear the keyboard buffer */
  fflush(stdin);
  /* get character from keyboard */
  c = getc(stdin);
} while (c != CR);

} /* -- END OF FUNCTION -- */


void PC_Move_to( REAL x, REAL y )
/*************************************************************************
*  Function: PC_Move_to                                                  *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Moves to a new position on the screen                                 *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: x,y - new screen coordinate                                *
*             ScreenWidth, ScreenHeight - dimensions of screen           *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  moveto                                                                *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  none                                                                  *
*************************************************************************/
{

int sx,sy;    /* screen x,y coordinate */

sx = (int)(x*ScreenWidth);
sy = (int)(y*ScreenHeight);

moveto(sx,ScreenHeight-sy);

} /* -- END OF FUNCTION -- */


void PC_Set_colour( int col )
/*************************************************************************
*  Function: PC_Set_colour                                               *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Sets the current drawing colour                                       *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  col - colour to be used for output                                    *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  setcolor                                                              *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  none                                                                  *
*************************************************************************/
{

/* set the current drawing colour */
setcolor(col);

} /* -- END OF FUNCTION -- */


void PC_Set_linestyle( int line_type )
/*************************************************************************
*  Function: PC_Set_linestyle                                            *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Sets the current line style for drawing lines                         *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: line_type - the type of line to use                        *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  setlinestyle                                                          *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  none                                                                  *
*************************************************************************/
{

/* select line style */
switch(line_type) {
 case 1 : /* dotted line - normal width */
     setlinestyle(DOTTED_LINE,EMPTY_FILL,NORM_WIDTH);
     break;
 case 2 : /* dashed line - normal width */
     setlinestyle(DASHED_LINE,EMPTY_FILL,NORM_WIDTH);
     break;
 case 3 : /* solid line - normal width */
     setlinestyle(SOLID_LINE,EMPTY_FILL,NORM_WIDTH);
     break;
 case 4 : /* dotted line - thick width */
     setlinestyle(DOTTED_LINE,EMPTY_FILL,THICK_WIDTH);
     break;
 case 5 : /* dashed line - thick width */
     setlinestyle(DASHED_LINE,EMPTY_FILL,THICK_WIDTH);
     break;
 case 6 : /* solid line - thick width */
     setlinestyle(SOLID_LINE,EMPTY_FILL,THICK_WIDTH);
     break;
 } /* end of cases */

} /* -- END OF FUNCTION -- */

/*************************************************************************
*                  END OF DEVICE DRIVERS FOR THE IBM PC                  *
*************************************************************************/

