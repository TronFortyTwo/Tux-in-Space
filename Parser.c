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
 * This is the instruction's parser. elaborate the input and do what these sentences in this strange human language would say.
 * 
 * 
 */

/**
 * The main function
 * of the parser
 */
	ttime Parser(tsys *sys, tinf *inf) {
		
		// what is scanned
		char input[COMMANDLENGHT+1];
		//the time we want
		ttime t = sys->stime;
		
		// Now for every possible command call the correct command's function or simply do it if is short.
		// when you write a new command, you must add the corrispondent if and add it
		for ( ; ; ) {
			scanf("%s", input);
			// continue
			if (strcmp("step", input) == 0) {
				t.millisec += 1000 * sys->precision;
				UpdateTime(&t);
				break;
			}
			// the help
			else if (strcmp("help", input) == 0) {
				OPS(inf, "HELP\n\nYou have to press commands to manage the system. Insert a command to visualize his interface. Some command are:\n-step\n-create\n-jump\n-wait\n-print\n\ninsert a command:", NULL, NULL);
				continue;
			}
			// jump
			else if (strcmp("jump", input) == 0) {
				t = Jump(&sys->stime, inf, &sys->precision);
				break;
			}
			// info
			else if (strcmp("info", input) == 0) {
				Info(sys, inf);
				continue;
			}
			// print
			else if (strcmp("print", input) == 0) {
				OPSo(sys, inf);
				continue;
			}
			// wait
			else if (strcmp("wait", input) == 0) {
				t = Wait(&sys->stime, inf, &sys->precision);
				break;
			}
			// create
			else if (strcmp("create", input) == 0) {
				Create(sys, inf);
				OPSo(sys, inf);
				continue;
			}
			// save
			else if (strcmp("save", input) == 0) {
				SaveSys(sys, inf);
				continue;
			}
			// wrong command
			else {
				Reask(inf, input);
				continue;
			}
		}

	return t;
	}
	
	/**
	 * The Reask function. Reask the input
	 */
	void Reask(tinf *inf, char *command){
		char buffer[BUFFERSIZE];
		strcpy(buffer, "Sorry. But the command ");
		strcat(buffer, command);
		strcat(buffer, " that you wrote is unknow. Write another command:");
		OPSE(inf, buffer, 0, 0);	
		return;
	}
	
	/***
	 * Shows functions
	 */
	void Info(tsys *sys, tinf *inf) {
	
		char buffer[BUFFERSIZE];
		tobj *obj;
		long double c[8];

		strcpy(buffer, "INFO\n\nSystem ");
		strcat(buffer, sys->name);
		strcat(buffer, " whit %i object\n\nOf which object do you want informations? press 0 to quit");
		OPS(inf, buffer, &sys->nactive, NULL);
		scanf("%s", buffer);
		if(strcmp(buffer, "0") == 0){
			OPS(inf, "Insert a new command", NULL, NULL);
			return;
		}
		obj = SearchObject(sys, buffer);
		if(obj == NULL){
			OPS(inf, "INFO\n\nno object whit this name is been found. press a button to continue", NULL, NULL);
			scanf("%s", buffer);
			return;
		}	
		strcpy (buffer, "INFO object ");
		strcat (buffer, obj->name);
		strcat (buffer, "\n\ntype: ");
		strcat (buffer, obj->type->name);
		strcat (buffer, "\n\nmass: %l\n\nradius: %l\n\nx: %l\n\ny: %l\n\nz: %l\n\nvelocity in x: %l\n\nvelocity in y: %l\n\nvelocity in z: %l\n\nInsert a new command:");
		c[0] = obj->mass;
		c[1] = obj->radius;
		c[2] = obj->x;
		c[3] = obj->y;
		c[4] = obj->z;
		c[5] = obj->velx;
		c[6] = obj->vely; 
		c[7] = obj->velz; 
		OPS(inf, buffer, NULL, c);
		scanf("%s", buffer);
		return;
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
	
	void Create(tsys *sys, tinf *inf) {
		
		//if there isn't any space for a new object resize the object buffer
		if (sys->nactive == sys->nalloc)
			ExtendObjBuf(sys, inf);
	
		//initialize the new object
		InitObject(inf, &sys->o[sys->nactive], sys->Stype, 0);
		sys->nactive++;

		return;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
