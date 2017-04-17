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
 * Generic stuff
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
// A debugless binary is lighter and faster

#define DEBUG ON

/////////////////////////////////////////////////////

#include <limits>
#include <cstdint>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <fstream>

		
// The three axis must have different codes
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

// A three char string that represent a picture of ALLERT or ATTENCTION
#define IRREGULARITY "(!)"
	
// Values returned by functions
#define GOOD_SIG		1	// good
#define BAD_SIG			2	// generic bad
#define FILE_ERR_SIG	3	// file not found
#define CORRUPTED_SIG	4	// file ureadable
#define NEW_SIG			5	// new
#define LOAD_SIG		6	// load
#define ABORTED_SIG		7	// aborted action

// The video mode
#define V_OPS 0
#define V_GL 1

// The files and directoryes
#define DEBUG_FILE "debug.dbg"				// Where are printed debug information
#define TYPE_DATABASE_FILE "type.typ"		// Where read type information
#define CONFIGURATION_FILE "cspace.conf"	// Where read configuration inormation
#define OBJECT_PATH "Objects/"				// Where save/load systems
#define SYSTEM_PATH "Systems/"				// Where save/load objects


// More precise data types
typedef 	int8_t		BYTE;
typedef 	int16_t 	WORD;
typedef		int32_t		DWORD;
typedef		int64_t		QWORD;
typedef 	uint8_t		UBYTE;
typedef 	uint16_t 	UWORD;
typedef		uint32_t	UDWORD;
typedef		uint64_t	UQWORD;

#endif
