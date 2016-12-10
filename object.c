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
 *	Object oriented file where Create a "class" object, giving a coerent and fast API to the program
 * 
 * 	all these function have the obj_ prefix
 * 
 * 	NOTE:
 * 	this file functions should are ordered by alphabetical order
 */

#include "generic.h"
#include "object.h"
#include "OnlyPrintfSystem.h"
#include "in.h"
#include "math.h"
#include "debug.h"

// local constants
#define BIGGER_TOLERANCE 1.21
// internal functions
void obj_WipeName 		(char *);						// Wipe the name of an object (no mem lack)
void obj_WipeData		(void *);						// Wipe the data struct of an object
BYTE obj_Read 			(FILE *, tobj *, tStype *Stype);// Read from a file an object
BYTE obj_ReadComplete 	(FILE *, tobj *, tStype *Stype);// Read from a file an object whit coordinates



/***
 * This function compute the distance between the center of two objects
 */
long double obj_Distance(tobj *i, tobj *l) {
	return math_Pitagora3D(i->x - l->x, i->y - l->y, i->z - l->z);
}

/***
 * Put in *b the address of the bigger object
 * i and l are the two objects,
 */
void obj_GetBigger (tobj *i, tobj *l, tobj **b) {
	
	// an object is bigger if has mass much bigger
	if (i->mass > l->mass*BIGGER_TOLERANCE)
		*b = i;
	else if (l->mass > i->mass*BIGGER_TOLERANCE)
		*b = l;
	// if no one is much bigger than the other, pick one randomly, but considering the mass
	else {
		srand(time(NULL));
		if 		( (rand()/RAND_MAX) > (i->mass/(l->mass+i->mass)) )
			*b = l;
		else
			*b = i;
	}
}

/***
 * 	The function InitObject initialize a new object and ask information about it
 * 
 * 	n is the number of the object to initialize, if in a list
 * 	return ABORTED_SIG if the new object isn't initialized
 */
BYTE obj_Init (tobj *obj, tStype *Stype) {
		
	//variables
	void *var[18];
	int input;
	char comment[64];			// This is a buffer that contein comment of what is just been done
	char mass_irregularity[3];	// assume the value IRREGULARITY if the mass is out of range
	char color_irregularity[3];	// assume the value IRREGULARITY if the color is out of range
	
	// Initialize the object
	obj_LowInit(obj);
	obj_Rename(obj, "Choose a name for your new object");
	obj->type = type_Search(Stype, "Generic object");
	obj->mass = 0;
	obj->radius = 0;
	obj->color.blue = 0;
	obj->color.red = 0;
	obj->color.green = 0;
	obj->x = 0;
	obj->y = 0;
	obj->z = 0;
	obj->velx = 0;
	obj->vely = 0;
	obj->velz = 0;
	
	// the loop
	strcpy(comment, " ");
	strcpy(mass_irregularity, " ");
	strcpy(color_irregularity, " ");
	
	while(1) {
		// check for IRREGALARITY
		// irregularity: MASS
		if ((obj->mass > obj->type->mass_min) && ((obj->mass < obj->type->mass_max) || (obj->type->mass_max == -1))) {
			strcpy(mass_irregularity, "  ");
		}
		else {
			strcpy(mass_irregularity, IRREGULARITY);
			strcat(comment, "\n");
			strcat(comment, IRREGULARITY);
			strcat(comment, ": mass out of range");
		}
		// irregularity: COLOR
		if (color_CheckRange(obj->color, obj->type->color_min, obj->type->color_max) == GOODSIGNAL)
			strcpy(color_irregularity, " ");
		else {
			strcpy(color_irregularity, IRREGULARITY);
			strcat(comment, "\n");
			strcat(comment, IRREGULARITY);
			strcat(comment, ": color out of range");
		}
		// irregularity: TYPE
		if (obj->type == type_Search(Stype, "Choose a type")) {
			strcat(comment, "\n");
			strcat(comment, IRREGULARITY);
			strcat(comment, ": Choose a type!");
		}
		
		// Print the actual state and scan the desire of the user
		var[0] = obj->name;
		var[1] = obj->type->name;
		var[2] = obj->type->description;
		var[3] = &obj->color.red;
		var[4] = color_irregularity;
		var[5] = &obj->color.green;
		var[6] = &obj->color.blue;
		var[7] = &obj->mass;
		var[8] = mass_irregularity;
		var[9] = &obj->radius;
		var[10] = &obj->x;
		var[11] = &obj->y;
		var[12] = &obj->z;
		var[13] = &obj->velx;
		var[14] = &obj->vely;
		var[15] = &obj->velz;
		var[16] = comment;
		OPS("CREATE A NEW OBJECT\n\n%f-1) name:         %s\n%f-2) type:         %s\n&ti7%s&t0\n%f-3) color:        red: %i   %s&ti7\ngreen: %i\nblue: %i&t0\n%f-4) mass:         %l   %s\n%f-5) radius:       %l\n%f-6) coordinates:  x: %l&ti7\ny: %l\nz: %l&t0\n%f-7) velocity:     x: %l&ti7\ny: %l\nz: %l&t0\n%f-8) LOAD  the object from a file\n%f-9) SAVE  this object to a file\n%f-10) DONE\n11) EXIT whitout saving\n\n%s", var);
		in_i(&input);
		
		// reset previous comment
		comment[0] = 0;
	
		// Name
		if(input == 1) {
			// two temp variable
			TNAME name;
			int temp = NAMELUN-1;
			var[0] = &temp;
			OPS ("INITIALIZE A NEW OBJECT\n\nInsert the name of the new object:\n&tdThe name must be of maximum %i character and can't contein spaces", var);
			in_s(name);
			// apply the new name
			obj_Rename(obj, name);
			strcpy(comment, "\nNew name assigned succefully!");
		}
		// Type
		else if(input == 2) {
			obj->type = type_Browser(Stype, "Choose a new type for your new object");
			strcpy(comment, "\nNew type assigned succefully!");
		}
		// Color
		else if(input == 3) {
			obj->color = color_Scan(obj->type->color_min, obj->type->color_max);
			strcpy(comment, "\nNew color assigned succefully!");
		}
		// Mass
		else if(input == 4) {
			var[0] = & obj->type->mass_min;
			if (obj->type->mass_max == -1)
				OPS ("Create A NEW OBJECT\n\nInsert the mass of the new object: (t)\n&tdThe mass's legal values start from %l", var);
			else{
				var[1] = & obj->type->mass_max;
				OPS ("Create A NEW OBJECT\n\nInsert the mass of the new object: (t)\n&tdThe mass's legal values are between %l and %l", var);
			}
			scanf("%Lf", & obj->mass);
			strcpy(comment, "\nNew mass assigned succefully!");
		}
		// Radius
		else if(input == 5) {
			OPS ("Create A NEW OBJECT\n\nInsert the radius of the new object: (Km)", var);
			scanf("%Lf", &obj->radius);
			strcpy(comment, "\nNew radius assigned succefully!");
		}
		// Coordiates
		else if(input == 6) {
			OPS ("Create A NEW OBJECT\n\nInsert the position in the x axis of the new object: (Km)", var);
			scanf("%Lf", &obj->x);
			OPS ("Create A NEW OBJECT\n\nInsert the position in the y axis of the new object: (Km)", var);
			scanf("%Lf", &obj->y);
			OPS ("Create A NEW OBJECT\n\nInsert the position in the z axis of the new object: (Km)", var);
			scanf("%Lf", &obj->z);
			strcpy(comment, "\nNew coordinates assigned succefully!");
		}
		// Velocity
		else if(input == 7) {
			OPS ("Create A NEW OBJECT\n\nInsert the velocity in the x axis of the new object: (Km/s)", var);
			scanf("%Lf", &obj->velx);
			OPS ("Create A NEW OBJECT\n\nInsert the velocity in the y axis of the new object: (Km/s)", var);
			scanf("%Lf", &obj->vely);
			OPS ("Create A NEW OBJECT\n\nInsert the velocity in the z axis of the new object: (Km/s)", var);
			scanf("%Lf", &obj->velz);
			strcpy(comment, "\nNew velocity assigned succefully!");
		}
		// LOAD
		else if(input == 8) {
			// load the object in a temporany variable
			tobj new;
			// initialize new
			obj_LowInit(&new);
			BYTE result = obj_Load(&new, Stype, obj->name);
			// if success
			if (result == GOODSIGNAL) {
				// move cinematic stats
				new.x = obj->x;
				new.y = obj->y;
				new.z = obj->z;
				new.velx = obj->velx;
				new.vely = obj->vely;
				new.velz = obj->velz;
				// move the temp(the new) object in the location
				obj_Move(&new, obj);
				// positive comment (resetting the previous)
				strcpy(comment, "New object loaded succefully!");
			}
			// negative comment if fail
			else {
				strcat(comment, "\nCan't load the object! ");
				if (result == FILE_ERR_SIG)
					strcat(comment, "No object whit that name found!");
				else if (result == CORRUPTED_SIG)
					strcat(comment, "File corrupted or outdated!");
				else {
					strcat(comment, "Unregognized error signal");
					#if DEBUG
					debug_Printf("obj_Init: obj_Load returned a signal not parsable. Update the error parser!");
					debug_Int(result);
					#endif
				}
			}
		}
		// SAVE
		else if(input == 9) {
			obj_Save(obj);
			strcpy(comment, "\nNew object saved succefully!");
		}	
		// DONE
		else if(input == 10) {
			if (!((strcmp(mass_irregularity, IRREGULARITY) == 0) || (strcmp(color_irregularity, IRREGULARITY) == 0) || (obj->type == type_Search(Stype, "Choose a type")) ) )
				break;
			else
				strcpy(comment, "\nCannot exit! Fix irregularity first");
		}
		// EXIT WHITOUT SAVE
		else if(input == 11) {
			// wipe the new object and quit
			obj_Wipe(obj);
			return ABORTED_SIG;
		}
	}
	return GOODSIGNAL;
}

/***
 * This function is born as a higher level obj_Read that is memory leack and seg fault safe
 */
BYTE obj_InitFromFile(tobj *o, FILE *fp, tStype *s) {
	// make some basic initialization at the object to prevent memory leack (and seg fault)
	obj_LowInit(o);
	return obj_Read(fp, o, s);
}

/***
 * This function is born as a higher level obj_ReadComplete that is memory leack and seg fault safe
 */
BYTE obj_InitFromFileComplete(tobj *o, FILE *fp, tStype *s) {
	// make some basic initialization at the object to prevent memory leack (and seg fault)
	obj_LowInit(o);
	return obj_ReadComplete(fp, o, s);
}

/***
 * This function move an object in another position, overwriting it
 * p is the start position, d the destination
 * 
 * NOTE:
 * 	- This function doesn't switch the two object, but only move one,
 * 		so at the end there are two identical objects
 *	- This function move the pointer to the dinamically allocated memory too,
 * 		so there is no need to obj_Wipe an object after is copyied to delete the first one
 */
void obj_Move (tobj *obj, tobj *dest) {
	// if are the same object, exit
	if (obj == dest)
		return;
	// delete the old object in the destination
	obj_Wipe(dest);
	// move the object
	*dest = *obj;
}

/***
 * The load object function load from a file the settingrmation about a object
 */
BYTE obj_Load(tobj *obj, tStype *Stype, char *name) {
		
	FILE *ofile;				// (the) o(bject) file
	{	// From the name, get the file address
		char path [NAMELUN + 15];	// the path of the object
		
		strcpy(path, OBJECT_PATH);
		strcat(path, name);
		strcat(path, ".object");
		
		ofile = fopen(path, "r");
		if (ofile == NULL)
			return FILE_ERR_SIG;
	}	
	// Read the object
	obj_Read(ofile, obj, Stype);
		
	//close the file and exit
	fclose(ofile);
	
	return GOODSIGNAL;
}

/***
 *  init a object in a low level manner to prevent seg fault or memory leack when doing the REAL initialization
 */
void obj_LowInit (tobj *o) {
	
	o->name = NULL;
	o->type = NULL;
	o->data = NULL;
}


BYTE obj_Read (FILE *stream, tobj *obj, tStype *Stype) {
	TNAME buffer;	// temporany buffer that store the name of the object and the name of the type of the object
	// scan the name
	in_fs(buffer, stream);
	obj_Rename(obj, buffer);
	// scan the type
	in_fs(buffer, stream);
	obj->type = type_Search(Stype, buffer);
	// scan all the other things
	fscanf(stream, "%d\n%d\n%d\n%Lf\n%Lf", &obj->color.red, &obj->color.green, &obj->color.blue, &obj->radius, &obj->mass);
	if (obj->type == NULL)
		return CORRUPTED_SIG;
	return GOODSIGNAL;
}

BYTE obj_ReadComplete (FILE *stream, tobj *obj, tStype *Stype) {
	TNAME buffer;
	// scan the name
	in_fs(buffer, stream);
	obj_Rename(obj, buffer);
	// scan the type
	in_fs(buffer, stream);
	obj->type = type_Search(Stype, buffer);
	// scan the other stuff
	fscanf(stream, "%d\n%d\n%d\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n", &obj->color.red, &obj->color.green, &obj->color.blue, &obj->radius, &obj->mass, &obj->x, &obj->y, &obj->z, &obj->velx, &obj->vely, &obj->velz);
	if (obj->type == NULL)
		return CORRUPTED_SIG;
	return GOODSIGNAL;
}
/***
 * This function renames an object
 */
void obj_Rename(tobj *o, char *nn) {	// nn is New Name
	// Wipe the old name
	obj_WipeName(o->name);
	// resize the name buffer
	o->name = (char *) malloc (sizeof(char[strlen(nn)]));
	while(o->name == NULL) {
		OPS_MemLack("Obj_Rename");
		o->name = (char *) malloc (sizeof(char[strlen(nn)]));
	}
	// copy the name
	strcpy(o->name, nn);
}

/***
 * The obj_Save function save a object in a file
 */
void obj_Save(tobj *obj) {
	
	// the path where the object must be saved, an input variable and the destination file pointer
	char path[NAMELUN+16];
	char input[2];
	FILE *dest;
	
	// Write the path
	strcpy(path, OBJECT_PATH);
	strcat(path, obj->name);
	strcat(path, ".object");
	
	//control that the file isn't alredy existent
	dest = fopen(path, "r");
	if(dest != NULL) {
		fclose(dest);
		OPS("While saving: The object you want to save alredy exist.\nDo you want to delete the previous object and save this? [n = no | something else = y]", NULL);
		in_s(input);
		if(!strcmp(input, "n"))
			return;
	}

	// Write the object
	dest = fopen(path, "w");
	obj_Write(dest, obj);
	fclose(dest);
}

/***
 * 	This function frees the object memory that is dinamically allocated (for now only the name)
 */
void obj_Wipe(tobj *obj) {
	// free the name
	obj_WipeName(obj->name);
	// free the datas
	obj_WipeData(obj->data);
}

/***
 * 	This function free the dinamic allocated memory of the data struct
 */
void obj_WipeData(void *data){
	free(data);
	data = NULL;
}

/***
 * this function delete free the name of an object
 * the name then is set to NULL
 */
void obj_WipeName(char *name) {
	free(name);
	name = NULL;
}

void obj_Write (FILE *stream, tobj *obj) {
	fprintf(stream, "%s\n%s\n%d\n%d\n%d\n%.128Lf\n%.128Lf", obj->name, obj->type->name, obj->color.red, obj->color.green, obj->color.blue, obj->radius, obj->mass);
}
void obj_WriteComplete (FILE *stream, tobj *obj) {
	fprintf(stream, "%s\n%s\n%d\n%d\n%d\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n", obj->name, obj->type->name, obj->color.red, obj->color.green,obj->color.blue, obj->radius, obj->mass, obj->x, obj->y, obj->z, obj->velx, obj->vely, obj->velz);
}
