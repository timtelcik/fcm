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

/* OPENGL_DRV.C
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
*  DEVICE DRIVER FOR SILICON GRAPHICS PERSONAL OPENGL                    *
*                                                                        *
*  Written by Tim Telcik                                                 *
*  Last Update: 5th October 1991                                         *
*  Last Update: 2nd November 2013                                        *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Contains device dependent drivers for OpenGL                          *
*  called from routines in DISPLAY.C.                                    *
*                                                                        *
*  Routines Included                                                     *
*  -----------------                                                     *
*  OPENGL_Activate_graphics                                              *
*  OPENGL_Deactivate_graphics                                            *
*  OPENGL_Draw_border                                                    *
*  OPENGL_Draw_text                                                      *
*  OPENGL_Draw_to                                                        *
*  OPENGL_Graphics_pause                                                 *
*  OPENGL_Move_to                                                        *
*  OPENGL_Set_colour                                                     *
*  OPENGL_Set_line_style                                                 *
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

/* INCLUDE OPENGL DEVICE DRIVERS HEADER */
#include "opengl_drv.h"

#define WIN_TITLE FALCON_VERSION_LABEL
#define WIN_WIDTH 768
#define WIN_HEIGHT 576


/*************************************************************************
*                       DECLARE PROTOTYPES
*************************************************************************/

void GLUT_Draw_Text( REAL x, REAL y, char *text );


/*************************************************************************
*                       DECLARE GLOBAL VARIABLES                         *
*************************************************************************/

extern int ScreenWidth;     /* Dimensions of graphics screen */
extern int ScreenHeight;    /* Dimensions of graphics screen */
GLFWwindow* window;         /* GLWD window where graphics are displayed */


/*************************************************************************
*               START OF DEVICE DEPENDENT ROUTINES FOR THE OPENGL        *
*************************************************************************/

static void glfw_error_callback(int error, const char* description) {
        fputs(description, stderr);
}


static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action,
                int mods)
{

		printf("User key %d \n", key);

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        		printf("User key ESCAPE \n");
                glfwSetWindowShouldClose(window, GL_TRUE);
        }
}


void OPENGL_Activate_graphics( void )
/*************************************************************************
*  Function: OPENGL_Activate_graphics                                    *
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

	printf("OPENGL_Activate_graphics \n");

	/* get screen dimensions (i.e. PAL format) */
	ScreenWidth = WIN_WIDTH;
	ScreenHeight = WIN_HEIGHT;

	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) {
		fprintf( stderr, "ERROR: Could not init GLFW rendering engine.\n");
		exit(EXIT_FAILURE);
	}

	/*
	 // https://earthserver.com/Setting_up_a_modern_C%2B%2B_development_environment_on_OSX#Install_GLFW
	 glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	 glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	 glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	 glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	 glfwOpenWindow(800, 600, 0, 0, 0, 0, 24, 8, GLFW_WINDOW);
	 */

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(ScreenWidth, ScreenHeight, WIN_TITLE, NULL, NULL);
// window = glfwCreateWindow(ScreenWidth, ScreenHeight, FALCON_VERSION_LABEL, NULL, NULL);

	if (!window) {
		fprintf( stderr, "ERROR: Could not create a new rendering window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, glfw_key_callback);

	glClear(GL_COLOR_BUFFER_BIT);

// set the background (clearing) color to RGB black = RGB(0,0,0)
	glClearColor(0.0, 0.0, 0.0, 0.0);

// set the background (clearing) color to RGB light gray = RGB(190,190,190)
// glClearColor(0.75, 0.75, 0.75, 0.75);

// set the foreground color to RGB blue RGB(0,0,1)
	glColor3f(0.0, 0.0, 1.0);

	float ratio;
	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	printf("width %d, height %d \n", width, height);

	ratio = width / (float) height;
	printf("ratio %.2f \n", ratio);

// http://www.opengl.org/sdk/docs/man/xhtml/glViewport.xml
// glViewport specifies the affine transformation of x and y from normalized device coordinates to window coordinates.
// Is this also the default setting?
// glViewport(0, 0, ScreenWidth, ScreenHeight);
	glViewport(0, 0, width, height);

// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

// Create an orthgraphic view matrix going from -1 -> 1 in each dimension on the screen (x, y, z).
// The glOrtho function multiplies the current matrix by an orthographic matrix.
// glOrtho(-1, 1, -1, 1, -1, 1);

// Create an orthgraphic view matrix going from [0..screenWidth,0..screenHeight] for (x,y) and [0..1] for z.
// glOrtho(0, ScreenWidth, ScreenHeight, 0, 0, 1);

// Create an orthgraphic view matrix going from [0..1,0..1] for (x,y) and [-1..1] for z.
// void glOrtho(GLdouble  left,  GLdouble  right,  GLdouble  bottom,  GLdouble  top,  GLdouble  nearVal,  GLdouble  farVal);
// see http://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
// see http://www.opengl.org/sdk/docs/man2/xhtml/gluOrtho2D.xml
	glOrtho(0, 1, 0, 1, -1, 1);

// Define model view
// TODO: Review purpose and usage in OpenGL setup process
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

// disable 3D check
	glDisable(GL_DEPTH_TEST);

	printf("INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

} /* -- END OF FUNCTION -- */



// Return TRUE if graphics are active
BOOLEAN OPENGL_Is_graphics_active( void ) {

	// printf( "OPENGL_Is_graphics_active \n");

   BOOLEAN active = TRUE;

   if (glfwWindowShouldClose(window)) {
	   active = FALSE;
	   printf( "OPENGL_Is_graphics_active: %d \n",active);
   }

	// printf( "OPENGL_Is_graphics_active: %d \n",active);

   return active;
}


// Poll for keyboard and mouse events
void OPENGL_Poll_events( void ) {

	// printf("OPENGL_Poll_events \n");

    glfwPollEvents();

}


void OPENGL_Deactivate_graphics( void )
/*************************************************************************
*  Function: OPENGL_Deactivate_graphics                                    *
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

printf("OPENGL_Deactivate_graphics \n");

glfwDestroyWindow(window);

glfwTerminate();

} /* -- END OF FUNCTION -- */


void OPENGL_Draw_border( void )
/*************************************************************************
*  Function: OPENGL_Draw_border                                            *
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

printf("Draw border \n");

// display a rectangle the dimensions of the viewport on the monitor

/*
float x1 = -0.75f;
float y1 = -0.75f;
float x2 = 0.75f;
float y2 = 0.75f;
*/

float x1 = 0.15f;
float y1 = 0.15f;
float x2 = 0.85f;
float y2 = 0.85f;

// printf("OPENGL_Draw_border: glRectf(%.2f,%.2f,%.2f,%.2f) \n",x1,y1,x2,y2);

/*
// draw rect solid
// http://www.opengl.org/sdk/docs/man2/xhtml/glRect.xml
// http://en.wikibooks.org/wiki/OpenGL_Programming/Basics/Rectangles
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glColor3f(0.0f, 0.0f, 1.0f);
glRectf(-0.75f,0.75f, 0.75f, -0.75f);
*/

// draw rect outline
// http://www.swiftless.com/tutorials/opengl/square.html
glBegin(GL_LINE_LOOP);
// glColor3d(0,0,1);
// glColor3f(0.0f, 0.0f, 1.0f);
glVertex2f(x1, y1);
glVertex2f(x2, y1);
glVertex2f(x2, y2);
glVertex2f(x1, y2);
glEnd();

// trigger immediate render
glFlush();

} /* -- END OF FUNCTION -- */


void OPENGL_Flush_graphics( void ) {
   printf("Flush graphics \n");
   glfwSwapBuffers(window);
}


void OPENGL_Draw_text( REAL x, REAL y, char text[] )
/*************************************************************************
*  Function: OPENGL_Draw_text                                            *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Draws a text string on the screen at the specified screen coordinate. *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: x,y    - screen coordinate                                 *
*             text   - text string to be displayed                       *
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

	printf("OPENGL_Draw_text: Draw text at NDC (%.2f,%.2f) : \"%s\" \n", x, y, text);

	// TODO: remove colour CYAN
	OPENGL_Set_colour(CYAN);

	GLUT_Draw_Text( x, y, text );

} /* -- END OF FUNCTION -- */


/*************************************************************************
*  Function: GLUT_Draw_Text                                              *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Draws text a NDC location.                                            *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: x,y - NDC                                                  *
*                                                                        *
*  Calls                                                                 *
*  -----                                                                 *
*  glutBitmapCharacter                                                   *
*                                                                        *
*  Outputs                                                               *
*  -------                                                               *
*  Displays text at NDC location.                                        *
*************************************************************************/
// http://www.idevgames.com/forums/thread-6250.html
// http://www.idevgames.com/forums/thread-6250.html
// http://www.opengl.org/discussion_boards/showthread.php/143335-GLUT-to-display-text
// http://www.opengl.org/archives/resources/features/KilgardTechniques/oglpitfall/
//
// NOTE: glutBitmapCharacter is deprecated
//    opengl_drv.c:424:6: warning: 'glutBitmapCharacter' is deprecated: first deprecated in OS X 10.9 [-Wdeprecated-declarations]
//    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[count]);
void GLUT_Draw_Text( REAL x, REAL y, char *text )
{
	// glDisable(GL_TEXTURE_2D);
  int len, i;
  glRasterPos2f( x, y );
  len = (int) strlen(text);
  printf("GLUT_Draw_Text: Location of |%s| is (%.2f,%.2f) \n", text, x, y);
  printf("GLUT_Draw_Text: Length of |%s| is |%d| \n", text, len);
  for (i = 0; i < len; i++)
  {
    // glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, text[i] );
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
  }
	// glEnable(GL_TEXTURE_2D);
}


void OPENGL_Draw_to( REAL x, REAL y )
/*************************************************************************
*  Function: OPENGL_Draw_to                                              *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Draws a line from the current screen coordinate to the new screen     *
*  coordinate.                                                           *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: x,y - NDC                                                  *
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

// draw a line to new screen coordinate
printf("OPENGL_Draw_to: glVertex2f(%.2f,%.2f) \n",x,y);
glVertex2f(x, y);

} /* -- END OF FUNCTION -- */


void OPENGL_Graphics_pause( void )
/*************************************************************************
*  Function: OPENGL_Graphics_pause                                         *
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

int c;   // character read from keyboard

// repeat while the user has not pressed return (Carriage Return)
do {
  // clear the keyboard buffer
  fflush(stdin);
  c = getc(stdin);
} while (c != CR);

} /* -- END OF FUNCTION -- */


void OPENGL_Move_to( REAL x, REAL y )
/*************************************************************************
*  Function: OPENGL_Move_to                                              *
*                                                                        *
*  Purpose                                                               *
*  -------                                                               *
*  Moves to the graphics cursor to a new position on the screen.         *
*                                                                        *
*  Inputs                                                                *
*  ------                                                                *
*  Parameter: x,y - NDC                                                  *
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

printf("OPENGL_Move_to: glVertex2f(%.2f,%.2f) \n",x,y);
glVertex2f(x, y);

} /* -- END OF FUNCTION -- */


void OPENGL_Set_colour( int col )
/*************************************************************************
*  Function: OPENGL_Set_colour                                           *
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

	// see http://www.tayloredmktg.com/rgb/

	// set the current drawing colour
	printf("OPENGL_Set_colour(%d) \n",col);

	if (col == BLACK) {
		glColor3f(0.0f, 0.0f, 0.0f);

	} else if (col == BLUE) {
		glColor3f(0.0f, 0.0f, 1.0f);

	} else if (col == RED) {
		glColor3f(1.0f, 0.0f, 0.0f);

	} else if (col == GREEN) {
		glColor3f(0.0f, 1.0f, 0.0f);

	} else if (col == MAGENTA) {
		glColor3f(1.0f, 0.0f, 1.0f);

	} else if (col == CYAN) {
		glColor3f(0.0f, 1.0f, 1.0f);

	} else if (col == YELLOW) {
		glColor3f(1.0f, 1.0f, 0.0f);

	} else if (col == WHITE) {
		glColor3f(1.0f, 1.0f, 1.0f);

	} else if (col == COL_GRAY) {
		glColor3i( 190, 190, 190 );

	} else if (col == COL_LIGHT_GRAY) {
		glColor3i( 211, 211, 211 );

	} else {
		printf("Unknown color code: %d \n",col);

	}

} /* -- END OF FUNCTION -- */


void OPENGL_Set_line_style( int line_type )
/*************************************************************************
*  Function: OPENGL_Set_line_style                                        *
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

	// http://www.felixgers.de/teaching/jogl/stippledLines.html

printf("OPENGL_Set_line_style: set line style : %d \n",line_type);

	// select line style

	switch (line_type) {

		case LINE_STYLE_DOTTED: {
			fprintf( stderr, "Not implemented - Ignoring line style: %d \n",
					line_type);
			glLineStipple(1, 0xAAAA);
			break;
		}
		case LINE_STYLE_DASHED: {
			// glLineStipple(2, 255);
			glLineStipple(2, 0xAAAA);
			break;
		}
		case LINE_STYLE_SOLID: {
			fprintf( stderr, "Not implemented - Ignoring line style: %d \n",
					line_type);
			glLineStipple(1, 0xFFFF);
			break;
		}
		case LINE_STYLE_DASHED_DOTTED: {
			fprintf( stderr, "Not implemented - Ignoring line style: %d \n",
					line_type);
			// glLineStipple(4, 3135);
			break;
		}
		default: {
			fprintf( stderr, "Unknown line style: %d \n", line_type);
			break;
		}

	} // end of cases

} /* -- END OF FUNCTION -- */


// TODO: add function header
void OPENGL_Begin_line_style( void ) {
	glEnable(GL_LINE_STIPPLE);
}


// TODO: add function header
void OPENGL_End_line_style( void ) {
	glDisable(GL_LINE_STIPPLE);
}


// TODO: add function header
void OPENGL_Begin_line_loop( void )
{
	printf("Begin line loop \n");
	 glBegin(GL_LINE_LOOP);
}


// TODO: add function header
void OPENGL_Begin_line( void )
{
	printf("Begin line \n");
	 glBegin(GL_LINES);
}


// TODO: add function header
void OPENGL_Begin_line_strip( void )
{
	printf("Begin line strip \n");
	 glBegin(GL_LINE_STRIP);
}


// TODO: add function header
void OPENGL_End_line_loop( void )
{
	printf("End line loop \n");
	 glEnd();
}


// TODO: add function header
void OPENGL_End_line( void )
{
	printf("End line \n");
	 glEnd();
}


// TODO: add function header
void OPENGL_End_line_strip( void )
{
	printf("End line strip \n");
	 glEnd();
}


/*************************************************************************
*                END OF DEVICE DEPENDENT DRIVERS FOR OPENGL              *
*************************************************************************/

