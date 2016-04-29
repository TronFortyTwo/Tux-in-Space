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
 * In this file there are functions that manage kind
 * 
 *
 *
 * Prototipes:
 */
	tSkind *InitKind (FILE *);
	char *KindDescriptionFromName (tSkind *kind, char *name);
	tkind *KindSearchName (tSkind *kind, char *name);
	char *KindParentFromName (tSkind *kind, char *name);
 
	/***
	 * The function InitObject set the kind structure reading it from a file and return his address
	 */
	tSkind *InitKind (FILE *stream) {
		
		// The kind mean structure (static because must be passed to others functions)
		static tSkind types_struct;
		//counter
		short i;
	
		// read how many kinds there are in the file
		fscanf(stream, "%i\n\n", &types_struct.number);
		
		//alloc enought spaces for all the one kind structure
		types_struct.kind = (tkind *) malloc (types_struct.number * sizeof(tkind));
		
		for (i=0; i!=types_struct.number; i++) {
			fscanf(stream, "%s\n", types_struct.kind[i].name);
			fscanf(stream, "%s\n", types_struct.kind[i].description);
			fscanf(stream, "%s\n\n", types_struct.kind[i].parent);
		}
	
		return &types_struct;
	}
	
	/***
	 * This function gave a name, return the pointer to that kind
	 */
	tkind *KindSearchName(tSkind *kind, char *name) {
		//counter
		short i;
		//the loop that search the kind whit the true name
		for(i=0; 0 == strcmp(kind->kind[i].name, name); i++);
		
		return &kind->kind[i];
	}
	
	
	
	/***
	 * This function write in the string dest the descripiton of the kind name
	 */ 
	char *KindDescriptionFromName (tSkind *kind, char *name) {

		// pointer to the requested kind
		tkind *kind_point;
		//Search the kind whit that name
		kind_point = KindSearchName (kind, name);
		return kind_point->description;
	}
	
	/***
	 * This function write in the string dest the parent of the kind name
	 */ 
	char *KindParentFromName (tSkind *kind, char *name) {
	
		// pointer to the requested kind
		tkind *kind_point;
		//Search the kind whit that name
		kind_point = KindSearchName (kind, name);
		//return the pointer to the parent name
		return kind_point->parent;
	}
