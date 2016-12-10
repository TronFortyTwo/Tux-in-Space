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
#include "type.h"
#include "debug.h"
#include "shell.h"
#include "menù.h"
#include "OnlyPrintfSystem.h"
#include "setting.h"

//
//	MAIN FUNCTION
//
int main (int argc, char *argv[]) {
		
	// INITIALIZATION OF THE PROGRAM
	
	// The type structure
	tStype *Stype;
		
	// file pointers
	FILE *Ftype;
		
	// initialize the program directories
	if(set_InitDir() != GOODSIGNAL) {
		printf("\n\nCSpace:\n\nError: can't Create program directories!\nPress something to exit");
		sgetchar();
		return EXIT_FAILURE;
	}
	// Initialize tset set from a file
	set_Init();
		
	// print loading and license banner
	OPS("LOADING CSPACE........\n\nCSpace - space simulator\n\nCopyright (C) 2016  emanuele.sorce@hotmail.com\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or compatibles", NULL);
		
	// Initialize the debug
	#if DEBUG
	debug_Init();
	#endif
		
	// Initialize Stype structure.
	{
		Ftype = fopen(TYPE_DATABASE_FILE, "r");
			if(Ftype != NULL) {
			Stype = type_Init(Ftype);
			fclose(Ftype);
		}
		else {
			OPS_Error("Can't open the file that conteins the type definitions\nPress a button to exit the program", NULL);
			sgetchar();
			return EXIT_FAILURE;
		}
	}

	// RUNNING
	while
		(Shell (Stype) != QUITSIGNAL);
		
		
	// EXITING THE PROGRAM
		
	// goodbye message
	OPS ("CSPACE\n\n\n%f-&t5SEE YOU LATER!", NULL);
	
		
	return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////////////

/***
 * Alloc a size of heap and return his pointer
 */
void *alloc_heap(size_t x, char *m) {
	void *p;
	p = malloc(x);
	while(p == NULL) {
		OPS_MemLack(m);
		p = malloc(x);
	}
	return p;
}
