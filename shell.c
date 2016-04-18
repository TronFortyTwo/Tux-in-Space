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
	
	int Shell (tsys *sys, tinf *inf);
	
	
	int Shell (tsys *sys, tinf *inf) {

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
			Rmotor(sys, inf, 0, "What is the name of this new system? [no spaces] [max %i characters]", comm, 0, 0);
			scanf("%s", sys->name);
			fflush(stdin);

			// Ask the user how many object there are in the system. the loop control that the value put don't put in overflow the stack
			comm[0]=NUMOGG;
			Rmotor(sys, inf, 0, "do you want to configure some object now?\nDigit the number of object you want to set up now\n\n (you could add, remove and modify objects in the system later, in runtime)", 0, 0, 0);
			scanf("%d", &sys->active[NUMOGG]);
			fflush(stdin);
			for (; ;) {
				Rmotor (sys, inf, 0, "Attenction! Wrong value! Put another number between 0 and %i", comm, 0, 0);
				scanf("%d", &sys->active[NUMOGG]);
				fflush(stdin);
				if(sys->active[NUMOGG] < NUMOGG)
					if(sys->active[NUMOGG] >= 0)
						break;
			}
			
			// Set all the object's type to 0 whit exeption of a number input of object that must setted to 11
			for (l=0; l != NUMOGG; l++) {
				if (l < sys->active[NUMOGG]) {
					sys->o[l].type = 11;
				}
				else {
					sys->o[l].type = 0;
				}
			}
			
			// update the active array
			UpdateActive(sys);
			
			// Ask the user informations about the objects
			for (l=0; l != sys->active[NUMOGG]; l++) {
				printf("calling Init Object");
				InitObject(inf, &sys->o[l], l+1);
			}
		}
		
		// The simulation loop (infinite)
		for ( ; ; ) {
		
			// call Pmotor
			staterec = Pmotor (sys);
			if (staterec != 0)
				return staterec;
				
			// call the output system accordingly to vmode
			if (inf -> vmode == 0) {
				staterec = Rmotor (sys, inf, 1, " ", 0, 0, 0);
				if (staterec != 0)	
					Rmotor(sys, inf, 0, "OnlyPrintfSystemOutput exited whit %i", &staterec, 0, 0);
			}
			
			// call the instruction parser
			staterec = Parser(sys, inf, 's' );
		}

		return 0;
	}
