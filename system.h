/*
#########################################################################################
#    CSpace - space simulator															#
#    Copyright (C) 2016  emanuele.sorce@hotmail.com										#
#																						#
#    This program is free software; you can redistribute it and/or modify				#
#    it under the terms of the GNU General Public License as published by				#
#    the Free Software Foundation, version 3 or compatibles.							#
#																						#
#    This program is distributed in the hope that it will be useful,					#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of						#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						#
#    GNU General Public License for more details.										#
#																						#
#    You should have received a copy of the GNU General Public License					#
#    along with this program; if not, write to the Free Software						#
#    Foundation, Inc.																	#
#########################################################################################
 *
 * Here we have functions that manage objects
 * 
 * 	(header file)
 */

#ifndef systemh
#define systemh

#include "generic.h"
#include "object.h"
#include "time.h"


// one system's structure: include the objects, the name and the number, the active object's position, the time of the system and the G constant of universal gravitation
typedef struct system {
	char *name;
	long double precision;	// Precision of the simulation (in second)
	ttime stime;			// the time of the simulation
	QWORD nactive;			// number of objects active
	QWORD nalloc;			// number of objects allocated
	tobj *o;				// the pointer to the dinamic allocated array of objects
	long double G;
	tStype *Stype;			// The pointer at the structure that coontein all the type
} tsys;
	
// prototypes of functions that can be called from everywhere
tsys *sys_Init		(tStype *);				// Init a new system
tsys *sys_Load		(tStype *);				// Load a system from a file
tobj *sys_SearchObj	(tsys *, char *);		// Search for an object in the system from his name
void  sys_RemoveObj (tsys *, tobj *);		// Remove an object from a system
void  sys_Save		(tsys *);				// Save an object in a file
void  sys_Free		(tsys *);				// Free all the dinamic allocated things in the sys structure (must use before close a system)
void  sys_NewObj	(tsys *);				// Create a new object and initialize it

#endif
