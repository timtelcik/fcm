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

#ifndef FCM_GL_COLOR_H_INCLUDED
#define FCM_GL_COLOR_H_INCLUDED

/**
*
* SGI OpenGL Porting Guide 007-1797-030.pdf
*
* IRIS GL provides defined color constants: BLACK, BLUE, RED, GREEN, MAGENTA, CYAN, YELLOW, and WHITE.
* OpenGL does not provide these constants and toogl does not translate them, so you have to port them explicitly.
*
*/

#define BLACK 0
#define BLUE 1
#define RED 2
#define GREEN 3
#define MAGENTA 4
#define CYAN 5
#define YELLOW 6
#define WHITE 7

#endif // FCM_GL_COLOR_H_INCLUDED

