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
 * 
 */
	
	void Shell (tinf *inf, tStype *Stype) {

		// Retruning value from the function
		int staterec;
		//the pointer to a system
		tsys *sys;
		//a time var
		ttime stime;
		
		do {
			// Call the mean menù, it tell to shell what to do.
			staterec = Menu(inf);
			// If the menù answered 0 the program initialize the system as new
			if (staterec == 0)
				sys = InitSystem(inf, Stype);
			if (staterec == 1)
				sys = LoadSystem(inf, Stype);
			if (sys != NULL)
				break;
		}
		while(1);
		//update this
		stime = sys->stime;
	
		// The simulation loop (infinite)
		do {
			// call the output system accordingly to vmode
			if (inf -> vmode == 0) {
				OPSo (sys, inf);
			}
			// call the instruction parser
			stime = Parser(sys, inf);
			// call the phisic motor how many times as Parser asks
			do {
				if(GetBiggerStime(&stime, &sys->stime) == 1)
					break;
				if(GetBiggerStime(&stime, &sys->stime) == 2)
					break;
				Pmotor(sys, inf);
			}
			while(1);
		}
		while(1);

		return;
	}
