/*
#############################################################################################
#    CSpace - space simulator																#
#    Copyright (C) 2016-2017  emanuele.sorce@hotmail.com									#
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

// Is important the YES = ON and OFF = NO
#define ON 1
#define OFF 0
#define NO OFF
#define YES ON

/////////////////////////////////////////////////////
// This is the flag that active/deactive debug. (ON/OFF)
// A debugless binary is lighter and faster, but is debugless

#define DEBUG ON

/////////////////////////////////////////////////////



// External standard library
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdint.h>
#include "OnlyPrintfSystem.h"
	
		
// The three axis must have different codes
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

// A three char string that represent a picture of ALLERT or ATTENCTION
#define IRREGULARITY "(!)"
	
// Values returned by functions
#define GOODSIGNAL 1	// good
#define BADSIGNAL 2		// generic bad
#define FILE_ERR_SIG 3
#define CORRUPTED_SIG 4
#define NEW_SIG 5
#define LOAD_SIG 6
#define ABORTED_SIG 7
#define QUITSIGNAL -1			// is even the value that the variable ttime.year assumes if the user want to quit, so must be negative!

// The video mode
#define V_OPS 0
#define V_GL 1

// The files and directoryes
#define DEBUG_FILE "debug.dbg"				// Where are printed debug settingrmation
#define DEBUG_FILE_LENGHT 10				// The size of DEBUG_FILE
#define TYPE_DATABASE_FILE "type.typ"		// Where read type settingrmation
#define CONFIGURATION_FILE "cspace.conf"	// Where read configuration settingrmation
#define OBJECT_PATH "Objects/"				// Where save/load systems
#define SYSTEM_PATH "Systems/"				// Where save/load objects
	
	
// A two-in-one macro whitout argurment (safe getchar)
#define sgetchar() (scanf(" "), getchar())

// More precise data types
typedef 	int8_t		BYTE;	// max +/- 128
typedef 	int16_t 	WORD;	// max +/- 32768
typedef		int32_t		DWORD;
typedef		int64_t		QWORD;

// the string as long as the max lenght of a type/system/object name
// to use carefully because is very long, use dinamically allocated strings instead where possible
#define NAMELUN 128
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
	// Coming soon
} tsetgl;
	
typedef struct Settings {
	int vmode;		// Visual mode
	tsetOPS ops;	// OPS settings
	tsetgl gl;		// Window and OpenGL settings
} tset;
	
//////////// THE ONLY GLOBAL VARIABLE /////////////
tset set;
////////////////////////////////////////////////////

// the function that will allocate a bunch of RAM in the heap
void *alloc_heap (size_t, char *);

#endif
