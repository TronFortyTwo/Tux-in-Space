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
 * The purpose of this is to print the state of the objects using only the OPS (OnlyPrintfSystem).
 * 
 * printf an intestation whit the current time and other stuff, then reserve some space for information about the objects
 * 
 */

	int OPSo (tsys *sys, tinf *inf) {
		DebugPrint(inf, "opso");
		
		// this array contein the screen to return to send to OPS for printing. HIs size is inf.maxoutput but, because there are special string that occupy more than one character(like %s) we alloc more than the minimum
		char buffer[BUFFERSIZE];
		// the array to give to Rmotor whit size. there are 6 long double for every object (x, y, z, velx, vely, velz)
		void **var = (void *) malloc (sizeof(void *[sys->nactive * 8 + 6]));
		int pos;
		// counters
		int i;
		
		// Printf the line whit the time and two lines of '-'
		strcpy (buffer, "TIME: Year %i | Day %i | %i:%i:%i,%i\n%f-%f-");
		var[0] = & sys->stime.year;
		var[1] = & sys->stime.day;
		var[2] = & sys->stime.hour;
		var[3] = & sys->stime.min;
		var[4] = & sys->stime.sec;
		var[5] = & sys->stime.millisec;
		
		pos = 6;
		// A loop that tell to every object something
		for (i=0; i!=sys->nactive; i++) {
			// Tell the name, type and mass, the x, the y and the z. conclude whit a line of '-'
			strcat(buffer, "%s | %s\nX axis: %l Km whit fast of %l Km/s\nY axis: %l Km whit fast of %l Km/s\nZ axis: %l Km whit fast of %l Km/s\n%f-");
			var[pos] = sys->o[i].name;
			pos++;
			var[pos] = sys->o[i].type->name;
			pos++;
			var[pos] = &sys->o[i].x;
			pos++;
			var[pos] = &sys->o[i].velx;
			pos++;
			var[pos] = &sys->o[i].y;
			pos++;
			var[pos] = &sys->o[i].vely;
			pos++;
			var[pos] = &sys->o[i].z;
			pos++;
			var[pos] = &sys->o[i].velz;
			pos++;
		}
		// if there isn't any object
		if(sys->nactive == 0)
			strcat(buffer, "\n&t1The system is empty. Use the 'create' command to create a new object");
		
		// Print
		OPS(inf, buffer, var);
		
		// free the RAM and exit
		free(var);
		return 0;
	}
