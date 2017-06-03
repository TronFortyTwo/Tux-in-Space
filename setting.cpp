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
 */

#include "setting.h"

// Internal constants
// Default values for the set structure
#define DEFAULT_OPS_HEIGHT 			48
#define DEFAULT_OPS_WIDTH 			68

using namespace std;

/***
 * set_Save save in a file the config of tset set
 */
void setting::Save() {
	
	ofstream cf(CONFIGURATION_FILE);
	if(!cf) {
		debug_Printf(IRREGULARITY" setting::Save() Can't open the - " CONFIGURATION_FILE " - file");
		return;
	}
	cf << height << "\n" << width << "\n";
}
	
/***
 * set_Init is a function that load from the config file 
 */
setting::setting() {
	
	ifstream cf(CONFIGURATION_FILE);
	// If there is a file
	if(cf) {
		// scan OPS settings
		cf >> height;
		cf >> width;
	}
	// if not, load defaults
	else 
		Defaults();
}
	
/***
 * This function reset the settings to the default values
 */
void setting::Defaults(){
	
	height = DEFAULT_OPS_HEIGHT;
	width = DEFAULT_OPS_WIDTH;
}

/***
 * This function initializes the directories if them doesn't exist
 * NOTE:
 * 	This function works only in *nix! Is not portable!
 */
signal setting::InitDir() {
	// The state of the directories
	struct stat st = {0};
	// Check for the object directory and Create it if not present
	if (stat(OBJECT_PATH, &st) == -1) {
		mkdir(OBJECT_PATH, 0700);
		// Check that the directories has been created succefully
		if (stat(OBJECT_PATH, &st) == -1)
			return signal::file_err;
	}
	// Check for the system directory and Create it if not present
	if (stat(SYSTEM_PATH, &st) == -1) { 
		mkdir(SYSTEM_PATH, 0700);	
		// Check that the directories has been created succefully
		if (stat(SYSTEM_PATH, &st) == -1)
			return signal::file_err;
	}
		
	return signal::good;
}
