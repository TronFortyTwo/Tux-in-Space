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
 * This is the instruction's parser. elaborate the input and do what these phrases in this strange human language would say.
 * The parser is smart(or not enought smart) and if you don't write all the word, he equally know what you mean
 * 
 * The parser now work for:
 * 		- shell. in main loop whit only OPS (s)
 * 
 * The parser command now are:
 * 	
 * 		- Continue
 * 		//exit from Parser whitout action. Is a command whitout function
 * 
 * 		- Change
 * 				NameObj
 * 						name
 * 						type
 * 						mass
 * 						x
 * 						y
 * 						z
 * 						fast
 * 							x
 * 							y
 * 							z
 * 				system
 * 						name
 * 						G
 * 						time
 * 						
 * 
 * 
 * 
 */
 
	/** Prototipes: */
	// The main function
	int Parser(tsys *sys, tinf *inf, char tag);
	// functions called only from Parser:
	// Reask reask for the instruction if the instruction is wrong
	int Reask(tinf *inf, char command[]);
	// Change function change system and objects's data
	int Change(tsys *sys);
	

	

/**
 * The main function
 * of the parser
 */
	int Parser(tsys *sys, tinf *inf, char tag) {
		
		// what is scanned
		char input[COMMANDLENGHT];
		
		// Now for every possible command call command call the correct command's function.
		// when you write a new command, you must add the corrispondent if and add it
		
		for ( ; ; ) {
			scanf("%s", input);
			fflush(stdin);
			// continue
			if (strcmp("continue", input) == 0)
				break;
			// change
			else if (strcmp("change", input)) {
				Change(sys);
				break;
			}
			// wrong command
			else {
				if (Reask(inf, input) == 0)
					continue;
				else
					break;
			}
		}

	return 0;
	}
	
	/**
	 * The Reask function. Reask the input
	 * Retrun 0 if the user want to rewrite a command, 1 if not
	 * NOTE:
	 * We don't have the pointer to sys, then we tell to Rmotor that is 0 because the OPS don't use the *sys
	 */
	int Reask(tinf *inf, char command[]){
		// the answer of the user
		char answer[32];
		strcpy(answer, command);
		Rmotor(0, inf, 0, "Sorry. But the word %c that you wrote is wrong. Do you want to write another command? [y/n]", 0, 0, answer);
		
		for(;;){
			// a loop that exit 0 or 1
			scanf("%s", answer);
			fflush(stdin);
			// if postitive return 0
			if (answer[0] == 'y') {
				Rmotor(0, inf, 0, "What is your command?", 0, 0, 0);
				return 0;
			}
			// if negative return 1
			else if (answer[0] == 'n')
				return 1;
			// if wrong reask
			else
				Rmotor(0, inf, 0, "Please answer 'y' or 'n'", 0, 0, 0);
		}
	}
	
	/***
	 * The Change function modifies datas.
	 * see up for sytax.
	 * 
	 */
	 int Change (tsys *sys) {
		
		char command[NAMELUN];
		short *objflag = (short *) malloc (sizeof(short) * (sys->active[NUMOGG]+1) );	// An array of value (0 or 1) that indicate if the object at the position sys->active[] can be the true name. additionaly the last member indicate if is the system to modify
		
		// Scanf the name of what you want to modify
		scanf("%s", command);
		fflush(stdin);
		
		// search in the names of objects and system for the char command
		
		free(objflag);
		
		return 0;
		}
