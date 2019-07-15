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

/* DISPLAY.C
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
*  DISPLAY ROUTINES                                                      *
*                                                                        *
*  Written by Tim Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Contains routines for displaying information (eg. lines, text) to the *
*  screen using a window/viewport combination which is based upon the GKS*
*  concept. Routines containing graphics commands for a specific machine *
*  have been isolated from this code so that these routines are device   *
*  independent.                                                          *
*                                                                        *
*  If you want to write your own device drivers see files 'OPENGL_DRV.C' *
*  and 'IRIS_DRV.C' to see how the device drivers have been set up.      *
*  Change the calling names in the DISPLAY routines to the names of your *
*  device drivers.                                                       *
*                                                                        *
*  Routines Included                                                     *
*  -----------------                                                     *
*  Activate_graphics                                                     *
*  Deactivate_graphics                                                   *
*  Draw_border                                                           *
*  Draw_border_coords                                                    *
*  Draw_cont_info                                                        *
*  Draw_to                                                               *
*  Draw_text                                                             *
*  Graphics_pause                                                        *
*  Move_to                                                               *
*  Set_colour                                                            *
*  Set_line_style                                                        *
*  Set_viewport                                                          *
*  Set_window                                                            *
*  Transform                                                             *
*************************************************************************/

/*************************************************************************
*                           INCLUDE HEADER FILES                         *
*************************************************************************/

/* INCLUDE STANDARD HEADERS */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* INCLUDE FALCON CONSTANTS HEADER */
#include "const.h"

/* INCLUDE FALCON TYPE DEFINITIONS */
#include "types.h"

/* INCLUDE FALCON GRAPHICS DISPLAY HEADER */
#include "display.h"


/*************************************************************************
*                             DECLARE GLOBAL VARIABLES                   *
*************************************************************************/

RECTANGLE Window;       // World coordinate (WC) window
RECTANGLE Viewport;     // Normalized device coordinate (NDC) viewport
int ScreenWidth;        // Screen width
int ScreenHeight;       // Screen height


/*************************************************************************
*                        START OF FALCON DISPLAY ROUTINES                *
*************************************************************************/

void Activate_graphics( void )
/*************************************************************************
*  Function: Activate_graphics                                           *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Activates the graphics system.                                        *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  none                                                                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  OPENGL_Activate_graphics                                              *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  see deivce dependent routine                                          *
*************************************************************************/
{

/* call device dependent routine */
#ifdef FCM_GRAPHICS_DRIVER_OPENGL
OPENGL_Activate_graphics();
#endif

} /* -- END OF FUNCTION -- */


void Deactivate_graphics( void )
/*************************************************************************
*  Function: Deactivate_graphics                                         *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Deactivates the graphics system.                                      *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  none                                                                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  OPENGL_Deactivate_graphics                                            *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  see device dependent routine                                          *
*************************************************************************/
{

/* call device dependent routine */
OPENGL_Deactivate_graphics();
// IRIS_Deactivate_graphics();

} /* -- END OF FUNCTION -- */


/**
* Returns TRUE if graphics mode is active
*/
BOOLEAN Is_graphics_active( void ) {
	return OPENGL_Is_graphics_active();
}


/*************************************************************************
*                                                                        *
* Poll keyboard and mouse events.                                        *
*                                                                        *
*************************************************************************/
void Poll_events( void ) {
   OPENGL_Poll_events();
}


void Draw_border( void )
/*************************************************************************
*  Function: Draw_border                                                 *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Draws a bounding box the size of the viewport.                        *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global: wxmin, wymin - lower left coordinate of bounding box          *
*          wxmax, wymax - upper right coordinates of bounding box        *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  OPENGL_Draw_border                                                    *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  see device dependent routine                                          *
*************************************************************************/
{

// call device dependent routine
OPENGL_Draw_border();
// IRIS_Draw_border();

} /* -- END OF FUNCTION -- */


void Draw_border_coords( REAL wxmin, REAL wymin, REAL wxmax, REAL wymax )
/*************************************************************************
*  Function: Draw_border_coords                                          *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Displays lower left and upper right coordinates of the region to be   *
*  contoured at opposite vertices of viewport bounding box.              *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global:    ScreenWidth, ScreenHeight - dimensions of monitor screen   *
*  Parameter: wxmin, wymin - lower left coordinates                      *
*             wxmax, wymax - upper right coordinates                     *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  Draw_text                                                             *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  displays viewport bounding box coordinates                            *
*************************************************************************/
{

char coord[90];   /* string containing coordinates */
char num[40];     /* string containing number */

printf("Draw_borer_coords: (%.2f,%.2f) (%.2f,%.2f) \n", wxmin, wymin, wxmax, wymax );

// convert coords of lower left vertex to a string and display
strcpy(coord,"(");
sprintf(num,"%.0f",floor(wxmin));
strcat(coord,num);
strcat(coord,",");
sprintf(num,"%.0f",floor(wymin));
strcat(coord,num);
strcat(coord,")");
Draw_text(0.05, 0.1, coord);

// convert coordinates of upper right vertex to a string and display
strcpy(coord,"(");
sprintf(num,"%.0f",ceil(wxmax));
strcat(coord,num);
strcat(coord,",");
sprintf(num,"%.0f",ceil(wymax));
strcat(coord,num);
strcat(coord,")");
Draw_text(0.75, 0.9, coord);

} /* -- END OF FUNCTION -- */


void Draw_cont_info( REAL lower_contour, REAL upper_contour,
		     REAL contour_interval)
/*************************************************************************
*  Function: Draw_cont_info                                              *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Displays the contour information (lower and upper contour bounds and  *
*  contour interval) to the screen.                                      *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global:    ScreenWidth, ScreenHeight - dimensions of monitor screen   *
*  Parameter: lower_contour, upper_contour - lower and upper contour     *
*                                            bounds                      *
*             contour_interval - vertical distance between contours      *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  Draw_text                                                             *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  displays contour information                                          *
*************************************************************************/
{

char title[100];      /* string containing title */
char num[40];        /* string containing number */

// convert contour info. to a string and display
strcpy(title,"Contour Range: ");
sprintf(num,"%.2f",lower_contour);
strcat(title,num);
strcat(title," - ");
sprintf(num,"%.2f",upper_contour);
strcat(title,num);
strcat(title," ; Contour Interval: ");
sprintf(num,"%.2f",contour_interval);
strcat(title,num);
Draw_text(0.2,0.95,title);

} /* -- END OF FUNCTION -- */


void Draw_to( REAL x, REAL y )
/*************************************************************************
*  Function: Draw_to                                                     *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Plots a line from the current screen coordinate to the new screen     *
*  coordinate.                                                           *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: x,y - new screen coordinate                                *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  OPENGL_Draw_to                                                        *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  see device dependent routine                                          *
*************************************************************************/
{

/* call device dependent routine */
OPENGL_Draw_to(x,y);
// IRIS_Draw_to(x,y);

} /* -- END OF FUNCTION -- */


void Draw_text( REAL x, REAL y, char text[] )
/*************************************************************************
*  Function: Draw_text                                                   *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Plots a text string on the screen at the specified screen coordinate  *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: x,y    - NDC coordinates                                   *
*             text - text string to be displayed                         *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  OPENGL_Draw_text                                                      *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  see device dependent routine                                          *
*************************************************************************/
{

// call device dependent routine
OPENGL_Draw_text(x,y,text);
// IRIS_Draw_text(x,y,string);

} /* -- END OF FUNCTION -- */


void Graphics_pause( void )
/*************************************************************************
*  Function: Graphics_pause                                              *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Pauses the graphics screen until the user decides to exit.            *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  none                                                                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  OPENGL_Graphics_pause                                                 *
*  Draw_text                                                             *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Displays continue prompt on screen                                    *
*************************************************************************/
{

// prompt user to exit contour display
/*
Draw_text( 0.30, 0.1, "** Contouring Finished. Press RETURN. **" );
*/

// call device dependent routine
OPENGL_Graphics_pause();
// IRIS_Graphics_pause();

} /* -- END OF FUNCTION -- */


void Move_to( REAL x, REAL y )
/*************************************************************************
*  Function: Move_to                                                     *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Moves to a new position on the screen.                                *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: x,y - new screen coordinate                                *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  OPENGL_Move_to                                                            *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  see device dependent routine                                          *
*************************************************************************/
{

/* call device dependent routine */
OPENGL_Move_to(x,y);
// IRIS_Move_to(x,y);

} /* -- END OF FUNCTION -- */


void Set_colour( int col )
/*************************************************************************
*  Function: Set_colour                                                  *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Sets the current drawing/output colour                                *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  col - colour to be used for output                                    *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  OPENGL_Set_colour                                                     *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  see device dependent routine                                          *
*************************************************************************/
{

/* call device dependent routine */
OPENGL_Set_colour(col);
// IRIS_Set_colour(col);

} /* -- END OF FUNCTION -- */


// TODO: add function header
void Begin_line_style( void ) {
	OPENGL_Begin_line_style();
}


// TODO: add function header
void End_line_style( void ) {
	OPENGL_End_line_style();
}


void Set_line_style( int line_type )
/*************************************************************************
*  Function: Set_line_style                                              *
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
*  OPENGL_Set_line_style                                                 *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  see device dependent routine                                          *
*************************************************************************/
{

/* call device dependent routine */
OPENGL_Set_line_style(line_type);
// IRIS_Set_line_style(line_type);

} /* -- END OF FUNCTION -- */


void Set_viewport( REAL xmin, REAL ymin, REAL xmax, REAL ymax )
/*************************************************************************
*  Function: Set_viewport                                                *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Sets the viewport window for viewing                                  *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global:    Viewport  - window viewport                                *
*  Parameter: xmin,ymin - lower left coordinates of viewport             *
*             xmax,ymax - upper right coordinates of viewport            *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Global: Viewport - window viewport                                    *
*************************************************************************/
{

// set the viewport
Viewport.xmin = xmin;
Viewport.ymin = ymin;
Viewport.xmax = xmax;
Viewport.ymax = ymax;
Viewport.xwidth = xmax - xmin;
Viewport.ywidth = ymax - ymin;

} /* -- END OF FUNCTION -- */


void Set_window( REAL xmin, REAL ymin, REAL xmax, REAL ymax )
/*************************************************************************
*  Function: Set_window                                                  *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Sets the world window                                                 *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global:    Window    - world window                                   *
*  Parameter: xmin,ymin - lower left coordinates of window               *
*             xmax,ymax - upper right coordinates of window              *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Global: Window - world window                                         *
*************************************************************************/
{

// set window
Window.xmin = xmin;
Window.ymin = ymin;
Window.xmax = xmax;
Window.ymax = ymax;
Window.xwidth = xmax - xmin;
Window.ywidth = ymax - ymin;

} /* -- END OF FUNCTION -- */


void Transform( REAL x, REAL y, REAL *nx, REAL *ny )
/*************************************************************************
*  Function: Transform                                                   *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Transforms points from World Coordinates (WC) to Normalized Device    *
*  Coordinates (NDC)                                                     *
*                                                                        *
*  Algorithm                                                             *
*  ---------                                                             *
*  calculate width of window                                             *
*  calculate height of window                                            *
*  calculate width of viewport                                           *
*  calculate height of viewport                                          *
*  calculate scaling factor of width                                     *
*  calculate scaling factor of height                                    *
*  get minimum x in window                                               *
*  get minimum y in window                                               *
*  get minimum x in viewport                                             *
*  get minimum y in viewport                                             *
*  transform x value from WC to NDC                                      *
*  transform y value from WC to NDC                                      *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Global:    Viewport - viewport window                                 *
*             Window   - world window                                    *
*  Parameter: x,y      - (x,y) point in WC                               *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  none                                                                  *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Parameter: nx,ny  - normalized (x,y) point                            *
*                                                                        *
*  Note                                                                  *
*  ----                                                                  *
*  World Co-ordinates (WC) are any dimension the user defines.           *
*  Normalized Device Co-ordinates (NDC) are 0..1 in x direction          *
*   and 0..1 in y direction.                                             *
*************************************************************************/
{

REAL sfx, sfy;     /* scaling factors for x and y */
REAL xwmin, ywmin; /* x and y window minimums */
REAL xvmin, yvmin; /* x and y viewport minimums */
REAL lxwc, lywc;   /* length of x and y axes in WC */
REAL lxndc, lyndc; /* length of x and y axes in NDC */

// get width of window
lxwc = Window.xwidth;
// get height of window
lywc = Window.ywidth;

// get width of viewport
lxndc = Viewport.xwidth;
// get height of viewport
lyndc = Viewport.ywidth;

// calculate scaling factor for width
sfx = lxwc / lxndc;
// calculate scaling factor for height
sfy = lywc / lyndc;

// get minimum x in window
xwmin = Window.xmin;
// get minimum y in window
ywmin = Window.ymin;
// get minimum x in viewport
xvmin = Viewport.xmin;
// get minimum y in viewport
yvmin = Viewport.ymin;

// transform x value from WC to NDC
*nx = ( (x - xwmin) / sfx ) + xvmin;
// transform y value from WC to NDC
*ny = ( (y - ywmin) / sfy ) + yvmin;

} /* -- END OF FUNCTION -- */


void Flush_graphics( void )
/*************************************************************************
*  Function: Flush_graphics                                              *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Flush graphic artifacts to display device.                            *
*************************************************************************/
{
   OPENGL_Flush_graphics();
}


void Begin_line_loop( void )
{
   OPENGL_Begin_line_loop();
}


void Begin_line( void )
{
   OPENGL_Begin_line();
}


void Begin_line_strip( void )
{
	OPENGL_Begin_line_strip();
}


void End_line_loop( void )
{
   OPENGL_End_line_loop();
}


void End_line( void )
{
   OPENGL_End_line();
}


void End_line_strip( void )
{
   OPENGL_End_line_strip();
}


/*************************************************************************
*                       END OF FALCON DISPLAY ROUTINES                   *
*************************************************************************/

