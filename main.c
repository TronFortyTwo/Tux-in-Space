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


#################################################################################################################################################
# This is the Main function of the program but doesn't do much, is a launchpad for compiling and esecution and contein files' initialization	#
#################################################################################################################################################
*/

	// Include the header file
	#include "CS_header.h"

	// Funzione principale

	int main (int argc, char *argv[]) {
		
		// INITIALIZATION OF THE PROGRAM
		
		// Basic structures
		tinf inf;
		tStype *Stype;
		
		// file pointers
		FILE *Ftype;
		
		// Initialize tinf inf from a file
		InitConfig(&inf);
		
		// print loading and license banner
		OPS(&inf, "LOADING CSPACE........\n\nCSpace - space simulator\n\nCopyright (C) 2016  emanuele.sorce@hotmail.com\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or compatibles", NULL);
		
		// the vmode is setted 0 (OPS)
		inf.vmode = V_OPS;
		// set num precision
		inf.numprecision = 6;
		
		InitDebug(&inf);
		
		// Read the types from a file
		Ftype = fopen(TYPE_DATABASE_FILE, "r");
		if(Ftype != NULL) {
			Stype = Inittype(Ftype, &inf);
			fclose(Ftype);
		}
		else {
			char input[2];		// input variable
			OPSE(&inf, "Can't open the file that conteins the type definitions\nPress a button to exit the program", NULL);
			scanf("%s", input);
			return 0;
		}


		// RUNNING THE PROGRAM
		while 
			(Shell (&inf, Stype) != QUITSIGNAL);
		
		
		// EXITING THE PROGRAM
		
		// free the memory
		FreeStype(Stype);
		
		// goodbye message
		OPS (&inf, "CSPACE\n\n%f-&t5SEE YOU LATER!", NULL);
		
		return 0;
	}
