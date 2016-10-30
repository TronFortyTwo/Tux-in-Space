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
 *	Object oriented file where Create a "class" object, giving a coerent and fast API to the program
 * 
 * 	all these function have the obj_ prefix.
 * 	You can't modify a object whitout pass throught a obj_ function
 *
 *	HEADER FILE
 */

#ifndef objecth
#define objecth

#include "generic.h"
#include "time.h"
#include "type.h"

// Object structure
typedef struct object {
	char *name;				// the name of the object
	ttype *type;			// the type of object
	long double	radius;		// the object for now are sphere
	long double mass;
	long double x;
	long double y;
	long double z;
	long double velx;		// velocity on x
	long double vely;		// velocity on y
	long double velz;		// velocity on z
	tcolor color;			// the color
	void *data;				// type specific information about the object (coming soon ;)
} tobj;

// Functions that can called from everywhere
// NOTE:
// Is deprecated the modify the obj structure whitout passing through one of these functions
// All these funtions should be memory leack and seg fault safe
void obj_Move 					(tobj *, tobj *);			// Move the first object in the second position
void obj_GetBigger 				(tobj *, tobj *, tobj **);	// Move the bigger of the two object in the third position
void obj_Wipe					(tobj *);					// Clean the dinamic memory of an object
BYTE obj_Load					(tobj *, tStype *, char *);	// Load an object from a file
void obj_Save					(tobj *);					// Save the object in a file
void obj_Init 					(tobj *, tStype *);			// Init a new object
void obj_Rename					(tobj *, char *);			// Rename an object safely
long double obj_Distance		(tobj *, tobj *);			// Compute the distance between two objects
BYTE obj_InitFromFile			(tobj *, FILE *, tStype *);	// Init an object from a file
BYTE obj_InitFromFileComplete	(tobj *, FILE *, tStype *);	// Init an object from a file already opened
void obj_Write 					(FILE *, tobj *);			// Write in a file an object already opened
void obj_WriteComplete			(FILE *, tobj *);			// Write in a file an object whit coordinates
void obj_SetType				(tobj *, tStype *, char *);	// Give to the object the type whit the name given
// ONLY THE PHISIC MOTOR CAN USE THIS!!! HOWEVER IS DEPRECATED THAT
void obj_LowInit				(tobj *);					// init a object in a low level manner to prevent seg fault or memory leack when doing the REAL initialization


#endif
