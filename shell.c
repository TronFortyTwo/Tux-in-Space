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
 *	Structure of Shell:
 *
 *	1)Receive basic instruction from Main
 *	2)Converse whit the phisic motor (Pmotor)
 *	3)Converse whit the user via OPSo or others
 *	4)Converse whit the user
 *	5)Goto 2 or goto 6
 *  6)Return to main
 * 
 * 	whit some others elaboration in the middle
 * 
 */
	
	void Shell (tinf *inf, tStype *Stype) {

		// Retruning value from the function
		int staterec;
		//the pointer to a system
		tsys *sys;
		//a time var
		ttime stime;
	
		// Call the mean menù, it tell to shell what to do.
		staterec = Menu(inf);

		// If the menù answered 0 the program initialize the system as new
		if (staterec == 0)
			sys = InitSystem(inf, Stype);
	
		//update this
		stime = sys->stime;
	
		// The simulation loop (infinite)
		for ( ; ; ) {
		
			// call the output system accordingly to vmode
			if (inf -> vmode == 0) {
				OPSo (sys, inf);
			}
			
			// call the instruction parser
			stime = Parser(sys->Stype, sys, inf, 's');
			
			// call the phisic motor how many times as Parser asks
			do {
				Pmotor(sys, inf);
				if(GetBiggerStime(&stime, &sys->stime) == 1)
					break;
				if(GetBiggerStime(&stime, &sys->stime) == 2)
					break;
			}
			while(1);
		}

		return;
	}
