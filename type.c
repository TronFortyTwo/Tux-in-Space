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
 * In this file there are functions that manage types and type.typ file
 * 
 */
	/***
	 * The function InitObject set the type structure reading it from a file and return his address
	 */
	tStype *Inittype (FILE *stream, tinf *inf) {
		
		// The type's mean structure (static because must be passed to others functions)
		static tStype Stype;
		//counter
		int i;
		//a temp buffer
		char buffer[DESCRIPTIONSIZE];
	
		// read how many types there are in the file
		Stype.number = 0;
		do{
			ScanFString (buffer, stream);				//name
			if(strcmp(buffer, "END OF FILE") == 0)
				break;
			ScanFString (buffer, stream);				//description
			ScanFString (buffer, stream);				//parent
			fscanf(stream, "\n");
			Stype.number++;
		}
		while(1);
		
		rewind(stream);
		
		//alloc enought spaces for all the ttype structure
		Stype.type = (ttype *) malloc (Stype.number * sizeof(ttype));
		for(; Stype.type == NULL;) {
			OPSML(inf, "Inittype");
			Stype.type = (ttype *) malloc (Stype.number * sizeof(ttype));
		}
		
		for (i=0; i!=Stype.number; i++) {
			//scan name, description and parent
			ScanFString (Stype.type[i].name, stream);
			ScanFString (Stype.type[i].description, stream);
			ScanFString (Stype.type[i].parent, stream);
			fscanf(stream, "\n");
		}

		return &Stype;
	}
	
	/***
	 * Given a name, this function return the pointer to that type. If there isn't any type whit that name return NULL
	 */
	ttype *typeSearchName(tStype *Stype, char *name) {
		//counter
		int i;
		//the loop that search the type whit the true name
		for(i=0; i!=Stype->number; i++) {
			//if the two name are equal
			if (0 == strcmp(Stype->type[i].name, name))
				 return &Stype->type[i];
		};
		
		printf("typeSearchName: No type whit the name %s has been found!\n", name);
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
		//temp string
		char number[4];
		//counters
		int i;
		int maxnum;
		//the number m at the position n represent that if the user pick the number n he mean the Stype->type[m]
		int *npoint = (int *) malloc (sizeof(int) * Stype->number);
		//inputs
		int input;
		int input2;
		
		//initialize the buffers
		strcpy (sbuf, title);
		strcat (sbuf, "\n");
		
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
			maxnum=0;
			do{
				//if the type has commonparent as parent
				if(strcmp(Stype->type[i].parent, commonparent) == 0) {
					snprintf(number, 3, "%d", maxnum+1);
					strcat(dbuf, number);
					strcat(dbuf, ") ");
					strcat(dbuf, Stype->type[i].name);
					strcat(dbuf, "\n");
					npoint[maxnum] = i;
					maxnum++;
				}
				//go to the next type
				i++;
			}
			while(i!=Stype->number);
		
			//add the Generic type button (if in a branch)
			maxnum++;
			snprintf(number, 3, "%d", maxnum);
			strcat(dbuf, number);
			strcat(dbuf, ") Generic ");
			if(strcmp(commonparent, "NULL") != 0)
				strcat(dbuf, commonparent);
			else
				strcat(dbuf, " object");
			//add the description button
			maxnum++;
			snprintf(number, 4, "%d", maxnum);
			strcat(dbuf, "\n\n");
			strcat(dbuf, number);
			strcat(dbuf, ") description of an object\n");
			//add the back button
			maxnum++;
			snprintf(number, 3, "%d", maxnum);
			strcat(dbuf, number);
			strcat(dbuf, ") back to the top of the tree");
			
			
			//print
			OPS(inf, dbuf, NULL, NULL);
			
			// scan input
			SafeIScan(inf, &input);
			
			// make the numbers start from zero and to higher number-1
			input--;
			maxnum--;
			
			// control that the value given is valid, if not, restart.
			if (input < 0)
				continue;
			if (input > maxnum)
				continue;
			
			//if the value point to a type set this type as pointer and continue if the type is parent of some type, else exit the loop
			if (input < maxnum-2) {
				strcpy(commonparent, Stype->type[npoint[input]].name);
				input2 = 0;
				for(i=0; i!=Stype->number; i++) {
					if(strcmp(commonparent, Stype->type[i].parent) == 0)
						input2++;
				}
				if(input2 == 0) {
					input = npoint[input];
					free(npoint);
					return &Stype->type[input];
				}
				continue;
			}
			//if is the generic type button
			if (input == maxnum-2) {
				free(npoint);
				if(strcmp(commonparent, "NULL") != 0)
					return typeSearchName(Stype, commonparent);
				else
					return typeSearchName(Stype, "Generic object");
			}
			//if is the description button
			if (input == maxnum-1){
				OPS(inf, "Of which type of object do you want an explaination? [type its number]", 0, 0);
				SafeIScan(inf, &input2);
				input2--;
				if (input2 < 0)
					continue;
				if (input2 > maxnum)
					continue;
				//if is the generic object type (that is a strange type) use this particular procedure
				if(strcmp(commonparent, "NULL") == 0) {
					if (maxnum-2 == input2) {
						OPS(inf, "There is no available description for the Common object type. Is for definition the object whitout caratteristic, so isn't suggested to use it.\n\npress a number to continue", 0, 0);
						SafeIScan(inf, &input2);
						continue;
					}
				}
				strcpy(dbuf, Stype->type[input2].name);
				strcat(dbuf, ":");
				strcat(dbuf, "\n\nDescription:   ");
				strcat(dbuf, Stype->type[input2].description);
				if(strcmp(Stype->type[input2].parent, "NULL") != 0) {  
					strcat(dbuf, "\n\nThis type of object is under the category:   ");
					strcat(dbuf, Stype->type[input2].parent);
				}
				else
					strcat(dbuf, "\n\nThis type of object isn't under any category");
				strcat(dbuf, "\n\nPress a number to continue");
				OPS(inf, dbuf, 0, 0);
				SafeIScan(inf, &input2);
				continue;
			}
			//if is the back button return to the start
			if (input == maxnum){
				strcpy (commonparent, "NULL");
				continue;
			}
			
		}
		while(1);
		 
		return NULL;
	}
	 
	 
	 
