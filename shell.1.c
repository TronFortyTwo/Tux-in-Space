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
 * This is the shell that connect everything and is the main program loop
 * 
 */

#include "generic.h"
#include "shell.h"
#include "system.h"
#include "menù.h"
#include "SDL_interface.h"
#include "pengine.h"
#include "OPSo.h"
#include "parser.h"

int Shell (tStype *Stype) {

	// he pointer to a system
	tsys *sys;
	// a time var (simulation time)
	ttime stime;
		
	//////////////////////////////////////////
	// menu_main AND SYSTEM INITIALIZATION
	
	while(1) {
		// here stime.year is used as temp variable
		if(set.vmode == V_OPS)
			stime.year = menu_main(Stype);
		else
			stime.year = Video_Menu(Stype);
		// Call the mean menù, it tell to shell what to do.
		switch (stime.year) {
			case NEW_SIG:
				sys = sys_Init(Stype);
				break;
			case LOAD_SIG:
				sys = sys_Load(Stype);
				break;
			case QUITSIGNAL:
				return QUITSIGNAL;				//there is no need to free the dinamycally allocated system like below because sys here isn't allocated yet
		}
		if (sys != NULL)
			break;
	}
		
		
	////////////////////////////////
	// SIMULATION LOOP
	//
		
	stime = sys->stime;
	// Use the right loop (set.vmode)
	if (set.vmode == V_OPS)
		while(stime.year != QUITSIGNAL) {
			// call the phisic engine
			Pengine (sys, stime);
			// Output
			OPSo (sys);
			// call the instruction parser and ask him for destination time
			stime = Parser(sys);
		}
	else if (set.vmode == V_SDL)
		while(stime.year != QUITSIGNAL) {
			// call the phisic engine
			Pengine(sys, stime);
			// output
			Video_SimGUI(sys);
			// instruction parser
			stime = Video_parser(sys);
		}

	// delete the system and exit
	sys_Free(sys);

	return GOODSIGNAL;
}
