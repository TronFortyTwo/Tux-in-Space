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

/***
 * This function print an int in the debug file
 */
	void DebugInt(int n) {
		
		if(inf.debug == OFF)
			return;
		
		char buffer[32];
		snprintf(buffer, 32, "%d", n);
		DebugPrint(buffer);
		
		return;
	}


/***
 * This function print in the debug file the attributes of an object
 */
	void DebugObject(tobj *obj) {
		
		if(inf.debug == OFF)
			return;
		
		// a string
		char buffer[DESCRIPTIONSIZE + 15];
		
		// the name
		sprintf(buffer, "NAME:\t\t\t%s", obj->name);
		DebugPrint(buffer);
		// the mass
		sprintf(buffer, "MASS:\t\t\t%Lf", obj->mass);
		DebugPrint(buffer);
		// the radius
		sprintf(buffer, "RADIUS:\t\t\t%Lf", obj->radius);
		DebugPrint(buffer);
		// the color
		sprintf(buffer, "COLOR:\t\t\t%i %i %i", obj->color.blue, obj->color.green, obj->color.red);
		DebugPrint(buffer);
		// type
		sprintf(buffer, "TYPE:\t\t\t%s", obj->type->name);
		DebugPrint(buffer);
		// coordinates
		sprintf(buffer, "COORDINATES:\t%Lf %Lf %Lf", obj->x, obj->y, obj->z);
		DebugPrint(buffer);
		// velocity
		sprintf(buffer, "VELOCITY:\t\t%Lf %Lf %Lf", obj->velx, obj->vely, obj->velz);
		DebugPrint(buffer);
		
		return;
	}

/***
 * This function print the Stype structure
 */
	void PrintStype(tStype *Stype) {
	
		if(inf.debug == OFF)
			return;
	
		int i; //counters
		char buffer[DESCRIPTIONSIZE + 32];
		
		DebugPrint("\n\nSTYPE PRINTING-------------------------\n");
		
		for (i=0; i!=Stype->number; i++) {
			sprintf(buffer, "NAME:\t\t\t%p\t\t%s",Stype->type[i].name, Stype->type[i].name);
			DebugPrint(buffer);
			sprintf(buffer, "DESCRPTION:\t\t%p\t\t%s",Stype->type[i].description, Stype->type[i].description);
			DebugPrint(buffer);
			sprintf(buffer, "PARENT:\t\t\t%p\t\t%s", Stype->type[i].parent, Stype->type[i].parent);
			DebugPrint(buffer);
			sprintf(buffer, "MASS MIN:\t\t%p\t\t%lf", &Stype->type[i].mass_min, Stype->type[i].mass_min);
			DebugPrint(buffer);
			sprintf(buffer, "MASS MAX:\t\t%p\t\t%lf", &Stype->type[i].mass_max, Stype->type[i].mass_max);
			DebugPrint(buffer);
			sprintf(buffer, "BLUE_RANGE:\t\t%i\t\t\t\t%i", Stype->type[i].color_min.blue, Stype->type[i].color_max.blue);
			DebugPrint(buffer);
			sprintf(buffer, "RED_RANGE:\t\t%i\t\t\t\t%i", Stype->type[i].color_min.red, Stype->type[i].color_max.red);
			DebugPrint(buffer);
			sprintf(buffer, "GREEN_RANGE:\t%i\t\t\t\t%i",  Stype->type[i].color_min.green, Stype->type[i].color_max.green);
			DebugPrint(buffer);
			sprintf(buffer, "HUNTED:\t\t\t%p\t\t", &Stype->type[i].hunted);
			if (Stype->type[i].hunted == YES)
				strcat(buffer, "YES");
			else
				strcat(buffer, "NO");
			DebugPrint(buffer);
			sprintf(buffer, "HUNTER:\t\t\t%p\t\t", &Stype->type[i].hunter);
			if (Stype->type[i].hunter == YES)
				strcat(buffer, "YES");
			else
				strcat(buffer, "NO");
			DebugPrint(buffer);
			sprintf(buffer, "PRODUCT:\t\t%p\t\t%s", Stype->type[i].product, Stype->type[i].product);
			DebugPrint(buffer);
			DebugPrint("\n");
		}
		return;
	}

/***
 *	Initialize the debug function
 */
	void InitDebug() {
		if(inf.debug == OFF)
			return;
		fclose(fopen(DEBUG_FILE, "w"));
		return;
	}
 
 

/***
 * This function write in the debug support (a file, stderr or something else) what is called to write
 */
	void DebugPrint(char *txt) {
		
		if(inf.debug == OFF)
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
