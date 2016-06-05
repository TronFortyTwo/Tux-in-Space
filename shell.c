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
 *	--------------------------------------------elaboration
 *	2)Converse whit the phisic motor (Pmotor)
 *	--------------------------------------------elaboration
 *	3)Converse whit the user via OPSo or others
 *	--------------------------------------------elaboration
 *	4)Converse whit the user
 *	--------------------------------------------elaboration
 *	5)Goto 2 or goto 6
 *	
 *  6)Return to main
 * 
 * 
 */
	
	void Shell (tinf *inf, tStype *Stype) {

		// Retruning value from the function
		int staterec;
		
		//the pointer to a system
		tsys *sys;
	
		// Call the mean menù, it tell to shell what to do.
		staterec = Menu(inf);

		// If the menù answered 0 the program initialize the system as new
		if (staterec == 0)
			sys = InitSystem(inf, Stype);
	
		// The simulation loop (infinite)
		for ( ; ; ) {
		
			// call the output system accordingly to vmode
			if (inf -> vmode == 0) {
				OPSo (sys, inf);
			}
			
			// call the instruction parser
			Parser(sys->Stype, sys, inf, 's');
			
			// call the phisic motor
			Pmotor(sys);
				
		}

		return;
	}
