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
 * This is the shell that connect the engines and the user
 * 
 * whit some others elaboration in the middle
 */
	
	int Shell (tinf *inf, tStype *Stype) {
		DebugPrint(inf, "shell");
		
		// he pointer to a system
		tsys *sys;
		// a time var (simulation time)
		ttime stime;
		
		//////////////////////////////////////////
		// MENU AND SYSTEM INITIALIZATION
		
		while(1) {
			// Call the mean menù, it tell to shell what to do.
			switch (Menu(inf, Stype)) {
				case NEW_SIG:
							sys = InitSystem(inf, Stype);
							break;
				case LOAD_SIG:
							sys = LoadSystem(inf, Stype);
							break;
				case QUITSIGNAL:
							return QUITSIGNAL;				//there is no need to free the dinamycally allocated system like below because sys here isn't allocated yet
			}
			if (sys != NULL)
				break;
		}
		
		//update this
		stime = sys->stime;
	
		////////////////////////////////
		// SIMULATION LOOP
		//
		
		while(1) {
			// call the output system accordingly to vmode
			switch (inf->vmode) {
				case V_OPS: 
						OPSo (sys, inf);
						break;
				default:
						OPSo (sys, inf);
			}
			// call the instruction parser
			stime = Parser(sys, inf);
			//check if the user want to exit
			if (stime.year == QUITSIGNAL)
				break;
			// call the phisic motor how many times as Parser asks
			Pmotor (sys, inf, stime);
		}

		// delete the system and exit
		free(sys->o);
		free(sys);

		return 0;
	}
