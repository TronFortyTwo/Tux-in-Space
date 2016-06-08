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
 * 		- jump
 * 		- Create
 * 
 * 
 */

/**
 * The main function
 * of the parser
 */
	ttime Parser(tStype *Stype, tsys *sys, tinf *inf, char tag) {
		
		// what is scanned
		char input[COMMANDLENGHT+1];
		//the time we want
		ttime t = sys->stime;
		
		// Now for every possible command call the correct command's function or simply do it if is short.
		// when you write a new command, you must add the corrispondent if and add it
		for ( ; ; ) {
			scanf("%s", input);
			// continue
			if (strcmp("continue", input) == 0)
				break;
			//jump
			else if (strcmp("jump", input) == 0) {
				t = Jump(&sys->stime, inf, &sys->precision);
				break;
			}
			// change
			else if (strcmp("create", input) == 0) {
				Create(Stype, sys, inf);
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

	return t;
	}
	
	/**
	 * The Reask function. Reask the input
	 * Retrun 0 if the user want to rewrite a command, 1 if not
	 * 
	 */
	int Reask(tinf *inf, char *command){
		// the answer of the user
		char buffer[BUFFERSIZE];
		strcpy(buffer, "Sorry. But the command ");
		strcat(buffer, command);
		strcat(buffer, " that you wrote is unknow. Do you want to write another command? [y/n]");
		OPSE(inf, buffer, 0, 0);
		
		for(;;){
			// a loop that exit 0 or 1
			scanf("%s", command);
			// if postitive return 0
			if (command[0] == 'y') {
				OPS(inf, "What is your command?", 0, 0);
				return 0;
			}
			// if negative return 1
			else if (command[0] == 'n')
				return 1;
			// if wrong reask
			else
				OPS (inf, "Please answer 'y' or 'n'", 0, 0);
		}
	}
	
	
	/***
	 * The Jump function make the simulation wait for a time 
	 */
	ttime Jump(ttime *now, tinf *inf, long double *precision){
		char buffer[BUFFERSIZE];
		ttime t;
		strcpy(buffer, "JUMP\n\nInsert the information about the moment you want to jump\n<year> <day> <hour> <minute> <second> <millisecond>\nThe jump will be made whit an error of max %l seconds");
		OPS(inf, buffer, NULL, precision);
		scanf("%d", &t.year);
		scanf("%d", &t.day);
		scanf("%d", &t.hour);
		scanf("%d", &t.min);
		scanf("%d", &t.sec);
		scanf("%d", &t.millisec);
		return t;
	}
	
	
	/***
	 * The create function create a new object
	 */
	
	void Create(tStype *Stype, tsys *sys, tinf *inf) {
		
		//if there isn't any space for a new object resize the object buffer
		if (sys->nactive == sys->nalloc) {
			ResizeObject(Stype, inf, &sys->o, sys->nalloc, sys->nalloc+OBJBUFSIZE);
			sys->nalloc += OBJBUFSIZE;
		}
	
		//initialize the new object
		InitObject(inf, &sys->o[sys->nactive], sys->Stype, 0);
		sys->nactive++;
	
		return;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
