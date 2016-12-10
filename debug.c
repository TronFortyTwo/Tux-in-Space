/*
#############################################################################
#    CSpace - space simulator												#
#    Copyright (C) 2016-2017 emanuele.sorce@hotmail.com		 				#
#																			#
#    This program is free software; you can redistribute it and/or modify	#
#    it under the terms of the GNU General Public License as published by	#
#    the Free Software Foundation, version 3 or compatibles.				#
#																			#
#    This program is distributed in the hope that it will be useful,		#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of			#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the			#
#    GNU General Public License for more details.							#
#																			#
#    You should have received a copy of the GNU General Public License		#
#    along with this program; if not, write to the Free Software			#
#    Foundation, Inc.														#
#############################################################################
 *
 * In this file there are some debug functions
 * 
 * If you are programming a new function and is buggy, why write debug function from scratch? here there are some optimized, nice and useful 
 * debugging function that you can call from everywhere easily 
 */

#include "generic.h"
#include "debug.h"

#if DEBUG

/***
 * Print a type
 */
void debug_Type(ttype *t) {
	
	debug_Printf("\nName:");
	debug_Printf(t->name);
	debug_Printf("Description:");
	debug_Printf(t->description);
	debug_Printf("Product:");
	debug_Printf(t->product->name);
	debug_Printf("Parent:");
	debug_Printf(t->parent->name);
}

/***
 * Print an int in the debug file
 */
void debug_Int(int n) {
		
	char buffer[32];
	snprintf(buffer, 32, "%d", n);
	debug_Printf(buffer);
}


/***
 * Print a double in the debug file
 */
void debug_Double(double n) {
	
	char buffer[32];
	snprintf(buffer, 32, "%lf", n);
	debug_Printf(buffer);
}

/***
 * Print in the debug file the attributes of an object
 */
void debug_Object(tobj *obj) {
		
	// a string
	char buffer[DESCRIPTIONSIZE + 15];
		
	// the name
	sprintf(buffer, "NAME:\t\t\t%s", obj->name);
	debug_Printf(buffer);
	// the mass
	sprintf(buffer, "MASS:\t\t\t%Lf", obj->mass);
	debug_Printf(buffer);
	// the radius
	sprintf(buffer, "RADIUS:\t\t\t%Lf", obj->radius);
	debug_Printf(buffer);
	// the color
	sprintf(buffer, "COLOR:\t\t\t%i %i %i", obj->color.blue, obj->color.green, obj->color.red);
	debug_Printf(buffer);
	// type
	sprintf(buffer, "TYPE:\t\t\t%s", obj->type->name);
	debug_Printf(buffer);
	// type product
	sprintf(buffer, "TYPE:\t\t\t%s", obj->type->product->name);
	debug_Printf(buffer);
	// coordinates
	sprintf(buffer, "COORDINATES:\t%Lf %Lf %Lf", obj->x, obj->y, obj->z);
	debug_Printf(buffer);
	// velocity
	sprintf(buffer, "VELOCITY:\t\t%Lf %Lf %Lf", obj->velx, obj->vely, obj->velz);
	debug_Printf(buffer);
}

/***
 * This function print the Stype structure
 */
void debug_Stype(tStype *Stype) {

	int i; //counters
	char buffer[DESCRIPTIONSIZE + 32];
		
	debug_Printf("\n\nSTYPE PRINTING -- types found:");
	debug_Int(Stype->number);
	debug_Printf("\n");
	
	for (i=0; i!=Stype->number; i++) {
		sprintf(buffer, "NAME:\t\t\t%p\t\t%s", Stype->type[i].name, Stype->type[i].name);
		debug_Printf(buffer);
		sprintf(buffer, "DESCRPTION:\t\t%p\t\t%s", Stype->type[i].description, Stype->type[i].description);
		debug_Printf(buffer);
		sprintf(buffer, "PARENT:\t\t\t%p\t\t%s", Stype->type[i].parent, Stype->type[i].parent->name);
		debug_Printf(buffer);
		sprintf(buffer, "MASS MIN:\t\t%p\t\t%lf", &Stype->type[i].mass_min, Stype->type[i].mass_min);
		debug_Printf(buffer);
		sprintf(buffer, "MASS MAX:\t\t%p\t\t%lf", &Stype->type[i].mass_max, Stype->type[i].mass_max);
		debug_Printf(buffer);
		sprintf(buffer, "BLUE_RANGE:\t\t%i\t\t\t\t%i", Stype->type[i].color_min.blue, Stype->type[i].color_max.blue);
		debug_Printf(buffer);
		sprintf(buffer, "RED_RANGE:\t\t%i\t\t\t\t%i", Stype->type[i].color_min.red, Stype->type[i].color_max.red);
		debug_Printf(buffer);
		sprintf(buffer, "GREEN_RANGE:\t%i\t\t\t\t%i",  Stype->type[i].color_min.green, Stype->type[i].color_max.green);
		debug_Printf(buffer);
		sprintf(buffer, "HUNTED:\t\t\t%p\t\t", &Stype->type[i].hunted);
		if (Stype->type[i].hunted == YES)
			strcat(buffer, "YES");
		else
			strcat(buffer, "NO");
		debug_Printf(buffer);
		sprintf(buffer, "HUNTER:\t\t\t%p\t\t", &Stype->type[i].hunter);
		if (Stype->type[i].hunter == YES)
			strcat(buffer, "YES");
		else
			strcat(buffer, "NO");
		debug_Printf(buffer);
		sprintf(buffer, "PRODUCT:\t\t%p\t\t%s", Stype->type[i].product, Stype->type[i].product->name);
		debug_Printf(buffer);
		debug_Printf("\n");
	}
}

/***
 *	Initialize the debug function
 */
	void debug_Init() {
		fclose(fopen(DEBUG_FILE, "w"));
	}
 
 

/***
 * This function write in the debug support (a file, stderr or something else) what is called to write
 */
void debug_Printf(char *txt) {
	
	// for now the debug support is a file
	FILE *file;
	file = fopen(DEBUG_FILE, "a");
	// write what is requested (whit a '\n' after)
	fprintf(file, "%s", txt);
	fprintf(file, "\n"); 
	// finalize all
	fclose(file);
}

#endif
