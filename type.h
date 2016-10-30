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
 *	(header file)
 */
#ifndef typeh
#define typeh
#include "generic.h"
#include "color.h"

// The size of a type's description. It must is bigger than NAMELUN
#define DESCRIPTIONSIZE 512

// The structure that represent a type of a object
typedef struct sStype {
	char *name;
	char *description;
	TNAME parent;
	double mass_min;			// Mass range
	double mass_max;
	tcolor color_max;			// Color range
	tcolor color_min;
	BYTE hunted;				// if are hunted by space monster (ON/OFF)
	BYTE hunter;				// if hunts (ON/OFF)
	char *product;				// if an object is destroyed, this is what can remains from it (type name)
} ttype;
	
// The structure whit all the types
typedef struct TypesStruct {
	WORD number;
	ttype *type;			// This is a pointer to the first member of the arrays that conteins all the types
} tStype;

// prototypes
tStype *type_Init (FILE *);						// Initialize the tStype structure from a file
ttype *type_Browser(tStype *, char *);			// Browse and choose a type
char *type_GetDescription (tStype *, char *);	// Get a description of a type
ttype *type_Search (tStype *, char *);			// Search a type from the name
char *type_GetParent (tStype *, char *);		// Get the parent from the name

#endif
