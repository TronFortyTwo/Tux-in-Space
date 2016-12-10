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
 * This is the instruction's parser. elaborate the input and do what these sentences in this strange human language would say.
 * 
 */

#include "Parser.h"
#include "generic.h"
#include "OnlyPrintfSystem.h"
#include "in.h"
#include "system.h"
#include "math.h"
#include "time.h"
#include "menù.h"

// internal functions
void parser_Reask(char *);
void sys_Save(tsys *);
void parser_Create(tsys *);
void parser_Delete(tsys *);
ttime parser_Quit (tsys *, ttime *);
void parser_Distance(tsys *);
ttime parser_Jump(ttime *, long double *);
ttime parser_Wait(ttime *, long double *);
void parser_Information (tsys *);

// internal constants
#define COMMANDLENGHT 64	// the max lenght of a command word

/**
 * The main function
 * of the parser
 */
ttime Parser(tsys *sys) {
		
	// what is scanned
	char input[COMMANDLENGHT+1];
	// the time we want (simulation)
	ttime t = sys->stime;
		
	// Now for every possible command call the correct command's function or simply do it if is short.
	// when you write a new command, you must add the corrispondent if and add it
	in_s(input);
	// continue
	if ((!strcmp("step", input)) || (!strcmp("s", input))) {
		t.millisec += 1000 * sys->precision;
		time_Update(&t);
	}
	// help
	else if ((!strcmp("help", input)) || (!strcmp("h", input))) {
		OPS("HELP\n\nYou have to press commands to manage the system. Insert a command to visualize his interface. Some commands are:\n-step (s)\n-create (c)\n-jump (j)\n-wait (w)\n-information (i)\n-settings\n-save\n-distance\n-quit\n-delete\n\nPress something to continue...", NULL);
		scanf("%s", input);
	}
	// parser_Jump
	else if ((!strcmp("jump", input)) || (!strcmp("j", input)))
		t = parser_Jump(&sys->stime, &sys->precision);
		
	// parser_Settings
	else if ((!strcmp("information", input)) || (!strcmp("i", input)) ||  (!strcmp("info", input)))
		parser_Information(sys);
	// parser_Wait
	else if ((!strcmp("wait", input)) || (!strcmp("w", input)))
		t = parser_Wait(&sys->stime, &sys->precision);
	// parser_Create
	else if (!(strcmp("create", input)) || (!strcmp("c", input)))
		parser_Create(sys);
	// parser_Quit / exit
	else if (!(strcmp("quit", input)) || (!strcmp("exit", input)))
		t = parser_Quit(sys, &sys->stime);
	// save
	else if (!strcmp("save", input))
		sys_Save(sys);
	//distance
	else if (!strcmp("distance", input))
		parser_Distance(sys);
	// delete an object
	else if (!(strcmp("delete", input)) || (!strcmp("remove", input)))
		parser_Delete(sys);
	// settings
	else if (!(strcmp("settings", input)) || (!strcmp("configuration", input)))
		menu_Settings(sys);
	// wrong command
	else {
		parser_Reask(input);
		sgetchar();
	}
	// Print a loading message
	OPS("Loading...", NULL);
		 
	return t;
}
	
/**
 * The parser_Reask function. parser_Reask the input
 */
void parser_Reask(char *command){
	void *var = command;
	OPS_Error("Sorry. But the command %s that you wrote is unknown. Press something to continue:", &var);
	return;
}
	
/***
 * This command calculate and show the distance between two objects
 */
void parser_Distance(tsys *sys){
	
	TNAME name;
	tobj *o;
	tobj *u;
	long double distance[2];
	void *var[2];
	
	//ask which two object
	OPS("DISTANCE\n\nCalculate the distance between two objects.\n\n&t2Insert the name of the first object:", NULL);
	in_s(name);
	o = sys_SearchObj(sys, name);
	if(o == NULL) {
		OPS_Error("There isn't any object whit that name!\n\nInsert a new command", NULL);
		return;
	}
	OPS("DISTANCE\n\nCalculate the distance between two objects.\n\n&t2Insert the name of the second object:", NULL);
	in_s(name);
	u = sys_SearchObj(sys, name);
	if(u == NULL) {
		OPS_Error("There isn't any object whit that name!\n\nInsert a new command", NULL);
		return;
	}
	distance[0] = math_Pitagora3D(o->x-u->x, o->y-u->y, o->z-u->z);
	distance[1] = math_Pitagora3D(o->x+o->velx-(u->x+u->velx), o->y+o->vely-(u->y+u->vely), o->z+o->velz-(u->z+u->velz)) - distance[0];
	var[0] = distance;
	var[1] = &distance[1];
	OPS("DISTANCE\n\nThe distance between the two object is:\n&td%l Km\n&t0And, if the two object take constant velocity, the distance will change at a velocity of\n&td%l km/s\n\n&t0Press something to continue...", var);
	scanf("%s", name);
		
	return;
}
	
/***
 * This function prepare the parser to parser_Quit
 */
ttime parser_Quit (tsys *sys, ttime *now){
		
	ttime t;	 	//this is the escape time
	char input;		
	//ask for confirm to parser_Quit
	OPS("QUIT\n\nAre you sure you want to quit? [y/n]\nOr you want to save before go? [s]", NULL);
	scanf(" %c", &input);
	//if doesn't want to parser_Quit return now
	if (input == 'n')
		return *now;
	if (input == 's')
		sys_Save(sys);
	else if (input != 'y') {
		OPS("Unrecognized input! please insert y/n/s\n\ninsert a new command:", NULL);
		return *now;
	}
	// now we prepare the parser_Quit event
	t = *now;
	t.year = QUITSIGNAL;		// <------ THIS IS THE SIGNAL THAT WE WANT TO parser_Quit
	return t;
}
	
/***
 * This function delete an object
 */
void parser_Delete(tsys *sys) {
		
	TNAME name;			//the name of the object
	tobj *obj;			//the pointer to the object
		
	// ask the user for the name
	OPS("DELETE\n\nWhich object do you want do delete?\n\n&t1Press 'n' to Quit", NULL);
	in_s(name);
	if (!strcmp(name, "n"))
		return;
		
	// search the object
	obj = sys_SearchObj(sys, name);
	if (obj == NULL) {	//if there isn't any object whit that name
		OPS_Error("There isn't any object whit that name!\nPress something to continue", NULL);
		sgetchar();
		return;
	}
		
	// delete the object
	sys_RemoveObj(sys, obj);
}
	
/***
 * parser_Settings about the system and the objects
 */
void parser_Information(tsys *sys) {
		
	tobj *obj;		// The object to describe
	void *var[13];	// The variables to give to OPS
	TNAME input;

	var[0] = sys->name;
	var[1] = &sys->nactive;
	// Generic informations about the system
	OPS("Informations\n\nSystem %s whit %i objects\n\nOf which object do you want informations? press 'n' to not display any object informations", var);
	in_s(input);
	if(strcmp(input, "n") == 0){
		OPS("Insert a new command", NULL);
		return;
	}
	// information about a precise object
	obj = sys_SearchObj(sys, input);
	if(obj == NULL){
		OPS_Error("No object whit this name is been found. press a button to continue", NULL);
		sgetchar();
		return;
	}	
	var[0] = obj->name;
	var[1] = obj->type->name;
	var[2] = &obj->color.red;
	var[3] = &obj->color.green;
	var[4] = &obj->color.blue;
	var[5] = &obj->mass;
	var[6] = &obj->radius;
	var[7] = &obj->x;
	var[8] = &obj->y;
	var[9] = &obj->z;
	var[10] = &obj->velx;
	var[11] = &obj->vely; 
	var[12] = &obj->velz; 
	OPS("Informations about %s\n%f-type: %s\n%f-color: &td \nred: %i\ngreen: %i\nblue: %i &t0 \n%f-mass: %l\n%f-radius: %l\n%f-x: %l\n\ny: %l\n\nz: %l\n%f-velocity in x: %l\n\nvelocity in y: %l\n\nvelocity in z: %l\n%f-\n\nPress somthing to continue...", var);
	sgetchar();
}
	
	
/***
 * The parser_Wait function make the simulation parser_Wait for a while. The user say how much 
 */
ttime parser_Wait(ttime *now, long double *precision) {
		
	ttime t;
		
	OPS("Wait\n\nInsert the settingrmation about how much simulation-time you want to wait\n<year> <day> <hour> <minute> <second> <millisecond>\nThe operation will be made whit an error of max %l seconds", (void **)&precision);
	//scanf the time
	scanf("%ld", &t.year);
	scanf("%d", &t.day);
	scanf("%d", &t.hour);
	scanf("%d", &t.min);
	scanf("%d", &t.sec);
	scanf("%d", &t.millisec);
	// elabore the new time and return
	t.millisec += now->millisec;
	t.sec += now->sec;
	t.min += now->min;
	t.hour += now->hour;
	t.day += now->day;
	t.year += now->year;
	time_Update(&t);
	return t;
}
	
/***
 * The parser_Jump function make the simulation Jump to a determined time 
 */
ttime parser_Jump(ttime *now, long double *precision) {

	ttime t;
	void *var[7];
	// set the var to give to OPS
	var[0] = &now->year;
	var[1] = &now->day;
	var[2] = &now->hour;
	var[3] = &now->min;
	var[4] = &now->sec;
	var[5] = &now->millisec;
	var[6] = &precision;
	
	OPS("Jump\n\nInsert the information about the moment you want to jump\n<year> <day> <hour> <minute> <second> <millisecond>\nThe actual time is: YEAR %i DAY %i TIME %i:%i:%i.%i\nThe jump will be made whit an error of max %l seconds" , var);
	while(1) {
		// year
		scanf("%ld", &t.year);
		// day
		scanf("%d", &t.day);
		// hour
		scanf("%d", &t.hour);
		// minute
		scanf("%d", &t.min);
		// second
		scanf("%d", &t.sec);
		// millisecond
		scanf("%d", &t.millisec);
		// update the time
		time_Update(&t);
		if(time_GetBigger(&t, now) == 1)	{ // if the time given is 
			// Error message if the time given isn't valid
			t = *now;
			OPS_Error("The time given is out of range! Please put a time that is future to the actual time, that is:\nYEAR %i DAY %i TIME %i:%i:%i.%i\nThe jump will be made whit an error of max %l seconds", var);
		}
		else
			break;
	}
	time_Update(&t);
	return t;
}
	
	
/***
 * The parser_Create function parser_Create a new object
 */
void parser_Create(tsys *sys) {
	// create a new object
	sys_NewObj(sys);
}
