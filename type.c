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
		in_hfs (buffer, stream);					// read a line
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
		
	rewind(stream);
		
	// scan the DEFAULT TYPE
	// name
	in_hfs(buffer, stream);
	defaultype.name = (char *) malloc (sizeof(char[strlen(&buffer[6])]));
	strcpy(defaultype.name, &buffer[6]);
	// description
	in_hfs(buffer, stream);
	strcpy(defaultype.description, &buffer[13]);
	// the mass range
	in_hfs(buffer, stream);
	defaultype.mass_max = strtoll(&buffer[10], NULL, 0);
	in_hfs(buffer, stream);
	defaultype.mass_min = strtoll(&buffer[10], NULL, 0);
	// the color range
	in_hfs(buffer, stream);							// blue
	defaultype.color_max.blue = strtod(&buffer[10], NULL);
	in_hfs(buffer, stream);
	defaultype.color_min.blue = strtod(&buffer[10], NULL);
	in_hfs(buffer, stream);							// red
	defaultype.color_max.red = strtod(&buffer[9], NULL);		
	in_hfs(buffer, stream);								
	defaultype.color_min.red = strtod(&buffer[9], NULL);		
	in_hfs(buffer, stream);							//green
	defaultype.color_max.green = strtod(&buffer[11], NULL);		
	in_hfs(buffer, stream);								
	defaultype.color_min.green = strtod(&buffer[11], NULL);	
	// hunted
	in_hfs(buffer, stream);
	if(buffer[8] == 'Y')
		defaultype.hunted = ON;
	else if(buffer[8] == 'N')
		defaultype.hunted = OFF;
	// hunter
	in_hfs(buffer, stream);
	if(buffer[8] == 'Y')
		defaultype.hunter = ON;
	else if(buffer[8] == 'N')
		defaultype.hunter = OFF;
	// product (defaultype has only one product)
	in_hfs(buffer, stream);
	defaultype.product = (char *) malloc (sizeof(char[strlen(&buffer[9])]));
	while(defaultype.product == NULL){
		OPS_MemLack("initype");
		defaultype.product = (char *) malloc (sizeof(char[strlen(&buffer[9])]));
	}
	strcpy(defaultype.product, &buffer[9]);
	// parent
	in_hfs(buffer, stream);
	strcpy(defaultype.parent, &buffer[8]);
	
	// scan the other types
	in_hfs(buffer, stream);
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
			in_hfs(buffer, stream);
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
	
	//the loop that search the type whit the true name
	for(int i=0; i!=Stype->number; i++) {
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
		return NULL;
	}
}
	 
/***
 * In the kind browser you can browse types read from type.typ file and stored in Stype, see descriptions and choose one type to return to the calling function
 * 
 * file is the source struct
 * title is an intestation to write as title
 */ 
ttype *type_Browser(tStype *Stype, char *title) {
		
	// in the gerarchic tree of type, is the common parent that the types shown have
	TNAME commonparent = "NULL";
	// the output buffer
	char buf[1024];
	// the last object number
	int maxn;
	// the number of the back, description and generic button
	int backn, descrn, genericn;
	
	// The pointers to the types listed
	ttype **types_listed = (ttype **) malloc (sizeof(ttype *) * Stype->number);
	while (types_listed == NULL){
		OPS_MemLack("type browser");
		types_listed = (ttype **) malloc (sizeof(ttype *) * Stype->number);
	}
	// input
	int input;
	// stuff to give to OPS and its counter
	int *ivar = (int *) malloc (sizeof(int) * (Stype->number + 4));
	while(ivar == NULL){
		OPS_MemLack("type Browser");
		ivar = (int *) malloc (sizeof(int) * (Stype->number + 4));
	}
	void **var = (void **) malloc(sizeof(void*) * (Stype->number * 2 + 4));	// +4 because there are other numbers to give to OPS
	while(var == NULL){
		OPS_MemLack("type Browser");
		var = (void **) malloc(sizeof(void*) * (Stype->number * 2 + 4));
	}
	int varpos;


	// the main loop
	while(1) {
		// restart elaborate the output
		varpos = 0;
		maxn = 0;
		// the title
		strcpy (buf, title);
		strcat (buf, "\n");
		// write in the dbuf the parent if there is one, else a generic word
		if (strcmp(commonparent, "NULL"))
			strcat(buf, commonparent);
		else
			strcat(buf, "Object");
		strcat(buf, ":\n");
		// search for types that have have as parent commonparent
		for (int i=0; i!=Stype->number; i++) {
			// if the type has commonparent as parent
			if(!strcmp(Stype->type[i].parent, commonparent)) {
				// write its number
				strcat(buf, "\n%i) %s");	// Write the object in the buffer
				types_listed[maxn++] = &Stype->type[i];
				ivar[varpos] = maxn;
				var[varpos] = &ivar[varpos++];
				var[varpos++] = Stype->type[i].name;
			}
		}
		// add the Generic type button
		genericn = maxn+1;
		strcat(buf, "\n%i");
		var[varpos++] = &genericn;
		strcat(buf, ") Generic ");
		if(strcmp(commonparent, "NULL"))
			strcat(buf, commonparent);
		else
			strcat(buf, "object");
		// some space then add the description button
		descrn = maxn+2;
		var[varpos++] = &descrn;
		strcat(buf, "\n\n%i) description of an object");
		// add the back button
		backn = maxn+3;
		var[varpos++] = &backn;
		strcat(buf, "\n%i) back to the top");
		
		// print
		OPS(buf, var);
		
		// make indexes start from 0
		maxn--;
		genericn--;
		descrn--;
		backn--;
		
		// scan the input as long as a valid number is given
		do {
			in_i(&input);
			input--;
		}
		while ((input < 0) || (input > backn));
		
		// if the value point to a type, set this type as pointer and continue if the type is parent of some type, else exit the loop
		if (input <= maxn) {
			BYTE flag = NO;		// NO if the type haven't any child  
			strcpy(commonparent, types_listed[input]->name);
			for(int i=0; i!=Stype->number; i++) {
				if(!strcmp(commonparent, Stype->type[i].parent))
					flag = YES;
			}
			if(flag == NO) {
				ttype *typetemp = types_listed[input];	// temp variable
				free(types_listed);
				free(var);
				free(ivar);
				return typetemp;
			}
		}
		// if is the generic type button
		else if (input == genericn) {
			free(types_listed);
			free(var);
			free(ivar);
			if(!strcmp(commonparent, "NULL"))
				return type_Search(Stype, "Generic object");
			else
				return type_Search(Stype, commonparent);
		}
		// if is the description button
		else if (input == descrn) {
			int n;
			ttype *type_descr;	// the type described
			varpos = 0;
			// output
			strcpy(buf, "Of which type of object do you want an explaination? [type its number]\n");
			for(int i=0; i <= maxn; i++){
				strcat(buf, "\n%i) %s");
				ivar[varpos] = i+1;
				var[varpos] = &ivar[varpos];
				varpos++;
				var[varpos++] = types_listed[i]->name;
			}
			// generic
			strcat(buf, "\n%i) Generic %s");
			ivar[varpos] = descrn;				// descrn = genericn+1
			var[varpos] = &ivar[varpos];
			varpos++;
			if(!strcmp(commonparent, "NULL"))	// if we are in the root
				var[varpos] = (type_Search(Stype, "Generic object"))->name;
			else
				var[varpos] = (type_Search(Stype, commonparent))->name;
			OPS(buf, var);
			// input
			in_i(&n);
			n--;
			// elaboration
			if ((n < 0) || (n > genericn)) {
				OPS("There is no object whit that number out there! press something to continue...", NULL);
				sgetchar();
				continue;
			}
			// if is the generic object type (that is a strange type) use this particular procedure
			else if(!strcmp(commonparent, "NULL")){
				if (n == genericn)
					type_descr = type_Search(Stype, "Generic object");
				else
					type_descr = type_Search(Stype, commonparent);
			}
			else
				type_descr = types_listed[n];
			strcpy(buf, "Info about:  ");
			strcat(buf, type_descr->name);
			strcat(buf, "\n\nDescription: &ti3");
			strcat(buf, type_descr->description);
			strcat(buf, "&t0");
			strcat(buf, "\nUnder the category:&t9 ");
			if ((!strcmp(type_descr->parent, "NULL")) || (!strcmp(type_descr->parent, "System")))
				strcat(buf, "(Not under any category)");
			else
				strcat(buf, type_descr->parent);
			strcat(buf, "&t0");
			// the mass range
			strcat(buf, "\nMinimum mass: %l");
			strcat(buf, "\nMaximum mass: ");
			var[0] = &type_descr->mass_min;
			varpos = 1;
			if(type_descr->mass_max == -1)
				strcat(buf, "infinite");
			else{
				strcat(buf, "%l");
				var[varpos++] = &type_descr->mass_max;
			}
			// the color range
			strcat(buf, "\nColor range:\n&t9red: %i - %i\ngreen: %i - %i\nblue: %i - %i&t0");
			var[varpos++] = &type_descr->color_min.red;
			var[varpos++] = &type_descr->color_max.red;
			var[varpos++] = &type_descr->color_min.green;
			var[varpos++] = &type_descr->color_max.green;
			var[varpos++] = &type_descr->color_min.blue;
			var[varpos]   = &type_descr->color_max.blue;
			// finalizing the description page
			strcat(buf, "\n\nPress something to continue...");
			OPS(buf, var);
			sgetchar();
		}
		// if is the back button return to the start
		else if (input == backn)
			strcpy (commonparent, "NULL");
	}
}
