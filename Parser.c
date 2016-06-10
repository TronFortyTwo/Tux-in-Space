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
			if (strcmp("step", input) == 0)
				break;
			// the help
			else if (strcmp("help", input) == 0) {
				OPS(inf, "HELP\n\nYou have to press commands to manage the system. Insert a command to visualize his interface. Some command are:\n-step\n-create\n-jump\n-wait\n\ninsert a command:", NULL, NULL);
				continue;
			}
			//jump
			else if (strcmp("jump", input) == 0) {
				t = Jump(&sys->stime, inf, &sys->precision);
				break;
			}
			//wait
			else if (strcmp("wait", input) == 0) {
				t = Wait(&sys->stime, inf, &sys->precision);
				break;
			}
			// create
			else if (strcmp("create", input) == 0) {
				Create(Stype, sys, inf);
				OPS(inf, "Insert a new command:", NULL, NULL);
				continue;
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
	 * The Wait function make the simulation wait for a while. The user say how much 
	 */
	ttime Wait(ttime *now, tinf *inf, long double *precision){
		ttime t;
		OPS(inf,"WAIT\n\nInsert the information about how much simulation-time you want to wait\n<year> <day> <hour> <minute> <second> <millisecond>\nThe operation will be made whit an error of max %l seconds", NULL, precision);
		scanf("%d", &t.year);
		scanf("%d", &t.day);
		scanf("%d", &t.hour);
		scanf("%d", &t.min);
		scanf("%d", &t.sec);
		scanf("%d", &t.millisec);
		t.millisec += now->millisec;
		t.sec += now->sec;
		t.min += now->min;
		t.hour += now->hour;
		t.day += now->day;
		t.year += now->year;
		UpdateTime(&t);
		return t;
	}
	
	/***
	 * The Jump function make the simulation jump to a determined time 
	 */
	ttime Jump(ttime *now, tinf *inf, long double *precision){
		//the time the user would to go
		ttime t;
		OPS(inf, "JUMP\n\nInsert the information about the moment you want to jump\n<year> <day> <hour> <minute> <second> <millisecond>\nThe jump will be made whit an error of max %l seconds" , NULL, precision);
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
		if (sys->nactive == sys->nalloc)
			ExtendObjBuf(sys, inf);
	
		//initialize the new object
		InitObject(inf, &sys->o[sys->nactive], sys->Stype, 0);
		sys->nactive++;
	
		return;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
