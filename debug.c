/*
#############################################################################
#    CSpace - space simulator												#
#    Copyright (C) 2016  emanuele.sorce@hotmail.com							#
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
 
///Prototypes
	void PrintStype(tinf *, tStype *);
	void DebugPrint(tinf *, char *);
	void InitDebug(tinf *);
	void DebugObject(tinf *, tobj *);
	void DebugInt(tinf *, int);

/***
 * This function print an int in the debug file
 */
	void DebugInt(tinf *inf, int n) {
		
		char buffer[32];
		snprintf(buffer, 32, "%d", n);
		DebugPrint(inf, buffer);
		
		return;
	}


/***
 * This function print in the debug file the attributes of an object
 */
	void DebugObject(tinf *inf, tobj *obj){
		// a string
		char buffer[DESCRIPTIONSIZE + 15];
		
		// the name
		sprintf(buffer, "NAME: %s", obj->name);
		DebugPrint(inf, buffer);
		// the mass
		sprintf(buffer, "MASS: %Lf", obj->mass);
		DebugPrint(inf, buffer);
		// the radius
		sprintf(buffer, "RADIUS: %Lf", obj->radius);
		DebugPrint(inf, buffer);
		// the color
		sprintf(buffer, "COLOR: %i %i %i", obj->color.blue, obj->color.green, obj->color.red);
		DebugPrint(inf, buffer);
		// type
		sprintf(buffer, "TYPE: %s", obj->type->name);
		DebugPrint(inf, buffer);
		// coordinates
		sprintf(buffer, "COORDINATES: %Lf %Lf %Lf", obj->x, obj->y, obj->z);
		DebugPrint(inf, buffer);
		// velocity
		sprintf(buffer, "VELOCITY: %Lf %Lf %Lf", obj->velx, obj->vely, obj->velz);
		DebugPrint(inf, buffer);
		
		return;
	}

/***
 * This function print the Stype structure
 */
	void PrintStype(tinf *inf, tStype *Stype) {
	
		int i; //counters
		char buffer[1024]; 
		
		DebugPrint(inf, "\n\nSTYPE PRINTING-------------------------\n");
		
		for (i=0; i!=Stype->number; i++) {
			sprintf(buffer, "NAME:\t\t%p\t\t%s",Stype->type[i].name, Stype->type[i].name);
			DebugPrint(inf, buffer);
			sprintf(buffer, "DESCRPTION:\t\t%p\t\t%s",Stype->type[i].description, Stype->type[i].description);
			DebugPrint(inf, buffer);
			sprintf(buffer, "PARENT:\t\t%p\t\t%s", Stype->type[i].parent, Stype->type[i].parent);
			DebugPrint(inf, buffer);
			sprintf(buffer, "MASS MIN:\t\t%p\t\t%lf", &Stype->type[i].mass_min, Stype->type[i].mass_min);
			DebugPrint(inf, buffer);
			sprintf(buffer, "MASS MAX:\t\t%p\t\t%lf", &Stype->type[i].mass_max, Stype->type[i].mass_max);
			DebugPrint(inf, buffer);
			sprintf(buffer, "BLUE_RANGE:\t\t%i\t\t%i", Stype->type[i].color_min.blue, Stype->type[i].color_max.blue);
			DebugPrint(inf, buffer);
			sprintf(buffer, "RED_RANGE:\t\t%i\t\t%i", Stype->type[i].color_min.red, Stype->type[i].color_max.red);
			DebugPrint(inf, buffer);
			sprintf(buffer, "GREEN_RANGE:\t\t%i\t\t%i",  Stype->type[i].color_min.green, Stype->type[i].color_max.green);
			DebugPrint(inf, buffer);
			sprintf(buffer, "HUNTED:\t\t%p\t\t%c", &Stype->type[i].hunted, Stype->type[i].hunted);
			DebugPrint(inf, buffer);
			sprintf(buffer, "HUNTER:\t\t%p\t\t%c", &Stype->type[i].hunter, Stype->type[i].hunter);
			DebugPrint(inf, buffer);
			sprintf(buffer, "PRODUCT:\t\t%p\t\t%s", Stype->type[i].product, Stype->type[i].product);
			DebugPrint(inf, buffer);
			DebugPrint(inf, "\n");
		}
	
		return;
	}

/***
 *	Initialize the debug function
 */
	void InitDebug(tinf* inf) {
		if(inf->debug == OFF)
			return;
		fclose(fopen(DEBUG_FILE, "w"));
		return;
	}
 
 

/***
 * This function write in the debug support (a file, stderr or something else) what is called to write
 */
	void DebugPrint(tinf *inf, char *txt) {
		
		if(inf->debug == OFF)
			return;
		
		// for now the debug support is a file
		FILE *file;
		file = fopen(DEBUG_FILE, "a");
		
		// write what is requested (whit a '\n' after)
		fprintf(file, "%s", txt);
		fprintf(file, "\n"); 
		
		fclose(file);
		
		return;
	}
