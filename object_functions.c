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
 * This function is a file where there are function that manage the objects at low-level
 * 
 */

#include "CS_header.h"


/***
 * This function rezize the object buffer if needed
 */
	void UpdateObjBuf(tsys *sys) {
		if(sys->nalloc - sys->nactive >= OBJBUFSIZE)
			ReduceObjBuf(sys);
	}


/***
 * 	This function delete an object freeing the memory
 */
	void CleanObject(tobj *obj) {
		// free the name
		if(obj->name != NULL) {
			free(obj->name);
			obj->name = NULL;
		}
	}

/***
 * This function move an object in another position, overwriting it
 * p is the start position, d the destination
 * 
 * NOTE:
 * 	This function doesn't switch the two object, but only move one,
 * 	so at the end there are two identical objects
 */
	void MoveObject (tobj *p, tobj *d) {
		// if are the same object, exit
		if (p == d)
			return;
		// delete the old object in the destination
		CleanObject(d);
		// move the object
		*d = *p;
	}

/***
 * This function Delete an object from the system object buffer in an automatic way, ehitout the need of more free() or sys->nactive--, and resize the buffer. all the code is packed here
 * So, call it whitout worry
 * p is the position of the object or the pointer to the object. You have to choose which call, depending on your needs
 */
	void AutoRemoveObject (tsys *sys, tobj *p) {
		// Move the last object in the p position, update counters and free memory
		MoveObject(&sys->o[--sys->nactive], p);
		// if necessary resize the object buffer
		if(sys->nalloc - sys->nactive >= OBJBUFSIZE)
			ReduceObjBuf(sys);
	}


/***
 * OBJECT I/O       (READ/WRITE)
 * WriteObject write in the stream given the object.
 * WriteObjectComplete write in the stream given the object whit coordinates and velocity
 * ReadObject read in the stream given the object.
 * Read ObjectComplete read in the stream given the object whit coordinates and velocity
 */
	void WriteObject (FILE *stream, tobj *obj) {
		fprintf(stream, "%s\n%s\n%d\n%d\n%d\n%.128Lf\n%.128Lf", obj->name, obj->type->name, obj->color.red, obj->color.green, obj->color.blue, obj->radius, obj->mass);
	}
	void WriteObjectComplete (FILE *stream, tobj *obj) {
		fprintf(stream, "%s\n%s\n%d\n%d\n%d\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n", obj->name, obj->type->name, obj->color.red, obj->color.green,obj->color.blue, obj->radius, obj->mass, obj->x, obj->y, obj->z, obj->velx, obj->vely, obj->velz);
	}
	int ReadObject (FILE *stream, tobj *obj, tStype *Stype) {
		TNAME buffer;	// temporany buffer that store the name of the object and the name of the name of the type of the object
		// scan the name
		ScanFString(buffer, stream);
		obj->name = (char *) malloc (sizeof(char[strlen(buffer)]));
		while (obj->name == NULL) {
			OPSML("ReadObject");
			obj->name = (char *) malloc (sizeof(char[strlen(buffer)]));
		}
		strcpy(obj->name, buffer);
		// scan the type
		ScanFString(buffer, stream);
		obj->type = typeSearchName(Stype, buffer);
		// scan all the other things
		fscanf(stream, "%d\n%d\n%d\n%Lf\n%Lf", &obj->color.red, &obj->color.green, &obj->color.blue, &obj->radius, &obj->mass);
		if (obj->type == NULL)
			return CORRUPTED_SIG;
		return GOODSIGNAL;
	}
	int ReadObjectComplete (FILE *stream, tobj *obj, tStype *Stype) {
		TNAME buffer;
		// scan the name
		ScanFString(buffer, stream);
		obj->name = (char *) malloc (sizeof(char[strlen(buffer)]));
		while (obj->name == NULL) {
			OPSML("ReadObjectComplete");
			obj->name = (char *) malloc (sizeof(char[strlen(buffer)]));
		}
		strcpy(obj->name, buffer);
		// scan the type
		ScanFString(buffer, stream);
		obj->type = typeSearchName(Stype, buffer);
		// scan the other stuff
		fscanf(stream, "%d\n%d\n%d\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n", &obj->color.red, &obj->color.green, &obj->color.blue, &obj->radius, &obj->mass, &obj->x, &obj->y, &obj->z, &obj->velx, &obj->vely, &obj->velz);
		if (obj->type == NULL)
			return CORRUPTED_SIG;
		return GOODSIGNAL;
	}
