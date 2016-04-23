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
 * NOTE:
 * For smart allocation, this is a recursive function, so the last two paramater when normally calling the function must be setted to 0
 * 
 * 
 */
	int OPSo (tsys *sys, tinf *inf);

	int OPSo (tsys *sys, tinf *inf) {
		
		// this array contein the screen to return to send to OPS for printing. HIs size is inf.maxoutput but, because there are special string that occupy more than one character(like %s) we alloc more than the minimum
		char buffer[BUFFERSIZE];
		//the type of the object
		char type[30];
		// the array to give to Rmotor whit size
		int ivar[5];
		long double *lvar = (long double *) malloc (sizeof(long double) * sys->nactive * 7);
		short lpos=0;
		// counters
		short i;
		short count;
		// pointer to a object
		tobj *obj;
		
		// Printf the line whit the time.
		strcpy (buffer, "TIME: Year %i | Day %i | %i:%i:%i,%i\n");
		ivar[0] = sys->year;
		ivar[1] = sys->day;
		ivar[2] = sys->hour;
		ivar[3] = sys->min;
		ivar[4] = sys->sec;
		ivar[5] = sys->millisec;
		// Write two lines of '-'
		for(i=0; i!=inf->width-2*FRAMELUN; i++) {
			strcat (buffer, "--");
		}
		
		// A loop that tell to every object something
		for (i=0; i!=sys->nactive; i++) {
			//set the pointer to the object we are using
			obj = &sys->o[sys->active[i]];
			//Tell the name, type and mass
			strcat(buffer, obj->name);
			strcat(buffer, " | ");
			ExtractType(obj->type, type);
			strcat(buffer, type);
			strcat(buffer, " | ");
			strcat(buffer, " mass of %l Kg");
			lvar[lpos++] = obj->mass;
			//Tell the x '\n', the y a '\n' and the z
			strcat(buffer, "\nX axis: %l Km whit fast of %l Km/s\nY axis:%l Km whit fast of %l Km/s\nZ axis: %l Km whit fast of %l Km/s\n");
			lvar[lpos++]= obj->x;
			lvar[lpos++]= obj->velx;
			lvar[lpos++]= obj->y;
			lvar[lpos++]= obj->vely;
			lvar[lpos++]= obj->z;
			lvar[lpos++]= obj->velz;
			// A line of '-'
			for(count=0; count!=inf->width-2*FRAMELUN; count++) {
				strcat (buffer, "-");
			}
		}
		
		//tell to Rmotor what is done
		OPS(inf, buffer, ivar, lvar);
		
		// dealloc the arrays
		free(lvar);
		
		return 0;
	}
