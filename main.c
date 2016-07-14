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


#################################################################################################################################################################################################################
# This is the Main function of the program but doesn't do much, is a launchpad for compiling and esecution, is a collection of structures definitions for the other functions and contein file's initialization	#
#################################################################################################################################################################################################################
*/

	// Include the header file
	#include "CS_header.h"

	// Funzione principale

	int main (int argc, char *argv[]) {
		
		// INITIALIZATION
		
		// definition of the structures
		tinf inf;
		tStype *Stype;
		
		// The types file
		FILE *Ftype;
		
		//an input variable
		char input[2];
		
		// default things for struct inf are setted.
		// height and width are respectively the number of height and width that Rmotor can use for printing
		inf.height = 38;
		inf.width = 120;
		
		//print that is loading
		OPS(&inf, "LOADING CSPACE........\n\nCSpace - space simulator\n\nCopyright (C) 2016  emanuele.sorce@hotmail.com\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or compatibles", 0, 0);
		
		// the vmode is setted 0 (onlyOPS)
		inf.vmode = 0;
		
		// set num precision
		inf.numprecision = 4;
		
		// Read the types from a file
		Ftype = fopen("type.typ", "r");
		if(Ftype != NULL) {
			Stype = Inittype(Ftype, &inf);
			fclose(Ftype);
		}
		else {
			OPSE(&inf, "Can't open the file type.typ conteiner of the definitions of object's types\nPress a button to exit the program", 0, 0);
			scanf("%s", input);
			return 0;
		}

		// RUNNING THE PROGRAM
		do{
			// call the shell
			if (Shell (&inf, Stype) == QUITSIGNAL)
				break;
		}
		while(1);
		
		// EXITING
		
		// goodbye message
		OPS (&inf, "CSPACE\n\n&t5SEE YOU LATER!", NULL, NULL);
		
		//free the memory
		free(Stype->type);
		
		return 0;
	}
