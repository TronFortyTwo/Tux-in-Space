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
 * Here are stuff linked whit settings
 * 
 * note:
 * 	InitDir() is granted to work on linux only
 * 
 *	HEADER FILE
 */

#ifndef settingh
#define settingh

#include "generic.h"
#include "debug.h"

// For LINUX this library is used to create directories
#include <sys/stat.h>


class setting {
	public:
		unsigned int width;			// The number of columns that OPS use
		unsigned int height;		// The number of lines that OPS use
		
		signal InitDir();	// initialize directories
		void Defaults();	// set default setting
		void Save();		// save set structure in a file
		
		setting();
	
};


#endif
