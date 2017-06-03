/*
#############################################################################################
#    Tux in Space - space exploration game													#
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

#include <limits>
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <experimental/filesystem>
//#include <SDL2/SDL.h>

// What interface to use?
// new proof of concrpt graphic GUI
#define iSDL false
// legacy OPS() based UI
#define iOPS true

// The three axis must have different codes
enum class axis3 {x, y, z};
enum class axis2 {x, y};

// A string that represents a picture of ALLERT, ATTENCTION, ERROR or similar
#define IRREGULARITY "(!)"
	
// Value returned by functions
// TODO: add more signal types for more precise use cases
enum class signal {
	good,		// good
	file_err,	// problem with file accessing or reading/writing
	corrupted,
	create,
	load,
	aborted		// aborted action
};

enum class comparison{ major, minor, equal };

// The files and directoryes
#define DEBUG_FILE "debug.dbg"				// Where are printed debug information
#define TYPE_DATABASE_FILE "type.typ"		// Where read type information
#define CONFIGURATION_FILE "tuxinspace.conf"	// configuration file
#define OBJECT_PATH "Objects/"				// Where save/load systems
#define SYSTEM_PATH "Systems/"				// Where save/load objects

#define BANNER "Code hosted on GitHub: http://github.com/TronFourtyTwo/Tux in Space\n\nLICENSE: \
GNU GPL V3\n\n Tux in Space - space simulator\nCopyright (C) 2016-2017  emanuele.sorce@hotmail.com\
\n\nThis program is free software; you can redistribute it and/or modify \
it under the terms of the GNU General Public License as published by the \
Free Software Foundation, version 3 or compatibles. This program is distributed \
in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even \
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  \
See the GNU General Public License version 3 for more details.\n\nYou should \
have received a copy of the GNU General Public License version 3 along with this program; \
if not, write to the Free Software Foundation, Inc."

#endif
