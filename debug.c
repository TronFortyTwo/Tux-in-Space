/*
#############################################################################
#    CSpace - space simulator												#
#    Copyright (C) 2016  emanuele.sorce@hotmail.com							#
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
 *
 * In this file there are some debug functions
 * 
 */
 
///Prototypes
	void PrintStype(tinf *, tStype *);
	void DebugPrint(tinf *, char *);

/***
 * This function print the Stype structure
 */
	void PrintStype(tinf *inf, tStype *Stype) {
	
		int i; //counter
		char buffer[2048];
		
		printf("\nSTYPE PRINTING-------------------------\n");
		
		for (i=0; i!=Stype->number; i++) {
			sprintf(buffer, "\nNAME: %s\nDESCRIPTION: %s\nPARENT: %s\nMASS_MIN: %lf\nMASS_MAX: %lf\nBLUE_RANGE: %i - %i\nRED_RANGE: %i - %i\nGREEN_RANGE: %i - %i\n", Stype->type[i].name, Stype->type[i].description, Stype->type[i].parent, Stype->type[i].mass_min, Stype->type[i].mass_max, Stype->type[i].color_min.blue, Stype->type[i].color_max.blue, Stype->type[i].color_min.red, Stype->type[i].color_max.red, Stype->type[i].color_min.green, Stype->type[i].color_max.green);
			DebugPrint(inf, buffer);
		}
		return;
	}

/***
 * This function write in the debug support (a file, stderr or something else) what is called to write
 */
	void DebugPrint(tinf *inf, char *txt) {
		
		if(inf->debug == 0)
			return;
		
		// for now the debug support is a file
		FILE *file;
		file = fopen("debug.dbg", "a");
		
		// write what is requested (but whit a '\n')
		fprintf(file, txt);
		fprintf(file, "\n"); 
		
		fclose(file);
		
		return;
	}
