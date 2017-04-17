/*
#############################################################################
#    CSpace - space simulator												#
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
	#if DEBUG
	debug_Init();
	#endif
	
	// initialize the program directories
	if(set.InitDir() != GOOD_SIG) {
		printf("\n\nCSpace:\n\nError: can't Create program directories!\nPress something to exit");
		in_s();
		return EXIT_FAILURE;
	}
	
	// print loading and license banner
	OPS(set, "LOADING CSPACE........\n\nCSpace - space simulator\n\nCopyright (C) 2016  emanuele.sorce@hotmail.com\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or compatibles", nullptr);
	
	// The big type STRucture
	BYTE result;
	typeSTR stype(result);
	// error handling
	if(result != GOOD_SIG){
		if(result == FILE_ERR_SIG) {
			OPS_Error(set, "Can't find the " TYPE_DATABASE_FILE " file, that contein the definitions of objects types.\n\nexiting.", nullptr);
			#if DEBUG
			debug_Printf("Stype initialization failed! exiting with:");
			debug_Int(FILE_ERR_SIG);
			#endif
			return EXIT_FAILURE;
		}
	}
	
	// RUNNING
	while
		(Shell (set, stype) != ABORTED_SIG);
		
	// EXITING THE PROGRAM
		
	// goodbye message
	OPS (set, "CSPACE\n\n\n%f-&t5SEE YOU LATER!", nullptr);
	
	return EXIT_SUCCESS;
}
