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
	 
	/***
	 * In the kind browser you can browse types in the type.typ file, see descriptions and choose one type to return to the calling function
	 * 
	 * file is the source struct
	 * title is an intestation to write as title
	 * if v is 0 we woudn't	return a type (so the UI changes respect 1)
	 * if v isn't 0			return a type
	 */ 
	ttype *TypeBrowser(tinf *inf, tStype *Stype, char *title) {
		 
		//in the gerarchic tree of type, is the common parent that the types shown have
		char commonparent[NAMELUN] = "NULL";
		// static buffer and dinamic buffer
		char sbuf[BUFFERSIZE];
		char dbuf[BUFFERSIZE];
		//temp pointer
		ttype *temp;
		//temp string
		char number[4];
		//counters
		int i;
		int num;
		//pointer for numbers
		ttype *npoint [Stype->number];
		//input
		int input;
		
		//initialize the buffers
		strcpy (sbuf, "TYPE BROWSER\n\n");
		strcat (sbuf, title);
		strcpy (sbuf, "\n\n");
		
		//the main loop
		do {
			//reset the dinamic buffer
			strcpy(dbuf, sbuf);
			//write in the dbuf the parent if one else a generic word
			if (strcmp(commonparent, "NULL") != 0)
				strcat(dbuf, commonparent);
			else
				strcat(dbuf, "Object");
			strcat(dbuf, ":\n\n");
			//search for types that have have as parent commonparent and add them to the buffer
			i=0;
			num=0;
			do{
				//if the type has commonparent as parent
				if(strcmp(Stype->type[i].parent, commonparent) == 0) {
					snprintf(number, 3, "%d", num+1);
					strcat(dbuf, ") ");
					strcat(dbuf, Stype->type[i].name);
					strcat(dbuf, "\n");
					npoint[num] = &Stype->type[i];
					num++;
				}
				//go to the next type
				i++;
			}
			while(i!=Stype->number);
			//add the description button
			num++;
			snprintf(number, 3, "%d", num);
			strcat(dbuf, "\n");
			strcat(dbuf, number);
			strcat(dbuf, ") description of an object\n");
			//add the back button
			num++;
			snprintf(number, 3, "%d", num);
			strcat(dbuf, number);
			strcat(dbuf, ") back");
			
			// scan input
			SafeIScan(inf, &input);
			
			// control that the value given is exact
			if (input < 1)
				if (input > num){
					OPSE(inf, "The value %i that you have typed is wrong! press a button to return to the menù and make another choice", &input, 0);
					continue;
				}
			//if the value point to a type set this type as pointer and continue if the type is parent of some type, else exit the loop
			if (input < num-2){
				strcpy(commonparent, Stype->type[input-1].name);
				num = 0;
				for(i=0; i!=Stype->number; i++) {
					if(strcmp(commonparent, Stype->type[i].parent) == 0)
						num++;
				}
				if(num > 0)
					return &Stype->type[input-1];
				continue;
			}
			//if is the description button
			if (input == num-1){
				OPS(inf, "TYPE BROWSER\n\nOf which type of object do you want an explaination? [type its number]", 0, 0);
				SafeIScan(inf, &input);
				//reset the buffer and display description
				strcpy(dbuf, sbuf);
				strcat(dbuf, "Type of object description:   ");
				temp = typeSearchName(Stype, npoint[input-1]->name);
				strcat(dbuf, temp->name);
				strcat(dbuf, "\n\nDescription:   ");
				strcat(dbuf, temp->description);
				if(strcmp(temp->parent, "NULL") != 0) {  
					strcat(dbuf, "\n\nThis object is under the category:   ");
					strcat(dbuf, temp->parent);
				}
				strcat(dbuf, "\n\nPress a number to continue");
				OPS(inf, dbuf, 0, 0);
				SafeIScan(inf, &input);
				continue;
			}
			//if is the back button return to the start
			if (input == num){
				strcpy (commonparent, "NULL");
				continue;
			}
		}
		while(1);
		 
		return NULL;
	}
	 
	 
	 
