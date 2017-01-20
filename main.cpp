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

// Include the header files
#include "generic.h"
#include "typeSTR.h"
#include "debug.h"
#include "shell.h"
#include "OnlyPrintfSystem.h"
#include "setting.h"

using namespace std;

//
//	MAIN FUNCTION
//
int main () {
		
	// INITIALIZATION OF THE PROGRAM
	
	// settings
	setting set;
	
	// initialize the program directories
	if(set.InitDir() != GOOD_SIG) {
		printf("\n\nCSpace:\n\nError: can't Create program directories!\nPress something to exit");
		sgetchar();
		return EXIT_FAILURE;
	}
	
	// print loading and license banner
	OPS(set, "LOADING CSPACE........\n\nCSpace - space simulator\n\nCopyright (C) 2016  emanuele.sorce@hotmail.com\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or compatibles", nullptr);
		
	// Initialize the debug
	#if DEBUG
	debug_Init();
	#endif
	
	// The big type STRucture
	typeSTR stype;
	
	// RUNNING
	while
		(Shell (set, stype) != QUIT_SIG);
		
		
	// EXITING THE PROGRAM
		
	// goodbye message
	OPS (set, "CSPACE\n\n\n%f-&t5SEE YOU LATER!", nullptr);
	
		
	return EXIT_SUCCESS;
}
