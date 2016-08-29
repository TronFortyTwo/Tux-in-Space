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
	
	int Shell (tStype *Stype) {
		DebugPrint("shell");
		
		// he pointer to a system
		tsys *sys;
		// a time var (simulation time)
		ttime stime;
		
		//////////////////////////////////////////
		// MENU AND SYSTEM INITIALIZATION
		
		while(1) {
			// Call the mean menù, it tell to shell what to do.
			switch (Menu(Stype)) {
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
		while(1) {
			// call the output system accordingly to inf->vmode (for now can be only OPSo, OpenGL interface implementation is WIP)
			OPSo (sys);
			// call the instruction parser and ask him for destination time
			stime = Parser(sys);
			// check if the user want to exit
			if (stime.year == QUITSIGNAL)
				break;
			// call the phisic motor
			Pmotor (sys, stime);
		}

		// delete the system and exit
		free(sys->o);
		free(sys);

		return GOODSIGNAL;
	}
