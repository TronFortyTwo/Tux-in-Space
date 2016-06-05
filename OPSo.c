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
 * This is a function of the Rmotor principal function.
 * The purpose of this is to print the state of the objects using only the OPS (OnlyPrintfSystem).
 * 
 * printf an intestation whit the current time and other stuff, then reserve some space for information about principal objects
 * 
 * 
 */

	int OPSo (tsys *sys, tinf *inf) {
		
		// this array contein the screen to return to send to OPS for printing. HIs size is inf.maxoutput but, because there are special string that occupy more than one character(like %s) we alloc more than the minimum
		char buffer[BUFFERSIZE];
		// the array to give to Rmotor whit size. there are 7 long double for every object (mass, x, y, z, velx, vely, velz)
		int ivar[5];
		long double *lvar = (long double *) malloc (sizeof(long double) * sys->nactive * 7);
		int lpos=0;
		// counters
		int i;
		// pointer to a object
		tobj *obj;
		
		// Printf the line whit the time and two lines of '-'
		strcpy (buffer, "TIME: Year %i | Day %i | %i:%i:%i,%i\n%f-%f-");
		ivar[0] = sys->year;
		ivar[1] = sys->day;
		ivar[2] = sys->hour;
		ivar[3] = sys->min;
		ivar[4] = sys->sec;
		ivar[5] = sys->millisec;
		
		// A loop that tell to every object something
		for (i=0; i!=sys->nactive; i++) {
			//set the pointer to the object we are using
			obj = &sys->o[i];
			//Tell the name, type and mass
			strcat(buffer, obj->name);
			strcat(buffer, " | ");
			strcat(buffer, obj->type->name);
			strcat(buffer, " | ");
			strcat(buffer, " mass of %l tons");
			lvar[lpos++] = obj->mass;
			//Tell the x '\n', the y a '\n' and the z
			strcat(buffer, "\nX axis: %l Km whit fast of %l Km/s\nY axis: %l Km whit fast of %l Km/s\nZ axis: %l Km whit fast of %l Km/s\n");
			lvar[lpos++]= obj->x;
			lvar[lpos++]= obj->velx;
			lvar[lpos++]= obj->y;
			lvar[lpos++]= obj->vely;
			lvar[lpos++]= obj->z;
			lvar[lpos++]= obj->velz;
			// A line of '-'
			strcat (buffer, "%f-");
		}
		
		//tell to Rmotor what has done
		OPS(inf, buffer, ivar, lvar);
		
		// dealloc the arrays
		free(lvar);
		
		return 0;
	}
