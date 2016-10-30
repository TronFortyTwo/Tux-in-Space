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
 * Here are stuff linked whit settings
 */

#include "generic.h"
#include "setting.h"
// Other libraries for unix-like
#include <sys/stat.h>

// Internal constants
// Default values for the set structure
#define DEFAULT_OPS_HEIGHT 			42
#define DEFAULT_OPS_WIDTH 			88
#define DEFAULT_DEBUG 				OFF
#define DEFAULT_OPS_NUMPRECISION 	6
#define DEFAULT_V_MODE 				V_OPS

/***
 * set_Save save in a file the config of tset set
 */
void set_Save(){
	
	FILE *cf = fopen(CONFIGURATION_FILE, "w");
	
	// print the vmode
	fprintf(cf, "%d\n", set.vmode);
	// print OPS settings
	fprintf(cf, "%d\n", set.ops.height);
	fprintf(cf, "%d\n", set.ops.width);
	fprintf(cf, "%d\n", set.ops.numprecision);
	
	fclose(cf);
}
	
/***
 * set_Init is a function that load from the config file 
 */
void set_Init() {
	
	FILE *cf = fopen(CONFIGURATION_FILE, "r");
	// If there is a file
	if(cf != NULL) {
		// scan the vmode
		fscanf(cf, "%d", &set.vmode);
		// scan OPS settings
		fscanf(cf, "%d", &set.ops.height);
		fscanf(cf, "%d", &set.ops.width);
		fscanf(cf, "%d", &set.ops.numprecision);
		fclose(cf);
	}
	// if not, load defaults
	else 
		set_SetDefault(set);
}
	
/***
 * This function reset the settings to the default values
 */
void set_SetDefault(){
	
	set.ops.height = DEFAULT_OPS_HEIGHT;
	set.ops.width = DEFAULT_OPS_WIDTH;
	set.ops.numprecision = DEFAULT_OPS_NUMPRECISION;
	set.vmode = DEFAULT_V_MODE;

	return;
}

/***
 * This function initializes the directories if them doesn't exist
 */
BYTE set_InitDir() {
	// The state of the directories
	struct stat st = {0};
	// Check for the object directory and Create it if not present
	if (stat(OBJECT_PATH, &st) == -1)
		mkdir(OBJECT_PATH, 0700);
		
	// Check for the system directory and Create it if not present
	if (stat(SYSTEM_PATH, &st) == -1) 
		mkdir(SYSTEM_PATH, 0700);
		
	// Check that the directories has been created succefully
	if (stat(SYSTEM_PATH, &st) == -1)
		return FILE_ERR_SIG;
			
	if (stat(OBJECT_PATH, &st) == -1)
		return FILE_ERR_SIG;
		
	return GOODSIGNAL;
}
