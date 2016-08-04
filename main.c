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
		
		// default things for struct inf are setted.
		// height and width are respectively the number of height and width that the program can use for printing (The minimum recommended configuration is: height 40 and width 60)
		inf.height = 41;
		inf.width = 100;
		
		//print loading...
		OPS(&inf, "LOADING CSPACE........\n\nCSpace - space simulator\n\nCopyright (C) 2016  emanuele.sorce@hotmail.com\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or compatibles", NULL);
		
		// the vmode is setted 0 (OPS)
		inf.vmode = V_OPS;
		// set num precision
		inf.numprecision = 6;
		// set the debug to on and set the stderr destination file
		inf.debug = ON;
		
		InitDebug(&inf);
		
		// Read the types from a file
		Ftype = fopen("type.typ", "r");
		if(Ftype != NULL) {
			Stype = Inittype(Ftype, &inf);
			fclose(Ftype);
		}
		else {
			char input[2];		//input variable
			OPSE(&inf, "Can't open the file type.typ that conteins the type definitions\nPress a button to exit the program", NULL);
			scanf("%s", input);
			return 0;
		}


		// RUNNING THE PROGRAM
		while 
			(Shell (&inf, Stype) != QUITSIGNAL);
		
		
		// EXITING THE PROGRAM
		
		// free the memory
		WORD i, l, p=0;						// counters
		BYTE f;								// flag
		char *prod[Stype->number];			// the addresses of the string alredy free
			
		for(i=0; i!=Stype->number; i++) {
			// free name
			free(Stype->type[i].name);
			
			// free Stype.type.product
			prod[i] = NULL;
			f = 0;
			// search if in prod[] there is already this address
			for(l=0; l!=Stype->number; l++)
				if(prod[l] == Stype->type[i].product)
					f = 1;
			if(f == 0){
				prod[p] = Stype->type[i].product;
				free(Stype->type[i].product);
				p++;
			}
		}
		free(Stype->type);
		
		// goodbye message
		OPS (&inf, "CSPACE\n\n%f-&t5SEE YOU LATER!", NULL);
		
		return 0;
	}
