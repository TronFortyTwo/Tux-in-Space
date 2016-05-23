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
	/***
	 * The function InitObject set the type structure reading it from a file and return his address
	 */
	tStype *Inittype (FILE *stream, tinf *inf) {
		
		// The type mean structure (static because must be passed to others functions)
		static tStype types_struct;
		//counter
		int i;
	
		// read how many types there are in the file
		fscanf(stream, "%i\n\n", &types_struct.number);
		
		//alloc enought spaces for all the ttype structure
		types_struct.type = (ttype *) malloc (types_struct.number * sizeof(ttype));
		for(; types_struct.type == NULL;) {
			OPSML(inf);
			types_struct.type = (ttype *) malloc (types_struct.number * sizeof(ttype));
		}
		
		for (i=0; i!=types_struct.number; i++) {
			//scan name, description and parent
			ScanFString (types_struct.type[i].name, stream);
			ScanFString (types_struct.type[i].description, stream);
			ScanFString (types_struct.type[i].parent, stream);
			fscanf(stream, "\n");
		}
	
		return &types_struct;
	}
	
	/***
	 * Given a name, this function return the pointer to that type. If there isn't any type whit that name return NULL
	 */
	ttype *typeSearchName(tStype *type, char *name) {
		//counter
		int i;
		//the loop that search the type whit the true name
		for(i=0; i!=type->number; i++) {
			//if the two name are equal
			if (0 == strcmp(type->type[i].name, name))
				 return &type->type[i];
		};
		
		return NULL;
	}
	
	
	
	/***
	 * This function return the descripiton of the type name
	 */ 
	char *typeDescriptionFromName (tStype *type, char *name) {

		// pointer to the requested type
		ttype *type_point;
		//Search the type whit that name
		type_point = typeSearchName (type, name);
		if(type_point!=NULL)
			return type_point->description;
		else
			return "This object type doesn't exist";
	}
	
	/***
	 * This function return the parent of the type name
	 */ 
	char *typeParentFromName (tStype *type, char *name) {
	
		// pointer to the requested type
		ttype *type_point;
		//Search the type whit that name
		type_point = typeSearchName (type, name);
		if(type_point!=NULL)
			return type_point->parent;
		else
			return "This object type doesn't exist";
	}
	 
	 
	 
	 
	 
