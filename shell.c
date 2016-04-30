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



 * Questa sarà il guscio di ogni motore che amministrerà le cose e
 * comunicherà coll'esterno
 * This is the shell that connect the engines and the user
 * 
 *	Structure of Shell:
 *
 *	1)Receive basic instruction from Main
 *	--------------------------------------------elaboration
 *	2)Converse whit the phisic motor (Pmotor)
 *	--------------------------------------------elaboration
 *	3)Converse whit the graphic motor (Rmotor)
 *	--------------------------------------------elaboration
 *	4)Converse whit the user
 *	--------------------------------------------elaboration
 *	5)Goto 2 or goto 6
 *	
 *  6)Retrun to main
 * 
 * 
 */
	
	void Shell (tsys *sys, tinf *inf);
	
	
	void Shell (tsys *sys, tinf *inf) {

		// Retruning value from the function. 0 if all is good
		int staterec;
	
		// Call the mean menù, it tell to shell what to do.
		staterec = Menu(inf);

		// If the menù answered 0 the program initialize the system as new
		if (staterec == 0)
			InitSystem(sys, inf);
	
		// The simulation loop (infinite)
		for ( ; ; ) {
		
			// call the output system accordingly to vmode
			if (inf -> vmode == 0) {
				OPSo (sys, inf);
			}
			
			// call the instruction parser
			Parser(sys, inf, 's' );
			
			// call the phisic motor
			Pmotor(sys);
				
		}

		return;
	}
