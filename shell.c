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
	
	int Shell (tStype *Stype) {
		DebugPrint("shell");
		
		// he pointer to a system
		tsys *sys;
		// a time var (simulation time)
		ttime stime;
		
		//////////////////////////////////////////
		// MENU AND SYSTEM INITIALIZATION
		
		while(1) {
			// here stime.year is used as temp variable
			if(inf.vmode == V_OPS)
				stime.year = Menu(Stype);
			else
				stime.year = GlMenu(Stype);
			// Call the mean menù, it tell to shell what to do.
			switch (stime.year) {
				case NEW_SIG:
					sys = InitSystem(Stype);
					break;
				case LOAD_SIG:
					sys = LoadSystem(Stype);
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
		// Use the right loop (inf.vmode)
		if (inf.vmode == V_OPS) {
			while(stime.year != QUITSIGNAL) {
				// call the phisic engine
				Pmotor (sys, stime);
				// Output
				OPSo (sys);
				// call the instruction parser and ask him for destination time
				stime = Parser(sys);
			}
		}
		else if (inf.vmode == V_SDL) {
			while(stime.year != QUITSIGNAL) {
				// call the phisic engine
				Pmotor(sys, stime);
				// output
				SGLGUI(sys);
				// instruction parser
				stime = GLparser(sys);
			}
		}

		// delete the system and exit
		free(sys->o);
		free(sys);

		return GOODSIGNAL;
	}
