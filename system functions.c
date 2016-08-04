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
 * HERE we have functions that help whit the system of the program 
 * 
 */

/***
 * 	This function InitObject initialize a new object and ask information about it
 * 
 * 	n is the number of the object to initialize, if in a list
 * 	
 * 	NOTE:
 * 	-this function is a bit :| Poker Face
 * 	-this is a recursive function
 */
	void InitObject (tinf *inf, tobj *obj, tStype *Stype, int n) {
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
		obj->type = typeSearchName(inf, Stype, "Chose a type");
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
				OPS (inf, "INITIALIZE A NEW OBJECT\n\nInsert the name of the new object:\n&tdThe name must be of maximum %i character and can't contein spaces", var);
				scanf("%s", obj->name);
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
			// COMMAND UNRECOGNIZED
			else if(input == 10)
				strcpy(comment, "\nCannot exit! fix irregularity first");
			
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
 * The load object function load from a file the information about a object
 */
	int LoadObject(tinf *inf, tobj *obj, tStype *Stype, char *name) {
		DebugPrint(inf, "loadobject");
		
		FILE *ofile;				// (the) o(bject) file
		char buffer [NAMELUN + 15];
		
		strcpy(buffer, "Objects/");
		strcat(buffer, name);
		strcat(buffer, ".object");
		
		ofile = fopen(buffer, "r");
		while(ofile == NULL)
			return FILE_ERR_SIG;
		
		// Read type, color, radius and mass
		ReadObject(inf, ofile, obj, Stype);
		
		//close the file and exit
		fclose(ofile);
		
		return GOODSIGNAL;
	}
 
/***
 * The SaveObject function save a object in a file
 */
	void SaveObject(tinf *inf, tobj *obj) {
	
		DebugPrint(inf, "SaveObject");
	
		//the path where the object must be saved, an input variable and the destination file pointer
		char path[NAMELUN+16];
		char input[2];
		FILE *dest;
		
		//Write the path
		strcpy(path, "Objects/");
		strcat(path, obj->name);
		strcat(path, ".object");
		
		//control that the file isn't alredy existent
		dest = fopen(path, "r");
		if(dest != NULL) {
			fclose(dest);
			OPS(inf, "While saving: The object you want to save alredy exist.\nDo you want to delete the previous object and save this? [n = no | something else = y]", NULL);
			scanf("%s", input);
			if(strcmp(input, "n") == 0)
				return;
		}
	
		// Write the object
		dest = fopen(path, "w");
		WriteObject(dest, obj);
		fclose(dest);
	
		return;	
	}

/***
 * InitSystem is a function that initialize a new system
 */
	tsys *InitSystem (tinf *inf, tStype *Stype) {
		
		DebugPrint(inf, "Initsystem");
		
		// var to give to OPS and counter
		int c;
		void *var;
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
		
		//set the constant of gravitation. 6.67e-11 (m*m*m)/(Kg*s*s) but whit our units (t, s and Km) is 6.67e-17
		sys->G = 6.67e-17;
		
		// Ask for the name of the new system
		c = NAMELUN-1;
		var = &c;
		OPS (inf, "NEW SYSTEM INITIALIZATION\n\nname of the system:\n&tdIsn't allowed any spaces and can be of a maximum of %i characters", &var);
		scanf("%s", sys->name);
		//ask for the precision
		OPS (inf, "NEW SYSTEM INITIALIZATION\n\nprecision of the simulation:\n&tdIndicate how much the simulation is precise. A big value mean leess precision but lighter hardware use.\nrecommended values: < 2", NULL);
		scanf("%Lf", &sys->precision);
		
		sys->nactive = 0;
		sys->nalloc = 0;
		sys->o = NULL;
	 
	 	return sys;
	}
	
	
	/***
	 * This function reduce the object buffer size
	 */
	 
	void ReduceObjBuf(tsys *sys, tinf *inf) {
		DebugPrint(inf, "reduceobjbuf");
		
		tobj *newo;		//(new o)bject buffer
		int c;			//(c)ounter
		// create a new buffer whit less objects
		newo = (tobj *) malloc (sizeof(tobj) * (sys->nalloc-OBJBUFSIZE));
		while (newo == NULL) {
			OPSML(inf, "ReduceObjBuf");
			newo = (tobj *) malloc (sizeof(tobj[sys->nalloc-OBJBUFSIZE]));
		}
		// update counter
		sys->nalloc -= OBJBUFSIZE;
		// copy what is stored in the old buffer in the new buffer
		for(c=0; c!= sys->nalloc; c++)
			newo[c] = sys->o[c];
		// delete the old buffer
		free(sys->o);
		// point sys->o at the new buffer
		sys->o = newo;
		// if can be reduced more, recall itself
		if(sys->nalloc - sys->nactive >= OBJBUFSIZE)
			ReduceObjBuf(sys, inf);
		// if the buffer is empty, set the pointer to NULL
		if(sys->nalloc == 0)
			sys->o = NULL;
		//exit
		free(newo);
		return;
	}
	
	/***
	 * This function make the object buffer size bigger
	 */
	void ExtendObjBuf(tsys *sys, tinf *inf){
		DebugPrint(inf, "extendobjbuf");
		
		tobj *newo;		//(new o)bject buffer
		int c;			//(c)ounter
		
		// create a new buffer whit more objects
		newo = (tobj *) malloc (sizeof(tobj[sys->nalloc+OBJBUFSIZE]));
		while (newo == NULL) {
			OPSML(inf, "ExtendObjBuf");
			newo = (tobj *) malloc (sizeof(tobj[sys->nalloc+OBJBUFSIZE]));
		}
		// copy what is stored in the old buffer in the new buffer
		for (c=0; c != sys->nalloc; c++)
			newo[c] = sys->o[c];
		// update counter
		sys->nalloc += OBJBUFSIZE;
		// if the old buffer isn't empty, delete the old buffer
		if(sys->o != NULL)
			free(sys->o);
		// point sys->o at the new buffer
		sys->o = newo;
		return;
	}
	
	/***
	 * Save a system in the directory Systems/
	 */
	void SaveSys(tsys *sys, tinf *inf){
		DebugPrint(inf, "savesys");
		
		//the path where the system must be saved, an input variable and the destination file pointer
		char path[NAMELUN+13];
		char input[2];
		FILE *dest;
		// counter
		int i;
		
		//Write the path
		strcpy(path, "Systems/");
		strcat(path, sys->name);
		strcat(path, ".sys");
		
		//control that the file isn't alredy existent
		dest = fopen(path, "r");
		if(dest != NULL) {
			fclose(dest);
			OPS(inf, "While saving: The system you want to save alredy exist.\nDo you want to delete the previous system and save this? [n = no | something else = y]", NULL);
			scanf("%s", input);
			if(strcmp(input, "n") == 0)
				return;
		}
	
		// Write the object
		dest = fopen (path, "w");
		// Write information about the system
		fprintf (dest, "%.128Lf\n%ld\n%.128Lf\n",  sys->precision, sys->nactive, sys->G);
		fprintf (dest, "%ld\n%d\n%d\n%d\n%d\n%d\n", sys->stime.year, sys->stime.day, sys->stime.hour, sys->stime.min, sys->stime.sec, sys->stime.millisec);	//the time
		// write the system's object's datas
		for(i=0; i!=sys->nactive; i++)
			WriteObjectComplete(dest, &sys->o[i]);
		fclose(dest);
	
		OPS(inf, "SYSTEM SAVED WHIT SUCCESS!\n\nPress something to continue", NULL);
		scanf("%s", input);		
	
		return;
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
		scanf("%s", sys->name);
		// write the path
		strcpy (path, "Systems/");
		strcat (path, sys->name);
		strcat (path, ".sys");
		// open the file
		dest = fopen(path, "r");
		if (dest == NULL) {
			OPSE(inf, "A system whit that name doesn't exist! Type something to continue and return to the menù", NULL);
			scanf("%s", path);
			free(sys);
			return NULL;
		}
		// scanf system's informations
		fscanf (dest, "%Lf\n%ld\n%Lf\n", &sys->precision, &sys->nactive, &sys->G);
		fscanf (dest, "%ld\n%d\n%d\n%d\n%d\n%d\n", &sys->stime.year, &sys->stime.day, &sys->stime.hour, &sys->stime.min, &sys->stime.sec, &sys->stime.millisec);
		// alloc memory
		sys->nalloc = 0;
		while(sys->nalloc < sys->nactive)
			sys->nalloc += OBJBUFSIZE;
		sys->o = (tobj *) malloc (sizeof(tobj[sys->nalloc]));
		while(sys->o == NULL) {
			OPSML(inf, "LoadSystem");
			sys->o = (tobj *) malloc (sizeof(tobj[sys->nalloc]));
		}
		// fscanf for objects datas
		for(i=0; i!=sys->nactive; i++) {
			if(ReadObjectComplete(inf, dest, &sys->o[i], Stype) == CORRUPTED_SIG) {
				DebugPrint(inf, "(!) the system to load seem corrupted!");
				DebugPrint(inf, sys->o[i].type->name);
			}
		}
		fclose(dest);
		sys->Stype = Stype;
		return sys;
	}
	
	
	/***
	 * the function search object search a object in a system whit a name and return his pointer or NULL if there isn't any object whit that name
	 */
	tobj *SearchObject(tsys *sys, char *name) {
		int i;
		for (i=0; i != sys->nactive; i++)
			if(strcmp(sys->o[i].name, name) == 0)
				return &sys->o[i];
		return NULL;
	}
	
	/***
	 * OBJECT I/O       (READ/WRITE)
	 * WriteObject write in the stream given the object.
	 * WriteObjectComplete write in the stream given the object whit coordinates and velocity
	 * ReadObject read in the stream given the object.
	 * Read ObjectComplete read in the stream given the object whit coordinates and velocity
	 */
	void WriteObject (FILE *stream, tobj *obj) {
		fprintf(stream, "%s\n%s\n%d\n%d\n%d\n%.128Lf\n%.128Lf", obj->name, obj->type->name, obj->color.red, obj->color.green, obj->color.blue, obj->radius, obj->mass);
		return;
	}
	void WriteObjectComplete (FILE *stream, tobj *obj) {
		fprintf(stream, "%s\n%s\n%d\n%d\n%d\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n", obj->name, obj->type->name, obj->color.red, obj->color.green,obj->color.blue, obj->radius, obj->mass, obj->x, obj->y, obj->z, obj->velx, obj->vely, obj->velz);
		return;
	}
	int ReadObject (tinf *inf, FILE *stream, tobj *obj, tStype *Stype) {
		char type[NAMELUN];
		ScanFString(obj->name, stream);
		ScanFString(type, stream);
		fscanf(stream, "%d\n%d\n%d\n%Lf\n%Lf", &obj->color.red, &obj->color.green, &obj->color.blue, &obj->radius, &obj->mass);
		obj->type = typeSearchName(inf, Stype, type);
		if (obj->type == NULL)
			return CORRUPTED_SIG;
		return GOODSIGNAL;
	}
	int ReadObjectComplete (tinf *inf, FILE *stream, tobj *obj, tStype *Stype) {
		char type[NAMELUN];
		ScanFString(obj->name, stream);
		ScanFString(type, stream);
		fscanf(stream, "%d\n%d\n%d\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n", &obj->color.red, &obj->color.green, &obj->color.blue, &obj->radius, &obj->mass, &obj->x, &obj->y, &obj->z, &obj->velx, &obj->vely, &obj->velz);
		obj->type = typeSearchName(inf, Stype, type);
		if (obj->type == NULL)
			return CORRUPTED_SIG;
		return GOODSIGNAL;
	}
