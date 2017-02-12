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
 * The purpose of this is to Create a friendly UI using only the OPS (OnlyPrintfSystem).
 * 
 * print an intestation whit the current time and other stuff, then reserve some space for settingrmation about the objects
 * 
 */

#include "OPSo.h"

using namespace std;

void OPSo (const setting& set, system_c& sys) {
		
	// this array contein the screen to send to OPS for printing
	string buffer;
	// the array to give to OPS whit size. there are 6 long double for every object (x, y, z, velx, vely, velz)
	vector<void *> var;
		
	// Printf the line whit the time and two lines of '-'
	buffer = "TIME: Year %i | Day %i | %i:%i:%i,%i\n%f-%f-";
	var.reserve(6);
	var[0] = & sys.stime.year;
	var[1] = & sys.stime.day;
	var[2] = & sys.stime.hour;
	var[3] = & sys.stime.min;
	var[4] = & sys.stime.sec;
	var[5] = & sys.stime.millisec;
	
	// if there isn't any object
	if (sys.nobj) {
		// A loop that tell to every object something
		for (int i=0; i!=sys.nobj; i++) {
			// Tell the name, type and mass, the x, the y and the z. conclude whit a line of '-'
			buffer += "%s | %s\nX axis: %l Km whit fast of %l Km/s\nY axis: %l Km whit fast of %l Km/s\nZ axis: %l Km whit fast of %l Km/s\n%f-";
			var.reserve(var.size()+8);
			var.push_back(&sys.o[i].name);
			var.push_back(&sys.o[i].typ->name);
			var.push_back(&sys.o[i].posx);
			var.push_back(&sys.o[i].velx);
			var.push_back(&sys.o[i].posy);
			var.push_back(&sys.o[i].vely);
			var.push_back(&sys.o[i].posz);
			var.push_back(&sys.o[i].velz);
		}
	}
	else
		buffer += "\n&t1The system is empty.&t2\nUse the 'create' command to create a new object\nUse the 'help' command for help";
	
	// Print all
	OPS(set, buffer, &var[0]);
}
