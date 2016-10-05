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
 
#include "generic.h"
#include "type.h"
#include "in.h"
#include "debug.h"
#include "OnlyPrintfSystem.h"
  

/***
 * The function obj_Init set the type structure reading it from a file and return his address
 */
tStype *type_Init (FILE *stream) {
		
	// The type's mean structure (static because is passed to other functions)
	static tStype Stype;
	// the default type
	ttype defaultype;
	// a temp buffer
	char buffer[DESCRIPTIONSIZE + 13];
	// counters
	int i;
	
	// count how many types there are in the file (-1 because there is the default type)
	Stype.number = -1;
	while(1) {
		fscanf(stream, "\n");
		in_fs (buffer, stream);				// read a line
		if (!strcmp(buffer, "EOF"))					// if the file is finished exit
			break;
		else if (!strncmp (buffer, "NAME:", 5))		// if is a new object memorize that there is a new object
			Stype.number++;
	}
		
	// alloc enought spaces for all the ttype structure
	Stype.type = (ttype *) malloc (sizeof(ttype[Stype.number]));
	while(Stype.type == NULL) {
		OPS_MemLack("type_Init");
		Stype.type = (ttype *) malloc (sizeof(ttype[Stype.number]));
	}
		
	// scan the DEFAULT TYPE
	rewind(stream);
	// name
	in_fs(buffer, stream);
	defaultype.name = (char *) malloc (sizeof(char[strlen(&buffer[6])]));
	strcpy(defaultype.name, &buffer[6]);
	// description
	in_fs(buffer, stream);
	strcpy(defaultype.description, &buffer[13]);
	// the mass range
	in_fs(buffer, stream);
	defaultype.mass_max = strtoll(&buffer[10], NULL, 0);
	in_fs(buffer, stream);
	defaultype.mass_min = strtoll(&buffer[10], NULL, 0);
	// the color range
	in_fs(buffer, stream);							// blue
	defaultype.color_max.blue = strtod(&buffer[10], NULL);
	in_fs(buffer, stream);
	defaultype.color_min.blue = strtod(&buffer[10], NULL);
	in_fs(buffer, stream);							// red
	defaultype.color_max.red = strtod(&buffer[9], NULL);		
	in_fs(buffer, stream);								
	defaultype.color_min.red = strtod(&buffer[9], NULL);		
	in_fs(buffer, stream);							//green
	defaultype.color_max.green = strtod(&buffer[11], NULL);		
	in_fs(buffer, stream);								
	defaultype.color_min.green = strtod(&buffer[11], NULL);	
	// hunted
	in_fs(buffer, stream);
	if(buffer[8] == 'Y')
		defaultype.hunted = ON;
	else if(buffer[8] == 'N')
		defaultype.hunted = OFF;
	// hunter
	in_fs(buffer, stream);
	if(buffer[8] == 'Y')
		defaultype.hunter = ON;
	else if(buffer[8] == 'N')
		defaultype.hunter = OFF;
	// product (defaultype has only one product)
	in_fs(buffer, stream);
	defaultype.product = (char *) malloc (sizeof(char[strlen(&buffer[9])]));
	while(defaultype.product == NULL){
		OPS_MemLack("initype");
		defaultype.product = (char *) malloc (sizeof(char[strlen(&buffer[9])]));
	}
	strcpy(defaultype.product, &buffer[9]);
	// parent
	in_fs(buffer, stream);
	strcpy(defaultype.parent, &buffer[8]);
	fscanf(stream, "\n");
	
	//scan the other types
	in_fs(buffer, stream);
	for(i=0; i != Stype.number; i++) {
		// assign at the type the default values
		Stype.type[i] = defaultype;
		// scan customized values
		Stype.type[i].name = (char *) malloc (sizeof(char[strlen(&buffer[6])]));
		while(Stype.type[i].name == NULL) {
			OPS_MemLack("type_Init");
			Stype.type[i].name = (char *) malloc (sizeof(char[strlen(&buffer[6])]));
		}
		strcpy(Stype.type[i].name, &buffer[6]);	//the name
		while(1) {
			in_fs(buffer, stream);
			if(!strncmp(buffer, "DESCRIPTION: ", 13))					//the description
				strcpy(Stype.type[i].description, &buffer[13]);
				
			else if(!strncmp(buffer, "MASS_MAX: ", 10)) {				//the maximum mass
				Stype.type[i].mass_max = strtod(&buffer[10], NULL);
			}
			else if(!strncmp(buffer, "MASS_MIN: ", 10)) {				//the minimum mass
				Stype.type[i].mass_min = strtod(&buffer[10], NULL);
			}
			else if(!strncmp(buffer, "BLUE_MIN: ", 10)) {				//the minimum blue
				Stype.type[i].color_min.blue = strtod(&buffer[10], NULL);
			}
			else if(!strncmp(buffer, "BLUE_MAX: ", 10)) {				//the maximum blue
				Stype.type[i].color_max.blue = strtod(&buffer[10], NULL);
			}
			else if(!strncmp(buffer, "RED_MIN: ", 9)) {					//the minimum red
				Stype.type[i].color_min.red = strtod(&buffer[9], NULL);
			}
			else if(!strncmp(buffer, "RED_MAX: ", 9)) {					//the minimum red
				Stype.type[i].color_max.red = strtod(&buffer[9], NULL);
			}
			else if(!strncmp(buffer, "GREEN_MAX: ", 11)) {				//the maximum green
				Stype.type[i].color_max.green = strtod(&buffer[11], NULL);
			}
			else if(!strncmp(buffer, "GREEN_MIN: ", 11)) {				//the minimum green
				Stype.type[i].color_min.green = strtod(&buffer[11], NULL);
			}
			else if(!strncmp(buffer, "HUNTED: ", 8)) {					//if is hunted
				if(buffer[8] == 'Y')
					Stype.type[i].hunted = ON;
				else if(buffer[8] == 'N')
					Stype.type[i].hunted = OFF;
			}
			else if(!strncmp(buffer, "HUNTER: ", 8)) {					//if hunts
				if(buffer[8] == 'Y')
					Stype.type[i].hunter = ON;
				else if(buffer[8] == 'N')
					Stype.type[i].hunter = OFF;
			}
			else if(!strncmp(buffer, "PRODUCT: ", 9)) {					//the product
				Stype.type[i].product = (char *) malloc (sizeof(char[strlen(&buffer[9])]));
				while(Stype.type[i].product == NULL){
					OPS_MemLack("initype");
					Stype.type[i].product = (char *) malloc (sizeof(char[strlen(&buffer[9])]));
				}
				strcpy(Stype.type[i].product, &buffer[9]);
			}
			else if(!strncmp(buffer, "PARENT: ", 8)) {					//the parent
				strcpy(Stype.type[i].parent, &buffer[8]);
				fscanf(stream, "\n");
			}
			else
				break;
		}
	}	
	//finalization
	#if DEBUG
	debug_Stype(&Stype);
	#endif
	free(defaultype.name);
	free(defaultype.product);
	return &Stype;
}
	
/***
 * Given a name, this function return the pointer to that type. If there isn't any type whit that name return NULL
 */
ttype *type_Search(tStype *Stype, char *name) {
	
	//counter
	int i;
	//the loop that search the type whit the true name
	for(i=0; i!=Stype->number; i++) {
		//if the two name are the same
		if (0 == strcmp(Stype->type[i].name, name))
			 return &Stype->type[i];
	}
	
	#if DEBUG
	debug_Printf("type_Search (!) No type whit the name (read below) has been found! This is a bug!");
	debug_Printf(name);
	#endif
	
	return NULL;
}
	
	
	
/***
 * This function return the descripiton of the type name
 */ 
char *type_GetDescription (tStype *type, char *name) {
	
	// pointer to the requested type
	ttype *type_point;
	//Search the type whit that name
	type_point = type_Search (type, name);
	if(type_point!=NULL)
		return type_point->description;
	else {
		#if DEBUG
		debug_Printf("type_GetDescription (!) NO type whit that name has been found! This is a bug!");
		#endif
		return "This object type doesn't exist! I'm a bug";
	}
}
	
/***
 * This function return the parent of the type name
 */ 
char *type_GetParent (tStype *type, char *name) {
	
	// pointer to the requested type
	ttype *type_point;
	//Search the type whit that name
	type_point = type_Search (type, name);
	if(type_point!=NULL)
		return type_point->parent;
	else {
		#if DEBUG
		debug_Printf("type_GetDescription (!) NO type whit that name has been found! This is a bug!");
		#endif
		return "This object type doesn't exist! I'm a bug";
	}
}
	 
/***
 * In the kind browser you can browse types read from type.typ file and stored in Stype, see descriptions and choose one type to return to the calling function
 * 
 * file is the source struct
 * title is an intestation to write as title
 */ 
ttype *type_Browser(tStype *Stype, char *title) {
		
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
	while (npoint == NULL){
		OPS_MemLack("type_Browser");
		npoint = (int *) malloc (sizeof(int) * Stype->number);
	}
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
		snprintf(number, 3, "%d", maxnum);
		strcat(dbuf, "\n\n");
		strcat(dbuf, number);
		strcat(dbuf, ") description of an object\n");
		//add the back button
		maxnum++;
		snprintf(number, 3, "%d", maxnum);
		strcat(dbuf, number);
		strcat(dbuf, ") back to the top of the tree");
		
		//print
		OPS(dbuf, NULL);
			
		// scan input
		in_i(&input);
		
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
				return type_Search(Stype, commonparent);
			else
				return type_Search(Stype, "Generic object");
		}
		//if is the description button
		if (input == maxnum-1){
			OPS("Of which type of object do you want an explaination? [type its number]", NULL);
			in_i(&input2);
			input2--;
			if (input2 < 0)
				continue;
			if (input2 >= maxnum)
				continue;
			//if is the generic object type (that is a strange type) use this particular procedure
			if(strcmp(commonparent, "NULL") == 0) {
				if (maxnum-2 == input2) {
					OPS("There is no available description for the Common object type. Is for definition the object whitout caratteristic, so isn't suggested to use it.\n\npress a number to continue", NULL);
					in_i(&input2);
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
			OPS(dbuf, var);
			in_i(&input2);
			continue;
		}
		//if is the back button return to the start
		if (input == maxnum) {
			strcpy (commonparent, "NULL");
			continue;
		}		
	}
	while(1);
 
	return NULL;
}
	 
	 
	 
