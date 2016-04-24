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
 * In this file there are functions that manage type
 * 
 *
 *
 * Prototipes:
 */
	void ExtractType (int , char *);
	tStype *InitType (FILE *);
 
/***
 * The function InitObject set the type structure reading it from a file and return his address
 */
	tStype *InitType (FILE *stream) {
		
		// The type mean structure
		tStype types_struct;
		//counter
		short i;
	
		// read how many types there are in the file
		fscanf("%i\n", types_struct.number);
		
		//alloc enought spaces for all the one type structure
		types_struct.type = (ttype *) malloc (types_struct.number * sizeof(ttype));
		
		for (i=0; i!=types_struct; i++) {
			fscanf(stream, "%s\n", types_struct.type[i]->name);
			fscanf(stream, "%s\n", types_struct.type[i]->description);
			fscanf(stream, "%s\n", types_struct.type[i]->from);
		}
	
		return &types_struct;
	}


/***
 * This function gave a number write in a variable the name
 * 
 */
	void ExtractType (int type, char *dest) {
	
		if (type <= 0)
			strcpy(dest, "Error Type");
		else if (type == 0)
			strcpy(dest, "Void");
		else if (type == 1)
			strcpy(dest, "Spaceship");
		else if (type == 2)
			strcpy(dest, "Sun");
		else if (type == 3)
			strcpy(dest, "Generic Planet");
		else if (type == 4)
			strcpy(dest, "Rock Planet");
		else if (type == 5)
			strcpy(dest, "Giant Gas Planet");
		else if (type == 6)
			strcpy(dest, "Natural Satellite");
		else if (type == 7)
			strcpy(dest, "Asteroid");
		else if (type == 8)
			strcpy(dest, "Comet");
		else if (type == 9)
			strcpy(dest, "Black Hole");
		else if (type == 10)
			strcpy(dest, "Space Station");
		else if (type == 11)
			strcpy(dest, "Unknow type");
		else if (type >= 11)
			strcpy(dest, "Error Type");
	
		return;
	}
