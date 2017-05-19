/*
#############################################################################
#    Tux in Space - space simulator											#
#    Copyright (C) 2016-2017  emanuele.sorce@hotmail.com					#
#																			#
#    This program is free software; you can redistribute it and/or modify	#
#    it under the terms of the GNU General Public License as published by	#
#    the Free Software Foundation, version 3 or compatibles.				#
#																			#
#    This program is distributed in the hope that it will be useful,		#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of			#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the			#
#    GNU General Public License for more details.							#
#																			#
#    You should have received a copy of the GNU General Public License		#
#    along with this program; if not, write to the Free Software			#
#    Foundation, Inc.														#
#############################################################################


########################################################################
# This is the Main function and contein program initialization	
########################################################################
*/

#include "main.h"

using namespace std;

//
//	MAIN FUNCTION
//
int main () {
		
	// INITIALIZATION OF THE PROGRAM
	
	// settings
	setting set;
	
	// Initialize the debug
	debug_Init();
	
	// initialize the program directories
	if(set.InitDir() != signal::good) {
		printf("\n\nTUX IN SPACE:\n\nError: can't Create program directories!\nPress something to exit");
		in_s();
		return EXIT_FAILURE;
	}
	
	// print loading and license banner
	OPS(set, "LOADING TUX IN SPACE........\n\n" BANNER);
	
	// The big type STRucture
	signal result;
	typeSTR stype(result);
	// error handling
	if(result != signal::good){
		if(result == signal::file_err) {
			OPS_Error(set, "Can't find the " TYPE_DATABASE_FILE " file, that contein the definitions of objects types.\n\nexiting.");
			debug_Printf("Stype initialization failed! exiting with file error signal");
			return EXIT_FAILURE;
		}
	}
	
	// RUNNING
	while
		(Run (set, stype) != false);
		
	// EXITING THE PROGRAM
		
	// goodbye message
	OPS (set, "Tux in Space\n\n\n%r-&t5SEE YOU LATER!");
	
	return EXIT_SUCCESS;
}
