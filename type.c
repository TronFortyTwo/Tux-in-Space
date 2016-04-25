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
	tStype *InitType (FILE *);
 
/***
 * The function InitObject set the type structure reading it from a file and return his address
 */
	tStype *InitType (FILE *stream) {
		
		// The type mean structure (static because must be passed to others functions)
		static tStype types_struct;
		//counter
		short i;
	
		// read how many types there are in the file
		fscanf(stream, "%i\n\n", &types_struct.number);
		
		//alloc enought spaces for all the one type structure
		types_struct.type = (ttype *) malloc (types_struct.number * sizeof(ttype));
		
		for (i=0; i!=types_struct.number; i++) {
			fscanf(stream, "%s\n", types_struct.type[i].name);
			fscanf(stream, "%s\n", types_struct.type[i].description);
			fscanf(stream, "%s\n\n", types_struct.type[i].parent);
		}
	
		return &types_struct;
	}
