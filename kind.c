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
	tSkind *InitKind (FILE *, tinf *);
	char *KindDescriptionFromName (tSkind *, char *);
	tkind *KindSearchName (tSkind *, char *);
	char *KindParentFromName (tSkind *, char *);
 
	/***
	 * The function InitObject set the kind structure reading it from a file and return his address
	 */
	tSkind *InitKind (FILE *stream, tinf *inf) {
		
		// The kind mean structure (static because must be passed to others functions)
		static tSkind types_struct;
		//counter
		int i;
	
		// read how many kinds there are in the file
		fscanf(stream, "%i\n\n", &types_struct.number);
		
		//alloc enought spaces for all the tkind structure
		types_struct.kind = (tkind *) malloc (types_struct.number * sizeof(tkind));
		for(; types_struct.kind == NULL;) {
			OPSML(inf);
			types_struct.kind = (tkind *) malloc (types_struct.number * sizeof(tkind));
		}
		
		for (i=0; i!=types_struct.number; i++) {
			//scan name, description and parent
			ScanFString (types_struct.kind[i].name, stream);
			ScanFString (types_struct.kind[i].description, stream);
			ScanFString (types_struct.kind[i].parent, stream);
			fscanf(stream, "\n");
		}
	
		return &types_struct;
	}
	
	/***
	 * Given a name, this function return the pointer to that kind. If there isn't any kind whit that name return NULL
	 */
	tkind *KindSearchName(tSkind *kind, char *name) {
		//counter
		int i;
		//the loop that search the kind whit the true name
		for(i=0; i!=kind->number; i++) {
			//if the two name are equal
			if (0 == strcmp(kind->kind[i].name, name))
				 return &kind->kind[i];
		};
		
		return NULL;
	}
	
	
	
	/***
	 * This function return the descripiton of the kind name
	 */ 
	char *KindDescriptionFromName (tSkind *kind, char *name) {

		// pointer to the requested kind
		tkind *kind_point;
		//Search the kind whit that name
		kind_point = KindSearchName (kind, name);
		if(kind_point!=NULL)
			return kind_point->description;
		else
			return "This object kind doesn't exist";
	}
	
	/***
	 * This function return the parent of the kind name
	 */ 
	char *KindParentFromName (tSkind *kind, char *name) {
	
		// pointer to the requested kind
		tkind *kind_point;
		//Search the kind whit that name
		kind_point = KindSearchName (kind, name);
		if(kind_point!=NULL)
			return kind_point->parent;
		else
			return "This object kind doesn't exist";
	}
