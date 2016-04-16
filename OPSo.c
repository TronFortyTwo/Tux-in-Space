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
 * printf a intestation whit the current time and other stuff, then reserve some space for information about principal objects
 * 
 */
	int OPSo (tsys *sys, tinf *inf);

	int OPSo (tsys *sys, tinf *inf) {
		
		// this array contein the screen to return to send to OPS for printing. HIs size is inf.maxoutput but, because there are special string that occupy more than one character(like %s) we alloc more than the minimum
		char phrase[4096];
		// the position in phrase
		short position = 0;
		// the position on the inf's variables
		short ivarpos = 0;
		// 4 if in overflow, 0 if not
		short overflow = 0;
		
		// Now a line of '-' the current time, another line of '-' 
		// After every function we control if in writing we go on overflow. If yes stop elaborating the string.
		
		// save a line of '-' in inf.cvar[0] whitout '\0' character (needed later)
		GetLine(inf, "-", 2*FRAMELUN, 0);
		
		// current time
		if(overflow == 0) {
			position = position + Was (&phrase[0], "Year:%i Day:%i Hour:%i.%i.%i,%i\n", position);
			inf->ivar[ivarpos] = sys->year;
			ivarpos++;
			inf->ivar[ivarpos] = sys->day;
			ivarpos++;
			inf->ivar[ivarpos] = sys->hour;
			ivarpos++;
			inf->ivar[ivarpos] = sys->min;
			ivarpos++;
			inf->ivar[ivarpos] = sys->sec;
			ivarpos++;
			inf->ivar[ivarpos] = sys->millisec;
			ivarpos++;
			if(position == -1)
				overflow = 4;
		}
		// two line of '-'. Remember that in inf->cvar[0] is the line of '-'
		if(overflow == 0) {
			position = position + Was (&phrase[0], inf->cvar[0], position);
			if(position == -1)
				overflow = 4;
		}
		
		phrase[position] = '\0';
		
		// tell to Rmotor to printf what elaborated
		Rmotor(sys, inf, 0, phrase);
		
		return 0;
	}
