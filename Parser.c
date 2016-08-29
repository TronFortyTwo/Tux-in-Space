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
 */

/**
 * The main function
 * of the parser
 */
	ttime Parser(tsys *sys) {
		DebugPrint("parser");
		
		// what is scanned
		char input[COMMANDLENGHT+1];
		// the time we want (simulation)
		ttime t = sys->stime;
		
		// Now for every possible command call the correct command's function or simply do it if is short.
		// when you write a new command, you must add the corrispondent if and add it
		scanf("%s", input);
		// continue
		if ((!strcmp("step", input)) || (!strcmp("s", input))) {
			t.millisec = t.millisec + (1000 * sys->precision);
			UpdateTime(&t);
		}
		// help
		else if ((!strcmp("help", input)) || (!strcmp("h", input))) {
			OPS("HELP\n\nYou have to press commands to manage the system. Insert a command to visualize his interface. Some command are:\n-step (s)\n-create (c)\n-jump (j)\n-wait (w)\n-info\n-settings\n-save\n-distance\n-quit\n-delete\n\nPress something to continue...", NULL);
			scanf("%s", input);
		}
		// jump
		else if ((!strcmp("jump", input)) || (!strcmp("j", input)))
			t = Jump(&sys->stime, &sys->precision);
			
		// info
		else if (!strcmp("info", input))
			Info(sys);
		// wait
		else if ((!strcmp("wait", input)) || (!strcmp("w", input)))
			t = Wait(&sys->stime, &sys->precision);
		// create
		else if (!(strcmp("create", input)) || (!strcmp("c", input)))
			Create(sys);
		// quit / exit
		else if (!(strcmp("quit", input)) || (!strcmp("exit", input)))
			t = Quit(sys, &sys->stime);
		// save
		else if (!strcmp("save", input))
			SaveSys(sys);
		//distance
		else if (!strcmp("distance", input))
			DistanceCommand(sys);
		// delete an object
		else if (!(strcmp("delete", input)) || (!strcmp("remove", input)))
			DeleteObject(sys);
		// settings
		else if (!(strcmp("settings", input)) || (!strcmp("configuration", input))){
			Setting();
		}
		// wrong command
		else {
			Reask(input);
			scanf("%s", input);
		}
		// Print a loading message
		OPS("Loading...", NULL);
		 
		return t;
	}
	
	/**
	 * The Reask function. Reask the input
	 */
	void Reask(char *command){
		void *var = command;
		OPSE("Sorry. But the command %s that you wrote is unknow. Press something to continue:", &var);
		return;
	}
	
	/***
	 * This command calculate and show the distance between two objects
	 */
	void DistanceCommand(tsys *sys){
		DebugPrint("distancecommand");
		char name[NAMELUN];
		tobj *o;
		tobj *u;
		long double distance[2];
		void *var[2];
		
		//ask which two object
		OPS("DISTANCE\n\nCalculate the distance between two objects.\n\n&t2Insert the name of the first object:", NULL);
		ScanString(name);
		o = SearchObject(sys, name);
		if(o == NULL) {
			OPSE("There isn't any object whit that name!\n\nInsert a new command", NULL);
			return;
		}
		OPS("DISTANCE\n\nCalculate the distance between two objects.\n\n&t2Insert the name of the second object:", NULL);
		ScanString(name);
		u = SearchObject(sys, name);
		if(u == NULL) {
			OPSE("There isn't any object whit that name!\n\nInsert a new command", NULL);
			return;
		}
		distance[0] = Pitagora(o->x-u->x, o->y-u->y, o->z-u->z);
		distance[1] = Pitagora(o->x+o->velx-(u->x+u->velx), o->y+o->vely-(u->y+u->vely), o->z+o->velz-(u->z+u->velz)) - distance[0];
		var[0] = distance;
		var[1] = &distance[1];
		OPS("DISTANCE\n\nThe distance between the two object is:\n&td%l Km\n&t0And, if the two object take constant velocity, the distance will change at a velocity of\n&td%l km/s\n\n&t0Press something to continue...", var);
		scanf("%s", name);
		
		return;
	}
	
	/***
	 * This function prepare the parser to quit
	 */
	ttime Quit (tsys *sys, ttime *now){
		DebugPrint("quit");
		
		ttime t;	 	//this is the escape time
		char input;		
		//ask for confirm to quit
		OPS("CSPACE\n\nAre you sure you want to quit? [y/n]\nOr you want to save before go? [s]", NULL);
		scanf(" %c", &input);
		//if doesn't want to quit return now
		if (input == 'n')
			return *now;
		if (input == 's')
			SaveSys(sys);
		else if (input != 'y') {
			OPS("Unrecognized input! please insert y/n/s\n\ninsert a new command:", NULL);
			return *now;
		}
		// now we prepare the quit event
		t = *now;
		t.year = QUITSIGNAL;		// <------ THIS IS THE SIGNAL THAT WE WANT TO QUIT
		return t;
	}
	
	/***
	 * This function delete an object
	 */
	void DeleteObject(tsys *sys) {
		DebugPrint("deleteobject");
		
		TNAME name;			//the name of the object
		tobj *obj;			//the pointer to the object
		
		//ask the user for the name
		OPS("Which object do you want do delete?\n\n&t1Press 'n' to quit", NULL);
		ScanString(name);
		if (!strcmp(name, "n")) {
			OPS("Insert a new command", NULL);
			return;
		}
		
		//search the object
		obj = SearchObject(sys, name);
		if (obj == NULL) {	//if there isn't any object whit that name
			OPSE("There isn't any object whit that name!\n\nInsert a new command", NULL);
			return;
		}
		
		//delete the object moving the last object in the position of this object, and, if needed resize the object buffer
		*obj = sys->o[sys->nactive-1];		
		sys->nactive--;
		if (sys->nalloc - sys->nactive >= OBJBUFSIZE)
			ReduceObjBuf(sys);
		
		return;
	}
	
	/***
	 * Info about the system and the objects
	 */
	void Info(tsys *sys) {
		DebugPrint("info");
		
		tobj *obj;			// The object to describe
		void *var[13];		// The variables to give to OPS
		TNAME input;

		var[0] = sys->name;
		var[1] = &sys->nactive;
		// Generic information about the system
		OPS("INFO\n\nSystem %s whit %i objects\n\nOf which object do you want informations? press 'n' to not display any object information", var);
		ScanString(input);
		if(strcmp(input, "n") == 0){
			OPS("Insert a new command", NULL);
			return;
		}
		// Informations about a precise object
		obj = SearchObject(sys, input);
		if(obj == NULL){
			OPSE("No object whit this name is been found. press a button to continue", NULL);
			sgetchar();
			return;
		}	
		var[0] = obj->name;
		var[1] = obj->type->name;
		var[2] = &obj->color.red;
		var[3] = &obj->color.green;
		var[4] = &obj->color.blue;
		var[5] = &obj->mass;
		var[6] = &obj->radius;
		var[7] = &obj->x;
		var[8] = &obj->y;
		var[9] = &obj->z;
		var[10] = &obj->velx;
		var[11] = &obj->vely; 
		var[12] = &obj->velz; 
		OPS("INFO %s\n%f-type: %s\n%f-color: &td \nred: %i\ngreen: %i\nblue: %i &t0 \n%f-mass: %l\n%f-radius: %l\n%f-x: %l\n\ny: %l\n\nz: %l\n%f-velocity in x: %l\n\nvelocity in y: %l\n\nvelocity in z: %l\n%f-\n\nPress somthing to continue...", var);
		sgetchar();
		return;
	}
	
	
	/***
	 * The Wait function make the simulation wait for a while. The user say how much 
	 */
	ttime Wait(ttime *now, long double *precision) {
		DebugPrint("wait");
		
		ttime t;
		
		OPS("WAIT\n\nInsert the information about how much simulation-time you want to wait\n<year> <day> <hour> <minute> <second> <millisecond>\nThe operation will be made whit an error of max %l seconds", (void **)&precision);
		scanf("%ld", &t.year);
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
	ttime Jump(ttime *now,long double *precision) {
		DebugPrint("jump");
		
		ttime t;
		
		OPS("JUMP\n\nInsert the information about the moment you want to jump\n<year> <day> <hour> <minute> <second> <millisecond>\nThe jump will be made whit an error of max %l seconds" , (void **)&precision);
		scanf("%ld", &t.year);
		scanf("%d", &t.day);
		scanf("%d", &t.hour);
		scanf("%d", &t.min);
		scanf("%d", &t.sec);
		scanf("%d", &t.millisec);
		UpdateTime(&t);
		return t;
	}
	
	
	/***
	 * The create function create a new object
	 */
	
	void Create(tsys *sys) {
		DebugPrint("Create");
		
		// if there isn't any space for a new object resize the object buffer
		if (sys->nactive == sys->nalloc)
			ExtendObjBuf(sys);
	
		// initialize the new object
		InitObject(&sys->o[sys->nactive], sys->Stype);
		sys->nactive++;

		return;
	}
