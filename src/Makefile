##
# Falcon Contour Map
#
# Copyright (C) 1991-present Tim Telcik
#
# This program is free software: you can redistribute it and/or modify it under the terms of the
# GNU General Public License as published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program. If
# not, see <http://www.gnu.org/licenses/>.
##

CC=gcc
#INCLUDES = -I ./include
INCLUDES = -I ./include -I /usr/local/include
#CFLAGS= -c -Wall
#CFLAGS = -c $(INCLUDES)
CFLAGS= -c -Wall $(INCLUDES)
#LDFLAGS= -framework OpenGL -lglfw3 -v
#LDFLAGS= -framework OpenGL -lglfw3
#LDFLAGS= -lglfw3 -framework OpenGL
#LDFLAGS= -v -L /usr/local/lib -lglfw3 -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
LDFLAGS= -v -L /usr/local/lib -lglfw3 -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework GLUT
SOURCES=display.c input.c interpol.c opengl_drv.c mainline.c output.c search.c sort.c topology.c track.c
RM=/bin/rm

OBJECTS=$(SOURCES:.c=.o)

EXECUTABLE=fcm-app

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	$(RM) *.o ${EXECUTABLE}

