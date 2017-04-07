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
 * This is the shell that connect everything and is the main program loop
 * 
 */

#include "shell.h"

using namespace std;

BYTE Shell (setting& set, typeSTR& stype) {
	
	// a pointer to the system-c
	system_c *sys;
	
	//////////////////////////////////////////
	// MENU AND SYSTEM INITIALIZATION
	
	BYTE result;
	
	// Call the mean menù, it tell what to do.
	switch (menu_main(set)) {
		case NEW_SIG:
			sys = new system_c(set, stype);
			break;
		case LOAD_SIG:
			sys = new system_c(set, stype, result);
			break;
		case QUIT_SIG:
			return QUIT_SIG;
	}
		
		
	////////////////////////////////
	// SIMULATION LOOP
	//
		
	time_sim stime = sys->stime;
	// Use the right loop (set.vmode) (for now only V_OPS availabile)
	/*
	if (set.vmode == V_OPS)
	*/
		while(stime.year != QUIT_SIG) {
			// call the phisic engine
			sys->Physic (stime);
			// Output
			OPSo (set, *sys);
			// call the instruction parser and ask him for destination time
			stime = Parser(set, *sys);
			// loading message
			OPS(set, "Loading...", nullptr);
		}
	/*
	else if (set.vmode == V_GL) {
			GUI implementation
		}
	*/

	delete sys;
	return GOOD_SIG;
}
