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
 * TIME LINE
 * ------------------------------
 * ------------------------------
 * 
 * Name    x     velx
 * Type    y     vely
 * mass    z     velz
 * 
 * ------------------------------
 * 
 * ...
 * 
 * 
 * 
 * 
 */
	int OPSo (tsys *sys, tinf *inf);

	int OPSo (tsys *sys, tinf *inf) {
		
		// this array contein the screen to return to send to OPS for printing. HIs size is inf.maxoutput but, because there are special string that occupy more than one character(like %s) we alloc more than the minimum
		char buffer[BUFFERSIZE];
		// the array to give to Rmotor whit size
		int ivar[5];
		long double *lvar = (long double *) malloc (sizeof(long double) * sys->nactive * 7);
		short lpos=0;
		//counter
		short i;
		// secondary little buffer
		char littlebuffer[30];
		
		// Printf the line whit the time.
		strcpy (buffer, "Year %i | Day %i | %i:%i:%i,%i\n");
		ivar[0] = sys->year;
		ivar[1] = sys->day;
		ivar[2] = sys->hour;
		ivar[3] = sys->min;
		ivar[4] = sys->sec;
		ivar[5] = sys->millisec;
		// Write two lines of '-'
		strcat (buffer, GetLine(inf, "-", 2*FRAMELUN));
	    strcat (buffer, GetLine(inf, "-", 2*FRAMELUN));
		strcat (buffer, "\n\n");
		// a loop for every object of the system
		for (i=0; i!=sys->nactive; i++) {
			// Write the name of the object
			strcat (buffer, sys->o[sys->active[i]].name);
			// Make some space and printf the x position, other space and the fast in x, then new line. alloc the long double array
			strcat (buffer, "    x axis: %l whit a fast of %l\n");
			lvar[lpos] = sys->o[sys->active[i]].x;
			lpos++;
			lvar[lpos] = sys->o[sys->active[i]].velx;
			lpos++;
			// Write the type of the object
			ExtractType(sys->o[sys->active[i]].type, littlebuffer);
			strcat (buffer, littlebuffer);
			// Write the y and his fast
			strcat (buffer, "    y axis: %l whit a fast of %l\n");
			lvar[lpos] = sys->o[sys->active[i]].y;
			lpos++;
			lvar[lpos] = sys->o[sys->active[i]].vely;
			lpos++;
			// Write in a new line: mass, z and z fast
			strcat (buffer, "mass: %l    z axis:%l whit an fast of %l\n");
			lvar[lpos] = sys->o[sys->active[i]].mass;
			lpos++;
			lvar[lpos] = sys->o[sys->active[i]].z;
			lpos++;
			lvar[lpos] = sys->o[sys->active[i]].velz;
			lpos++;
			// Write the final line of '-'
			strcat (buffer, GetLine(inf, "-", 2*FRAMELUN));
			
		}
		
		//tell to Rmotor what is done
		Rmotor(sys, inf, 0, buffer, ivar, lvar, 0);
		
		// dealloc the array
		free(lvar);
		
		return 0;
	}
