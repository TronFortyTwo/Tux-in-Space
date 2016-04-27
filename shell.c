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
	
		// variable for communicate whit other functions
		int comm[2];
	
		// counter
		int l = 0;

		// Call the mean menù, it tell to shell what to do.
		staterec = Menu(inf);

		// If the menù tell 0 the program initialize obj
		if (staterec == 0) {
			
			// Ask the name of the new system
			comm[0]=NAMELUN-1;
			OPS (inf, "What is the name of this new system? [no spaces] [max %i characters]", comm, 0);
			scanf("%s", sys->name);
			fflush(stdin);

			// Ask the user how many object there are in the system. the loop control that the value put don't put in overflow the stack
			comm[0]=NUMOGG;
			OPS(inf, "do you want to configure some object of the system now?\nDigit the number of object you want to set up now\n\n (you could add, remove and modify objects in the system later, in runtime)", 0, 0);
			SafeIScan(inf, &sys->nactive);
			for (; ;) {
				if(sys->nactive < NUMOGG)
					if(sys->nactive >= 0)
						break;
				OPS (inf, "Attenction! Wrong value! Put another number between 0 and %i", comm, 0);
				SafeIScan(inf, &sys->nactive);
			}
			
			// Set all the object's type to 0 whit exeption of a number input of object that must setted to 11
			for (l=0; l != NUMOGG; l++) {
				if (l < sys->nactive) {
					strcpy(sys->o[l].type, "Not_initialized");
				}
				else {
					strcpy(sys->o[l].type, "Void");
				}
			}
			
			// Update the active list
			UpdateActive(sys); 
			
			
			// Initialize some object
			for (l=0; l!=sys->nactive; l++) {
				InitObject(inf, &sys->o[l], sys->Stype, l+1);
			}
		}
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
