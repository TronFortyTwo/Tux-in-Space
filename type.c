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
		
		// The type's mean structure (static because is passed to other functions)
		static tStype Stype;
		//the default type
		ttype defaultype;
		//a temp buffer
		char buffer[DESCRIPTIONSIZE + 16];
		//counters
		int i;
	
		DebugPrint(inf, "Inittype");
	
		// count how many types there are in the file (-1 because there is the default type)
		Stype.number = -1;
		do{
			fscanf(stream, "\n");
			ScanFString (buffer, stream);				// read a line
			if (strcmp(buffer, "END OF FILE") == 0)		// if the file is finished exit
				break;
			else if (strncmp (buffer, "NAME:", 5) == 0)	// if is a new object memorize that there is a new object
				Stype.number++;
		}
		while(1);
		
		rewind(stream);
		
		//alloc enought spaces for all the ttype structure
		Stype.type = (ttype *) malloc (sizeof(ttype[Stype.number]));
		for(; Stype.type == NULL;) {
			OPSML(inf, "Inittype");
			Stype.type = (ttype *) malloc (sizeof(ttype[Stype.number]));
		}
		
		//scan the DEFAULT TYPE
		//name
		ScanFString(buffer, stream);
		strcpy(defaultype.name, &buffer[6]);
		//description
		ScanFString(buffer, stream);
		strcpy(defaultype.description, &buffer[13]);
		//the mass range
		ScanFString(buffer, stream);
		defaultype.mass_max = strtoll(&buffer[10], NULL, 0);
		ScanFString(buffer, stream);
		defaultype.mass_min = strtoll(&buffer[10], NULL, 0);
		//the color range
		ScanFString(buffer, stream);							// blue
		defaultype.color_max.blue = strtod(&buffer[10], NULL);
		ScanFString(buffer, stream);
		defaultype.color_min.blue = strtod(&buffer[10], NULL);
		ScanFString(buffer, stream);							// red
		defaultype.color_max.red = strtod(&buffer[9], NULL);		
		ScanFString(buffer, stream);								
		defaultype.color_min.red = strtod(&buffer[9], NULL);		
		ScanFString(buffer, stream);							//green
		defaultype.color_max.green = strtod(&buffer[11], NULL);		
		ScanFString(buffer, stream);								
		defaultype.color_min.green = strtod(&buffer[11], NULL);		
		//parent
		ScanFString(buffer, stream);
		strcpy(defaultype.parent, &buffer[8]);
		fscanf(stream, "\n");
		
		//scan the other types
		ScanFString(buffer, stream);
		for(i=0; i != Stype.number; i++) {
			//assign at the type the default values
			Stype.type[i] = defaultype;
			//scan customized values
			strcpy(Stype.type[i].name, &buffer[6]);	//the name
			do {
				ScanFString(buffer, stream);
				if(strncmp(buffer, "DESCRIPTION: ", 13) == 0)				//the description
					strcpy(Stype.type[i].description, &buffer[13]);
					
				else if(strncmp(buffer, "MASS_MAX: ", 10) == 0) {			//the maximum mass
					Stype.type[i].mass_max = strtod(&buffer[10], NULL);
				}
				else if(strncmp(buffer, "MASS_MIN: ", 10) == 0) {			//the minimum mass
					Stype.type[i].mass_min = strtod(&buffer[10], NULL);
				}
				else if(strncmp(buffer, "BLUE_MIN: ", 10) == 0) {			//the minimum blue
					Stype.type[i].color_min.blue = strtod(&buffer[10], NULL);
				}
				else if(strncmp(buffer, "BLUE_MAX: ", 10) == 0) {			//the maximum blue
					Stype.type[i].color_max.blue = strtod(&buffer[10], NULL);
				}
				else if(strncmp(buffer, "RED_MIN: ", 9) == 0) {				//the minimum red
					Stype.type[i].color_min.red = strtod(&buffer[9], NULL);
				}
				else if(strncmp(buffer, "RED_MAX: ", 9) == 0) {				//the minimum red
					Stype.type[i].color_max.red = strtod(&buffer[9], NULL);
				}
				else if(strncmp(buffer, "GREEN_MAX: ", 11) == 0) {			//the maximum green
					Stype.type[i].color_max.green = strtod(&buffer[11], NULL);
				}
				else if(strncmp(buffer, "GREEN_MIN: ", 11) == 0) {			//the minimum green
					Stype.type[i].color_min.green = strtod(&buffer[11], NULL);
				}
				else if(strncmp(buffer, "PARENT: ", 8) == 0) {				//the parent
					strcpy(Stype.type[i].parent, &buffer[8]);
					fscanf(stream, "\n");
				}
				else{
					break;
				}
			}
			while(1);
		}
		
		PrintStype(inf, &Stype);
		return &Stype;
	}
	
	/***
	 * Given a name, this function return the pointer to that type. If there isn't any type whit that name return NULL
	 */
	ttype *typeSearchName(tinf *inf, tStype *Stype, char *name) {
		DebugPrint(inf, "typesearchname");
		
		//counter
		int i;
		//the loop that search the type whit the true name
		for(i=0; i!=Stype->number; i++) {
			//if the two name are equal
			if (0 == strcmp(Stype->type[i].name, name))
				 return &Stype->type[i];
		};
		
		DebugPrint(inf, "typeSearchName: No type whit the name (read below) has been found! Probably this is a bug!\n");
		DebugPrint(inf, name);
		
		return NULL;
	}
	
	
	
	/***
	 * This function return the descripiton of the type name
	 */ 
	char *typeDescriptionFromName (tinf *inf, tStype *type, char *name) {
		DebugPrint(inf, "typedescriptionfromname");
		
		// pointer to the requested type
		ttype *type_point;
		//Search the type whit that name
		type_point = typeSearchName (inf, type, name);
		if(type_point!=NULL)
			return type_point->description;
		else
			return "This object type doesn't exist! I'm a bug";
	}
	
	/***
	 * This function return the parent of the type name
	 */ 
	char *typeParentFromName (tinf *inf, tStype *type, char *name) {
		DebugPrint(inf, "typeparentfromname");
	
		// pointer to the requested type
		ttype *type_point;
		//Search the type whit that name
		type_point = typeSearchName (inf, type, name);
		if(type_point!=NULL)
			return type_point->parent;
		else
			return "This object type doesn't exist! I'm a bug";
	}
	 
	/***
	 * In the kind browser you can browse types read from type.typ file and stored in Stype, see descriptions and choose one type to return to the calling function
	 * 
	 * file is the source struct
	 * title is an intestation to write as title
	 */ 
	ttype *TypeBrowser(tinf *inf, tStype *Stype, char *title) {
		 
		DebugPrint(inf, "typebrowser");
		
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
		//array to give to OPS
		void *var[8];
		int varpos;
		
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
		
			//add the Generic type button
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
			OPS(inf, dbuf, NULL);
			
			// scan input
			SafeIScan(inf, &input);
			
			// make the numbers start from zero
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
					return typeSearchName(inf, Stype, commonparent);
				else
					return typeSearchName(inf, Stype, "Generic object");
			}
			//if is the description button
			if (input == maxnum-1){
				OPS(inf, "Of which type of object do you want an explaination? [type its number]", NULL);
				SafeIScan(inf, &input2);
				input2--;
				if (input2 < 0)
					continue;
				if (input2 >= maxnum)
					continue;
				//if is the generic object type (that is a strange type) use this particular procedure
				if(strcmp(commonparent, "NULL") == 0) {
					if (maxnum-2 == input2) {
						OPS(inf, "There is no available description for the Common object type. Is for definition the object whitout caratteristic, so isn't suggested to use it.\n\npress a number to continue", NULL);
						SafeIScan(inf, &input2);
						continue;
					}
				}
				//if is the generic "commonparent" object
				strcpy(dbuf, Stype->type[npoint[input2]].name);
				strcat(dbuf, ":");
				strcat(dbuf, "\n\nDescription: &t9");
				strcat(dbuf, Stype->type[npoint[input2]].description);
				strcat(dbuf, "&t0");
				if(strcmp(Stype->type[npoint[input2]].parent, "NULL") != 0) {  
					strcat(dbuf, "\nCategory:   ");
					strcat(dbuf, Stype->type[npoint[input2]].parent);
				}
				else
					strcat(dbuf, "\nThis type of object isn't under any category");
				//the mass range
				strcat(dbuf, "\nMinimum mass: %l");
				strcat(dbuf, "\nMaximum mass: ");
				varpos=0;
				var[varpos] = &Stype->type[npoint[input2]].mass_min;
				varpos++;
				if(Stype->type[npoint[input2]].mass_max == -1)
					strcat(dbuf, "infinity");
				else{
					strcat(dbuf, "%l");
					var[varpos] = & Stype->type[npoint[input2]].mass_max;
					varpos++;
				}
				//the color range
				strcat(dbuf, "\nColor range:\n&t9red: %i - %i\ngreen: %i - %i\nblue: %i - %i&t0");
				var[varpos] = & Stype->type[npoint[input2]].color_min.red;
				varpos++;
				var[varpos] = & Stype->type[npoint[input2]].color_max.red;
				varpos++;
				var[varpos] = & Stype->type[npoint[input2]].color_min.green;
				varpos++;
				var[varpos] = & Stype->type[npoint[input2]].color_max.green;
				varpos++;
				var[varpos] = & Stype->type[npoint[input2]].color_min.blue;
				varpos++;
				var[varpos] = & Stype->type[npoint[input2]].color_max.blue;
				//finalizing the description page
				strcat(dbuf, "\n\nPress a number to continue");
				OPS(inf, dbuf, var);
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
	 
	 
	 
