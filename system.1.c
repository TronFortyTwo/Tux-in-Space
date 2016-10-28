/*
#################################################################################
#    CSpace - space simulator													#
#    Copyright (C) 2016  emanuele.sorce@hotmail.com								#
#																				#
#    This program is free software; you can redistribute it and/or modify		#
#    it under the terms of the GNU General Public License as published by		#
#    the Free Software Foundation, version 3 or compatibles.					#
#																				#
#    This program is distributed in the hope that it will be useful,			#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of				#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				#
#    GNU General Public License for more details.								#
#																				#
#    You should have received a copy of the GNU General Public License			#
#    along with this program; if not, write to the Free Software				#
#    Foundation, Inc.															#
#################################################################################
 *
 * Here we have functions that manage objects
 * 
 */

#include "system.h"
#include "OnlyPrintfSystem.h"
#include "in.h"
#include "debug.h"

// Internal functions
void sys_ReduceObjBuf	(tsys *);
void sys_ExtendObjBuf	(tsys *);
void sys_UpdateObjBuf	(tsys *);
tsys *sys_InitOPS 		(tStype *);
tsys *sys_LoadOPS 		(tStype *);

// Internal constants
#define OBJBUFSIZE 4	// When you alloc the object buffer, this is how many object you delete or Create when you resize

/***
 * This function prepare the object buffer for a new object and initialize it
 */
void sys_NewObj (tsys *sys) {
	// if there is no room in the buffer resize it
	if(sys->nalloc == sys->nactive)
		sys_ExtendObjBuf(sys);
	// initialize the new object (that is created in the last active postion of the buffer)
	// and update the counter
	obj_Init(&sys->o[sys->nactive++], sys->Stype);
}


/***
 * This function reduce the object buffer size if needed
 */
void sys_UpdateObjBuf(tsys *sys) {
	if(sys->nalloc - sys->nactive >= OBJBUFSIZE)
		sys_ReduceObjBuf(sys);
}


/***
 * This function Delete an object from the system object buffer in an automatic way, ehitout the need of more free() or sys->nactive--, and resize the buffer. all the code is packed here
 * So, call it whitout worry
 * p is the position of the object or the pointer to the object. You have to choose which call, depending on your needs
 */
void sys_RemoveObj (tsys *sys, tobj *p) {
	// Move the last object in the p position, update counters and free memory
	obj_Move(&sys->o[--sys->nactive], p);
	// if necessary resize the object buffer
	if(sys->nalloc - sys->nactive >= OBJBUFSIZE)
		sys_ReduceObjBuf(sys);
}

/***
 * This function reduce the object buffer size
 */
	 
void sys_ReduceObjBuf(tsys *sys) {
	
	tobj *backptr = sys->o;
	
	sys->o = (tobj *) realloc (sys->o, sys->nalloc-OBJBUFSIZE);
	if (sys->o == NULL){
		OPS_MemLack("Reduceobjbuf");
		sys->o = (tobj *) realloc (backptr, sys->nalloc-OBJBUFSIZE);
	}
	sys->nalloc+=OBJBUFSIZE;
}

	
/***
 * This function make the object buffer size bigger or create it if isn't allocated yet
 */
void sys_ExtendObjBuf(tsys *sys){
	
	tobj *backptr = sys->o;		//the old pointer
	
	sys->o = (tobj *) realloc (sys->o, sys->nalloc+OBJBUFSIZE);
	if (sys->o == NULL){
		OPS_MemLack("Extendobjbuf");
		sys->o = (tobj *) realloc (backptr, sys->nalloc+OBJBUFSIZE);
	}
	sys->nalloc+=OBJBUFSIZE;
}

/***
 * Save a system in the directory Systems/
 */
void sys_Save(tsys *sys){
	
	// the path where the system must be saved, an input variable and the destination file pointer
	char path[NAMELUN+13];
	char input[2];
	FILE *dest;
	// counter
	int i;
	
	// Write the path
	strcpy(path, SYSTEM_PATH);
	strcat(path, sys->name);
	strcat(path, ".sys");
	
	// control that the file isn't alredy existent
	dest = fopen(path, "r");
	if(dest != NULL) {
		fclose(dest);
		OPS("While saving: The system you want to save alredy exist.\nDo you want to delete the previous system and save this? [n = no | something else = y]", NULL);
		scanf("%s", input);
		if(strcmp(input, "n") == 0)
			return;
	}

	// Write the object
	dest = fopen (path, "w");
	// Write settingrmation about the system
	fprintf (dest, "%.128Lf\n%ld\n%.128Lf\n",  sys->precision, sys->nactive, sys->G);
	fprintf (dest, "%ld\n%d\n%d\n%d\n%d\n%d\n", sys->stime.year, sys->stime.day, sys->stime.hour, sys->stime.min, sys->stime.sec, sys->stime.millisec);	//the time
	// write the system's object's datas
	for(i=0; i!=sys->nactive; i++)
		obj_WriteComplete(dest, &sys->o[i]);
	fclose(dest);

	OPS("SYSTEM SAVED WHIT SUCCESS!\n\nPress something to continue", NULL);
	sgetchar();
}


/***
 * Switch between the OPS and the GL system initialization
 */
tsys *sys_Init (tStype *Stype) {

	if(set.vmode == V_OPS)
		return sys_InitOPS(Stype);
	OPS_Error("SDL UI can't do yet this. I'll send you to the OPS component. Press something to continue", NULL);
	sgetchar();
	return sys_InitOPS(Stype);
}
 

/***
 * InitSystemOPS is a function that initialize a new system
 */
tsys *sys_InitOPS (tStype *Stype) {
	
	// var to give to OPS and counter
	void *var;
	int c;
	// the system to Create
	tsys *sys = (tsys *) malloc (sizeof(tsys));
	while (sys == NULL) {
		OPS_MemLack("sys");
		sys = (tsys *) malloc (sizeof(tsys));
	}
	sys->o = NULL;
	
	// set the type struct pointer
	sys->Stype = Stype;
	// set the system's time
	sys->stime.year = 0;
	sys->stime.hour = 0;
	sys->stime.day = 0;
	sys->stime.min = 0;
	sys->stime.sec = 0;
	sys->stime.millisec = 0;
	
	// set the constant of gravitation. 6.67e-11 (m*m*m)/(Kg*s*s) but whit our units (t, s and Km) is 6.67e-17
	sys->G = 6.67e-17;
	
	// Ask for the name of the new system
	c = NAMELUN-1;
	var = &c;
	OPS ("NEW SYSTEM INITIALIZATION\n\nname of the system:\n&tdThe name can be of a maximum of %i characters and can't contein spaces", &var);
	scanf("%s", sys->name);
	//ask for the precision
	OPS ("NEW SYSTEM INITIALIZATION\n\nprecision of the simulation:\n&tdIndicate how much the simulation is precise. A big value mean leess precision but lighter hardware use.\nrecommended values: < 2", NULL);
	scanf("%Lf", &sys->precision);
	
	sys->nactive = 0;
	sys->nalloc = 0;
 
 	return sys;
}

/***
 * Switch between LoadSystemOPS and LoadSystemGl
 */
tsys *sys_Load(tStype *Stype){
	if(set.vmode == V_OPS)
		return sys_LoadOPS(Stype);
	OPS_Error("SDL UI can't do yet this. I'll send you to the OPS component. Press something to continue", NULL);
	sgetchar();
	return sys_LoadOPS(Stype);
}


/**
 * Load a system from a file using OPS
 * Create a new system and return his pointer
 */
tsys *sys_LoadOPS (tStype *Stype) {

	char path[NAMELUN+12];	// the system file (path)
	FILE *sysfp;			// the system file (pointer)
	int i;					// counter
	tsys *sys = (tsys *) malloc (sizeof(tsys));		// the new system
	while(sys == NULL){
		OPS_MemLack("sys_Init");
		sys = (tsys *) malloc (sizeof(tsys));
	}
	// ask which system
	OPS("LOAD SYSTEM\n\nWhat is the name of the system you want to load?", NULL);
	in_s(sys->name);
	// write the path
	strcpy (path, SYSTEM_PATH);
	strcat (path, sys->name);
	strcat (path, ".sys");
	// open the file
	sysfp = fopen(path, "r");
	if (sysfp == NULL) {
		OPS_Error("A system whit that name doesn't exist! Type something to continue and return to the main menu", NULL);
		sgetchar();
		free(sys);
		return NULL;
	}
	// scanf system's settingrmations
	fscanf (sysfp, "%Lf\n%ld\n%Lf\n", &sys->precision, &sys->nactive, &sys->G);
	fscanf (sysfp, "%ld\n%d\n%d\n%d\n%d\n%d\n", &sys->stime.year, &sys->stime.day, &sys->stime.hour, &sys->stime.min, &sys->stime.sec, &sys->stime.millisec);
	// alloc memory
	sys->nalloc = 0;
	while (sys->nalloc < sys->nactive)
		sys->nalloc += OBJBUFSIZE;
	sys->o = (tobj *) malloc (sizeof(tobj[sys->nalloc]));
	while (sys->o == NULL) {
		OPS_MemLack("sys_Load");
		sys->o = (tobj *) malloc (sizeof(tobj[sys->nalloc]));
	}
	// fscanf for objects datas
	for(i=0; i!=sys->nactive; i++) {
		if(obj_InitFromFileComplete(&sys->o[i], sysfp, Stype) == CORRUPTED_SIG) {
			#if DEBUG
			debug_Printf("(!) the system to load seem corrupted or outdated! While loading the object (read below):");
			debug_Printf(sys->o[i].name);
			#endif
		}
	}
	fclose(sysfp);
	sys->Stype = Stype;
	if(sys->nalloc == 0)
		sys->o = NULL;
	return sys;
}

/***
 * the function search object search a object in a system whit a name and return his pointer or NULL if there isn't any object whit that name
 */
tobj *sys_SearchObj(tsys *sys, char *name) {
	int i;
	for (i=0; i != sys->nactive; i++)
		if(!strcmp(sys->o[i].name, name))
			return &sys->o[i];
	return NULL;
}

/***
 * This function free a system (mem leack safe). MUST USE when exiting a simulation!
 */

void sys_Free (tsys *sys) {
	
	int i;
	
	// free all the objects of the buffer
	for(i=0; i!= sys->nactive; i++)
		obj_Wipe(&sys->o[i]);
	// free the buffer of objects
	free(sys->o);
	free(sys);
}
