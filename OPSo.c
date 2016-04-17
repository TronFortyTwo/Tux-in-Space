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
 * printf anintestation whit the current time and other stuff, then reserve some space for information about principal objects
 * 
 */
	int OPSo (tsys *sys, tinf *inf);

	int OPSo (tsys *sys, tinf *inf) {
		
		// this array contein the screen to return to send to OPS for printing. HIs size is inf.maxoutput but, because there are special string that occupy more than one character(like %s) we alloc more than the minimum
		char phrase[8192];
		// the position in phrase
		short position = 0;
		// the position on the inf's variables
		short ivarpos = 0;
		// an array of int to send to OPS
		int iarray[8];
		
		// Now a line of '-' the current time, another line of '-' 
		// After every function we control if
		
		// current time
		position = position + Was (phrase, "Year:%i Day:%i Hour:%i.%i.%i,%i\n", position);
		iarray[ivarpos] = sys->year;
		ivarpos++;
		iarray[ivarpos] = sys->day;
		ivarpos++;
		iarray[ivarpos] = sys->hour;
		ivarpos++;
		iarray[ivarpos] = sys->min;
		ivarpos++;
		iarray[ivarpos] = sys->sec;
		ivarpos++;
		iarray[ivarpos] = sys->millisec;
		ivarpos++;
		
		// two line of '-'.
		position = position + Was (phrase, GetLine(inf, "-", 0) , position);
		
		
		phrase[position] = '\0';
		
		// tell to Rmotor to printf what elaborated
		Rmotor(sys, inf, 0, phrase, iarray, 0, 0);
		
		return 0;
	}
