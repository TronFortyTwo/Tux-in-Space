/*
#############################################################################################
#    CSpace - space simulator																#
#    Copyright (C) 2016  emanuele.sorce@hotmail.com											#
#																							#
#    This program is free software; you can redistribute it and/or modify					#
#    it under the terms of the GNU General Public License as published by					#
#    the Free Software Foundation, version 3 or compatibles.								#
#																							#
#    This program is distributed in the hope that it will be useful,						#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of							#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the							#
#    GNU General Public License for more details.											#
#																							#
#    You should have received a copy of the GNU General Public License						#
#    along with this program; if not, write to the Free Software							#
#    Foundation, Inc.																		#
#############################################################################################
 *
 * This is CSpace header file
 * 
 */

#ifndef generich
#define generich

/////////////////////////////////////////////////////
// This is the flag that active/deactive debug. (1/0)
// A debugless binary is lighter and faster, but is debugless

#define DEBUG 0

/////////////////////////////////////////////////////



// External standard library
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdint.h>
#include <SDL2/SDL.h>
	
// Is important the YES = ON and OFF = NO
#define ON 1
#define OFF 0
#define NO OFF
#define YES ON
		
// The three axis must have different codes
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

// A three char string that represent a picture of ALLERT or ATTENCTION
#define IRREGULARITY "(!)"
	
// Values returned by functions
#define GOODSIGNAL 1
#define BADSIGNAL 2
#define FILE_ERR_SIG 3
#define CORRUPTED_SIG 4
#define NEW_SIG 5
#define LOAD_SIG 6
#define QUITSIGNAL -1			// is even the value that the variable ttime.year assumes if the user want to quit, so must be negative!
	
// The lenght of a name of an object, a system or a type
#define NAMELUN 64

// The video mode
#define V_OPS 0
#define V_SDL 1

// The files and directoryes
#define DEBUG_FILE "debug.dbg"				// Where are printed debug settingrmation
#define DEBUG_FILE_LENGHT 10				// The size of DEBUG_FILE
#define TYPE_DATABASE_FILE "type.typ"		// Where read type settingrmation
#define CONFIGURATION_FILE "cspace.conf"	// Where read configuration settingrmation
#define OBJECT_PATH "Objects/"				// Where save/load systems
#define SYSTEM_PATH "Systems/"				// Where save/load objects
	
	
// A two-in-one function call whitout argurment (safe getchar)
#define sgetchar() (scanf(" "), getchar())
	
// More precise data types
typedef 	int8_t		BYTE;	// max +/- 128
typedef 	int16_t 	WORD;	// max +/- 32768
typedef		int32_t		DWORD;
typedef		int64_t		QWORD;

// the string that contein a name of a type/system/object (deprecated, I'll switch to dinamically allocated buffers)
typedef char TNAME[NAMELUN];

/*
 * The structure menu_Settings is a structure that contein settings and other tecnical things 
 */
typedef struct settingOPS {
	unsigned int width;				// The number of columns that the program use
	unsigned int height;			// The number of lines that the program use
	unsigned int numprecision;		// Number of character used for printing the deciamal of a long double
} tsetOPS;
	
typedef struct settingGl {
	SDL_Window *win;			// the window
	BYTE SDLinit;				// YES if SDL is initialized, NO if not
	BYTE winopen;				// YES if the window is opened, NO if not
	float framerate;			// the framerate wanted of the program	
} tsetgl;
	
typedef struct Settings {
	int vmode;		// Visual mode
	tsetOPS ops;	// OPS settings
	tsetgl gl;		// Window and OpenGL settings
} tset;
	
//////////// THE ONLY GLOBAL VARIABLE /////////////
tset set;
////////////////////////////////////////////////////

#endif
