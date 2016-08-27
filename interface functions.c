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
 * HERE we have functions that help whit the interface system of the program 
 * 
 */
 
/***
 * 	The function InitObject initialize a new object and ask information about it
 * 
 * 	n is the number of the object to initialize, if in a list
 * 	
 */
	void InitObject (tinf *inf, tobj *obj, tStype *Stype) {
		DebugPrint(inf, "InitObject");
		
		//variables
		void *var[18];
		int input;
		int temp;
		char comment[64];			// This is a buffer that contein comment of what is just been done
		char mass_irregularity[3];	// assume the value IRREGULARITY if the mass is out of range
		char color_irregularity[3];	// assume the value IRREGULARITY if the color is out of range
		
		// Initialize the object whit blank attributes
		strcpy(obj->name, "Chose a name for your new object");
		obj->type = typeSearchName(inf, Stype, "Choose a type");
		obj->mass = 0;
		obj->radius = 0;
		obj->color.blue = 0;
		obj->color.red = 0;
		obj->color.green = 0;
		obj->x = 0;
		obj->y = 0;
		obj->z = 0;
		obj->velx = 0;
		obj->vely = 0;
		obj->velz = 0;
		
		// the loop
		strcpy(comment, " ");
		strcpy(mass_irregularity, " ");
		strcpy(color_irregularity, " ");
		
		do{
			// Print and scan the desire of the user
			var[0] = obj->name;
			var[1] = obj->type->name;
			var[2] = obj->type->description;
			var[3] = & obj->color.red;
			var[4] = color_irregularity;
			var[5] = & obj->color.green;
			var[6] = & obj->color.blue;
			var[7] = & obj->mass;
			var[8] = mass_irregularity;
			var[9] = & obj->radius;
			var[10] = & obj->x;
			var[11] = & obj->y;
			var[12] = & obj->z;
			var[13] = & obj->velx;
			var[14] = & obj->vely;
			var[15] = & obj->velz;
			var[16] = comment;
			OPS(inf, "CREATE A NEW OBJECT\n\n%f-1) name:         %s\n%f-2) type:         %s\n&ti7%s&t0\n%f-3) color:        red: %i   %s&ti7\ngreen: %i\nblue: %i&t0\n%f-4) mass:         %l   %s\n%f-5) radius:       %l\n%f-6) coordinates:  x: %l&ti7\ny: %l\nz: %l&t0\n%f-7) velocity:     x: %l&ti7\ny: %l\nz: %l&t0\n%f-8) LOAD  the object from a file\n%f-9) SAVE  this object in a file\n%f-10) DONE\n\n%s", var);
			SafeIScan(inf, &input);
		
			// Name
			if(input == 1) {
				temp = NAMELUN-1;
				var[0] = &temp;
				OPS (inf, "INITIALIZE A NEW OBJECT\n\nInsert the name of the new object:\n&tdThe name must be of maximum %i character", var);
				ScanString(obj->name);
				strcpy(comment, "\nNew name assigned succefully!");
			}
			// Type
			else if(input == 2) {
				obj->type = TypeBrowser(inf, Stype, "Chose a new type for your new object");
				strcpy(comment, "\nNew type assigned succefully!");
			}
			// Color
			else if(input == 3) {
				obj->color = ScanColor(inf, obj->type->color_min, obj->type->color_max);
				strcpy(comment, "\nNew color assigned succefully!");
			}
			// Mass
			else if(input == 4) {
				var[0] = & obj->type->mass_min;
				if (obj->type->mass_max == -1)
					OPS (inf, "CREATE A NEW OBJECT\n\nInsert the mass of the new object: (t)\n&tdThe mass's legal values start from %l", var);
				else{
					var[1] = & obj->type->mass_max;
					OPS (inf, "CREATE A NEW OBJECT\n\nInsert the mass of the new object: (t)\n&tdThe mass's legal values are between %l and %l", var);
				}
				scanf("%Lf", & obj->mass);
				strcpy(comment, "\nNew mass assigned succefully!");
			}
			// Radius
			else if(input == 5) {
				OPS (inf, "CREATE A NEW OBJECT\n\nInsert the radius of the new object: (Km)", var);
				scanf("%Lf", &obj->radius);
				strcpy(comment, "\nNew radius assigned succefully!");
			}
			// Coordiates
			else if(input == 6) {
				OPS (inf, "CREATE A NEW OBJECT\n\nInsert the position in the x axis of the new object: (Km)", var);
				scanf("%Lf", &obj->x);
				OPS (inf, "CREATE A NEW OBJECT\n\nInsert the position in the y axis of the new object: (Km)", var);
				scanf("%Lf", &obj->y);
				OPS (inf, "CREATE A NEW OBJECT\n\nInsert the position in the z axis of the new object: (Km)", var);
				scanf("%Lf", &obj->z);
				strcpy(comment, "\nNew coordinates assigned succefully!");
			}
			// Velocity
			else if(input == 7) {
				OPS (inf, "CREATE A NEW OBJECT\n\nInsert the velocity in the x axis of the new object: (Km/s)", var);
				scanf("%Lf", &obj->velx);
				OPS (inf, "CREATE A NEW OBJECT\n\nInsert the velocity in the y axis of the new object: (Km/s)", var);
				scanf("%Lf", &obj->vely);
				OPS (inf, "CREATE A NEW OBJECT\n\nInsert the velocity in the z axis of the new object: (Km/s)", var);
				scanf("%Lf", &obj->velz);
				strcpy(comment, "\nNew velocity assigned succefully!");
			}
			// LOAD
			else if(input == 8) {
				temp = LoadObject(inf, obj, Stype, obj->name);
				strcpy(comment, "\n");
				if (temp == GOODSIGNAL)									//load success
					strcat(comment, "New object loaded succefully!");
				else { 													//load failed
					strcat(comment, "Can't load the object!");
					if (temp == FILE_ERR_SIG)
						strcat(comment, "No object whit that name found!");
					else 		//CORRUPTED_SIG
						strcat(comment, "File corrupted or outdated!");
				}
			}
			// SAVE
			else if(input == 9) {
				SaveObject(inf, obj);
				strcpy(comment, "\nNew object saved succefully!");
			}
			// EXIT. Always added this. In case of exit however this isn't printed
			else if(input == 10)
				strcpy(comment, "\nCannot exit! Fix irregularity first");
			
			// check for IRREGALARITY
			// irregularity: MASS
			if ((obj->mass > obj->type->mass_min) && ((obj->mass < obj->type->mass_max) || (obj->type->mass_max == -1))) {
				strcpy(mass_irregularity, "  ");
			}
			else {
				strcpy(mass_irregularity, IRREGULARITY);
				strcat(comment, "\n");
				strcat(comment, IRREGULARITY);
				strcat(comment, ": mass out of range");
			}
			// irregularity: COLOR
			if (ColorRangeCheck(obj->color, obj->type->color_min, obj->type->color_max) == GOODSIGNAL)
				strcpy(color_irregularity, " ");
			else {
				strcpy(color_irregularity, IRREGULARITY);
				strcat(comment, "\n");
				strcat(comment, IRREGULARITY);
				strcat(comment, ": color out of range");
			}
			// irregularity: TYPE
			if (obj->type == typeSearchName(inf, Stype, "Choose a type")) {
				strcat(comment, "\n");
				strcat(comment, IRREGULARITY);
				strcat(comment, ": Choose a type!");
			}
			// EXIT
			if(input == 10) {
				if (!((strcmp(mass_irregularity, IRREGULARITY) == 0) || (strcmp(color_irregularity, IRREGULARITY) == 0) || (obj->type == typeSearchName(inf, Stype, "Choose a type")) ) )
					break;
			}
		}
		while(1);
		
		return;
	}

/***
 * InitSystem is a function that initialize a new system
 */
	tsys *InitSystem (tinf *inf, tStype *Stype) {
		DebugPrint(inf, "Initsystem");
		
		// var to give to OPS and counter
		void *var;
		int c;
		// the system to create
		tsys *sys = (tsys *) malloc (sizeof(tsys));
		while (sys == NULL) {
			OPSML(inf, "sys");
			sys = (tsys *) malloc (sizeof(tsys));
		}
		
		// set the type struct pointer
		sys->Stype = Stype;
		// set the system's time
		sys->stime.year = 0;
		sys->stime.hour = 0;
		sys->stime.day = 0;
		sys->stime.min = 0;
		sys->stime.sec = 0;
		sys->stime.millisec = 0;
		
		// set the constant of gravitation. 6.67e-11 (m*m*m)/(Kg*s*s) but whit our units (t, s and Km) is 6.67e-17
		sys->G = 6.67e-17;
		
		// Ask for the name of the new system
		c = NAMELUN-1;
		var = &c;
		OPS (inf, "NEW SYSTEM INITIALIZATION\n\nname of the system:\n&tdThe name can be of a maximum of %i characters", &var);
		scanf("%s", sys->name);
		//ask for the precision
		OPS (inf, "NEW SYSTEM INITIALIZATION\n\nprecision of the simulation:\n&tdIndicate how much the simulation is precise. A big value mean leess precision but lighter hardware use.\nrecommended values: < 2", NULL);
		scanf("%Lf", &sys->precision);
		
		sys->nactive = 0;
		sys->nalloc = 0;
		sys->o = NULL;
	 
	 	return sys;
	}
	
	/**
	 * Load a system from a file
	 * create a new system and return his pointer
	 */
	tsys *LoadSystem(tinf *inf, tStype *Stype) {
		DebugPrint(inf, "loadsystem");
	
		char path[NAMELUN+12];	// the file of the system
		FILE *dest;				// the file of the system
		int i;					// counter
		// the new system. allocated dinamically because is accessed in many other function after the end of this function
		tsys *sys = (tsys *) malloc (sizeof(tsys));
		while(sys == NULL){
			OPSML(inf, "InitSystem");
			sys = (tsys *) malloc (sizeof(tsys));
		}
		// ask which system
		OPS(inf, "LOAD SYSTEM\n\nWhat is the name of the system you want to load?", NULL);
		ScanString(sys->name);
		// write the path
		strcpy (path, SYSTEM_PATH);
		strcat (path, sys->name);
		strcat (path, ".sys");
		// open the file
		dest = fopen(path, "r");
		if (dest == NULL) {
			OPSE(inf, "A system whit that name doesn't exist! Type something to continue and return to the menù", NULL);
			getchar();
			free(sys);
			return NULL;
		}
		// scanf system's informations
		fscanf (dest, "%Lf\n%ld\n%Lf\n", &sys->precision, &sys->nactive, &sys->G);
		fscanf (dest, "%ld\n%d\n%d\n%d\n%d\n%d\n", &sys->stime.year, &sys->stime.day, &sys->stime.hour, &sys->stime.min, &sys->stime.sec, &sys->stime.millisec);
		// alloc memory
		sys->nalloc = 0;
		while (sys->nalloc < sys->nactive)
			sys->nalloc += OBJBUFSIZE;
		sys->o = (tobj *) malloc (sizeof(tobj[sys->nalloc]));
		while (sys->o == NULL) {
			OPSML(inf, "LoadSystem");
			sys->o = (tobj *) malloc (sizeof(tobj[sys->nalloc]));
		}
		// fscanf for objects datas
		for(i=0; i!=sys->nactive; i++) {
			if(ReadObjectComplete(inf, dest, &sys->o[i], Stype) == CORRUPTED_SIG) {
				DebugPrint(inf, "(!) the system to load seem corrupted or outdated!");
				DebugPrint(inf, sys->o[i].type->name);
			}
		}
		fclose(dest);
		sys->Stype = Stype;
		return sys;
	}
