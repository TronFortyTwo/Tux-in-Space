/*
#############################################################################################
#    CSpace - space simulator																#
#    Copyright (C) 2016-2017  emanuele.sorce@hotmail.com									#
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
#include "stdio.h"
#include "type.h"
#include "in.h"
#include "debug.h"

// internal functions
void type_Wipe (ttype *);			// Wipe the allocated mem of a type

/***
 * The function type_Init set the type structure reading it from a file and return his address
 */
tStype *type_Init (FILE *stream) {
	
	// The type's main structure (static because is passed to other functions)
	static tStype Stype;
	// buffer
	char buf[DESCRIPTIONSIZE+13];
	
	// count how many types there are in the file
	Stype.number = 0;
	{
		// a temp buffer
		char buffer[6];
		// count in a loop
		while(1) {
			fscanf(stream, "\n");
			in_hfs (buffer, stream);				// read a line
			if (!strncmp (buffer, "NAME:", 5))		// if is a new object memorize that there is a new object
				Stype.number++;
			else if (!strncmp(buffer, "EOF", 4))	// if the file is finished exit
				break;
		}
	}
		
	// alloc enought spaces for all the ttype structures
	Stype.type = (ttype *) alloc_heap(sizeof(ttype[Stype.number]), "type_init");
	
	// NAME. scan all the names
	rewind(stream);
	for(int i=0; i!=Stype.number; i++) {
		do
			in_hfs(buf, stream);
		while
			(strncmp("NAME: ", buf, 6));
		Stype.type[i].name = (char *) alloc_heap (sizeof(char) * strlen(&buf[6]), "type_Init");
		strcpy(Stype.type[i].name, &buf[6]);
	}
	// PARENT. Set all the parent
	rewind(stream);
	for(int i=0; i!=Stype.number; i++) {
		do
			in_hfs(buf, stream);
		while
			(strncmp("PARENT: ", buf, 8));
		Stype.type[i].parent = type_Search(&Stype, &buf[8]);
	}
	// OTHER STUFF
	// scan the stuff of all the types
	rewind(stream);
	// loop to scan all the types
	for(int i=0; i!=Stype.number; i++) {
		// start assigning some values of his parent
		Stype.type[i].color_max = Stype.type[i].parent->color_max;
		Stype.type[i].color_min = Stype.type[i].parent->color_min;
		Stype.type[i].hunted = Stype.type[i].parent->hunted;
		Stype.type[i].hunter = Stype.type[i].parent->hunter;
		Stype.type[i].mass_max = Stype.type[i].parent->mass_max;
		Stype.type[i].mass_min = Stype.type[i].parent->mass_min;
		Stype.type[i].product = Stype.type[i].parent->product;
		
		// then scan own values over his parent ones
		// name, jump it
		in_hfs(buf, stream);
		// description
		in_hfs(buf, stream);
		if(!strncmp(buf, "DESCRIPTION: ", 13)) {
			Stype.type[i].description = (char *) alloc_heap(sizeof(char) * strlen(&buf[13]), "type_Init");
			strcpy(Stype.type[i].description, &buf[13]);
			in_hfs(buf, stream);
		}
		// mass max:
		if(!strncmp(buf, "MASS MAX: ", 9)) {
			Stype.type[i].mass_max = atof(&buf[9]);
			in_hfs(buf, stream);
		}
		// mass min:
		if(!strncmp(buf, "MASS MIN: ", 9)) {
			Stype.type[i].mass_min = atof(&buf[9]);
			in_hfs(buf, stream);
		}
		// blue max:
		if(!strncmp(buf, "BLUE MAX: ", 9)) {
			Stype.type[i].color_max.blue = atoi(&buf[9]);
			in_hfs(buf, stream);
		}
		// blue min:
		if(!strncmp(buf, "BLUE MIN: ", 9)) {
			Stype.type[i].color_min.blue = atoi(&buf[9]);
			in_hfs(buf, stream);
		}
		// red max:
		if(!strncmp(buf, "RED MAX: ", 8)) {
			Stype.type[i].color_max.red = atoi(&buf[8]);
			in_hfs(buf, stream);
		}
		// red min:
		if(!strncmp(buf, "RED MIN: ", 8)) {
			Stype.type[i].color_min.red = atoi(&buf[8]);
			in_hfs(buf, stream);
		}
		// green max:
		if(!strncmp(buf, "GREEN MAX: ", 10)) {
			Stype.type[i].color_max.green = atoi(&buf[10]);
			in_hfs(buf, stream);
		}
		// green min:
		if(!strncmp(buf, "GREEN MIN: ", 10)) {
			Stype.type[i].color_min.green = atoi(&buf[10]);
			in_hfs(buf, stream);
		}
		// HUNTED:
		if(!strncmp(buf, "HUNTED: ", 8)) {
			if(buf[8] == 'N')
				Stype.type[i].hunted = NO;
			else
				Stype.type[i].hunted = YES;
			in_hfs(buf, stream);
		}
		// HUNTER:
		if(!strncmp(buf, "HUNTER: ", 8)) {
			if(buf[8] == 'N')
				Stype.type[i].hunter = NO;
			else
				Stype.type[i].hunter = YES;
			in_hfs(buf, stream);
		}
		// product:
		if(!strncmp(buf, "PRODUCT: ", 7)) {
			Stype.type[i].product = type_Search(&Stype, &buf[9]);
			in_hfs(buf, stream);
		}
	}
	
	// end
	return &Stype;
}

/****
 * Wipe all the dinamically allocated memory of a type
 */
void type_Wipe(ttype *t) {
	
	free(t->name);
	t->name = NULL;
	free(t->description);
	t->description = NULL;
}

/***
 * Given a name, this function return the pointer to that type. If there isn't any type whit that name return NULL
 */
ttype *type_Search(tStype *Stype, char *name) {
	
	// the loop that search the type whit the right name
	for(int i=0; i!=Stype->number; i++) {
		// if the two name have the same one
		if (!strcmp(Stype->type[i].name, name))
			 return &Stype->type[i];
	}
	
	#if DEBUG
	debug_Printf("type_Search (!) No type whit the name (read below) has been found! This is a bug!");
	debug_Printf(name);
	#endif
	
	return NULL;
}

/***
 * In the kind browser you can browse types read from type.typ file and stored in Stype, see descriptions and choose one type to return to the calling function
 * 
 * file is the source struct
 * title is an intestation to write as title
 */ 
ttype *type_Browser(tStype *Stype, char *title) {
		
	// in the gerarchic tree of types, is the common parent that the types listed have
	ttype *commonparent = type_Search(Stype, "Generic object");
	ttype *genobj = commonparent;
	// the output buffer
	char buf[1024];
	// the last object number
	int maxn;
	// the number of the back and description buttons
	int backn, descrn;
	// The pointers to the types listed
	ttype **types_listed = (ttype **) alloc_heap(sizeof(ttype *) * Stype->number, "type browser");
	// input
	int input;
	// stuff to give to OPS and its counter
	int *ivar = (int *) alloc_heap (sizeof(int) * (Stype->number + 4), "type browser");
	void **var = (void **) alloc_heap(sizeof(void*) * (Stype->number * 2 + 4), "type browser");	// +4 because there are other numbers to give to OPS
	int varpos;


	// the main loop
	while(1) {
		// restart elaborate the output
		varpos = 0;
		maxn = 0;
		// the title
		strcpy (buf, title);
		strcat (buf, "\n");
		// write in the dbuf the parent
		strcat(buf, commonparent->name);
		strcat(buf, ":\n");
		// search for types that have have as parent commonparent
		for (int i=0; i!=Stype->number; i++) {
			// if the type has commonparent as parent
			if(Stype->type[i].parent == commonparent) {
				// write its number
				strcat(buf, "\n%i) %s");	// Write the object in the buffer
				types_listed[maxn++] = &Stype->type[i];
				ivar[varpos] = maxn;
				var[varpos] = &ivar[varpos];
				varpos++;
				var[varpos++] = Stype->type[i].name;
			}
		}
		// some space then add the description button
		descrn = maxn+1;
		var[varpos++] = &descrn;
		strcat(buf, "\n\n%i) description of an object");
		// add the back button
		backn = maxn+2;
		var[varpos++] = &backn;
		strcat(buf, "\n%i) back to the top");
		
		// print
		OPS(buf, var);
		
		// make indexes start from 0
		maxn--;
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
			commonparent = types_listed[input];
			for(int i=0; i!=Stype->number; i++) {
				if(commonparent == Stype->type[i].parent)
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
			var[varpos] = commonparent->name;
			OPS(buf, var);
			// input
			in_i(&n);
			n--;
			// check that is a valid value
			if ((n < 0) || (n > descrn)) {
				OPS("There is no object whit that number out there! press something to continue...", NULL);
				sgetchar();
				continue;
			}
			// set the type
			type_descr = types_listed[n];
			
			strcpy(buf, "Info about:  ");
			strcat(buf, type_descr->name);
			strcat(buf, "\n\nDescription: &ti3");
			strcat(buf, type_descr->description);
			strcat(buf, "&t0");
			strcat(buf, "\nUnder the category:&t9 ");
			strcat(buf, type_descr->parent->name);
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
			commonparent = genobj;
	}
}
