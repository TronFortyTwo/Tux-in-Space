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
		
		// What is going to be printed. If the buffers go in overflow increase its size (see constants.h)
		char buffer [BUFFERSIZE];
		char reffub [BUFFERSIZE];
		// name of the object to load and the name of a type of object
		char name[NAMELUN+17];
		char input[DESCRIPTIONSIZE];
		// object to load
		FILE *objfile;
		// array to give to Rmotor whit counters
		int ivar[5];
		int ipos = 0;
		long double lvar[10];
		int lpos=0;
	
		// Title
		strcpy(buffer, "NEW OBJECT INITIALIZATION:\n");
		// A number
		if(n > 0){
			strcat(buffer, "object number %i");
			ivar[ipos] = n;
			ipos++;
		}
		// Ask user if he want to load a preexistent object
		strcpy (reffub, buffer);
		strcat (reffub, "\n\nDo you want to load a saved object?\n&tdDigit the name of the object you want to load or 'n' if you want to create a new object.");
		OPS(inf, reffub, ivar, lvar);
		scanf("%s", reffub);
		// if the user want to load an object
		if(0 != strcmp(reffub, "n")) {
			//add the extension (.object) and the path objects/
			strcat(reffub, ".object");
			strcpy(name, "Objects/");
			strcat(name, reffub);
			objfile = fopen(name, "r");
			if(objfile==NULL) {
				OPSE(inf, "The file you would to load doesn't exist!\nRestart initialization sequence", 0, 0);
				SafeIScan(inf, &ivar[0]);
				InitObject(inf, obj, Stype, n);
				return;
			}
			// Read name, type, radius, mass and color, then close the file
			ScanFString(obj->name, objfile);
			ScanFString(input, objfile);
			obj->type = typeSearchName(Stype, input);
			fscanf(objfile, "%d", &obj->color.red);
			fscanf(objfile, "%d", &obj->color.green);
			fscanf(objfile, "%d", &obj->color.blue);
			fscanf(objfile, "%Lf", &obj->radius);
			fscanf(objfile, "%Lf", &obj->mass);
			fclose(objfile);
			// tell name, type, radius and mass whitout ask
			strcat(buffer, "\n\nname:    ");
			strcat(buffer, obj->name);
			strcat(buffer, "\n\ntype of the object:  ");
			strcat(buffer, obj->type->name);
			strcat(buffer, "\n\ncolor:  %i %i %i");
			ivar[ipos] = obj->color.red;
			ipos++;
			ivar[ipos] = obj->color.green;
			ipos++;
			ivar[ipos] = obj->color.blue;
			ipos++;
			strcat(buffer, "\n\nradius:  %l");
			lvar[lpos] = obj->radius;
			lpos++;
			strcat(buffer, "\n\nmass:  ");
		}
		//if the user doesn't want to load from a file an object
		else {
			// some space and ask about the name
			strcat (buffer, "\n\nname:    ");
			strcpy (reffub, buffer);
			strcat (reffub, "\n&tdThe name of the object must be of a maximum of %i characters and spaces are not allowed");
			ivar[ipos] = NAMELUN-1;
			OPS(inf, reffub, ivar, lvar);
			scanf("%s", obj->name);
			strcat(buffer, obj->name);
			// ask about the type
			obj->type = TypeBrowser(inf, Stype, "Let's choose the type of object for your new object");
			strcat(buffer, "\n\ntype:    ");
			strcat(buffer, obj->type->name);
			//ask about the color
			strcat(buffer, "\n\ncolor:  ");
			strcpy(reffub, buffer);
			strcat(reffub, "\n&tdThe color of the new object must be composed of three numbers whit value 0 to 255, the first is the red, the second the green and the third the blue");
			OPS(inf, reffub, ivar, lvar);
			obj->color = ScanColor(inf, obj->type->color_min, obj->type->color_max);
			ivar[ipos] = obj->color.red;
			ipos++;
			ivar[ipos] = obj->color.green;
			ipos++;
			ivar[ipos] = obj->color.blue;
			ipos++;
			// ask about the radius
			strcat(buffer, " %i %i %i \n\nradius:  ");
			strcpy(reffub, buffer);
			strcat(reffub, " (Km)");
			OPS(inf, reffub, ivar, lvar);
			scanf("%Lf", &obj->radius);
			lvar[lpos] = obj->radius;
			lpos++;
			// ask about the mass (a loop because continue to ask if the mass is out of range)
			strcat(buffer, "%l\n\nmass:  ");
			do {
				strcpy(reffub, buffer);
				strcat(reffub, " (t) 1 ton = 1000 Kg\n&tdFor the type ");
				strcat(reffub, obj->type->name);
				strcat(reffub, " the mass must be:\nmin: %l\nmax: ");
				lvar[lpos] = obj->type->mass_min;
				if(obj->type->mass_max == -1)
					strcat(reffub, "infinity");
				else {
					strcat(reffub, "%l");
					lvar[lpos+1] = obj->type->mass_max;
				}
				OPS(inf, reffub, ivar, lvar);
				scanf("%Lf", &obj->mass);
				//the mass is valid if is below min mass and under max mass
				if(obj->mass > obj->type->mass_min && ((obj->mass < obj->type->mass_max) || (obj->type->mass_max == -1)) )
					break;
			}
			while(1);
		}
		// ask about the x
		lvar[lpos] = obj->mass;
		lpos++;
		strcat(buffer, "%l\n\nposition of the object in the x axis:  ");
		strcpy(reffub, buffer);
		strcat(reffub, " (Km)");
		OPS(inf, reffub, ivar, lvar);
		scanf("%Lf", &obj->x);
		fflush(stdin);
		// ask about the y
		lvar[lpos]=obj->x;
		lpos++;
		strcat (buffer, "%l\n\nposition of the object in the y axis:  ");
		strcpy (reffub, buffer);
		strcat (reffub, " (Km)");
		OPS(inf, reffub, ivar, lvar);
		scanf("%Lf", &obj->y);
		fflush(stdin);
		// ask about the z
		lvar[lpos]=obj->y;
		lpos++;
		strcat (buffer, "%l\n\nposition of the object in the z axis:  ");
		strcpy (reffub, buffer);
		strcat (reffub, " (Km)");
		OPS(inf, reffub, ivar, lvar);
		scanf("%Lf", &obj->z);
		fflush(stdin);
		// ask about the x's fast
		lvar[lpos]=obj->z;
		lpos++;
		strcat (buffer, "%l\n\nfast of the object throught the x axis:  ");
		strcpy (reffub, buffer);
		strcat (reffub, " (Km/s)");
		OPS(inf, reffub, ivar, lvar);
		scanf("%Lf", &obj->velx);
		fflush(stdin);
		// ask about the y's fast
		lvar[lpos]=obj->velx;
		lpos++;
		strcat (buffer, "%l\n\nfast of the object throught the y axis:  ");
		strcpy (reffub, buffer);
		strcat (reffub, " (Km/s)");
		OPS(inf, reffub, ivar, lvar);
		scanf("%Lf", &obj->vely);
		fflush(stdin);
		// ask about the z's fast
		lvar[lpos]=obj->vely;
		lpos++;
		strcat (buffer, "%l\n\nfast of the object throught the z axis:  ");
		strcpy (reffub, buffer);
		strcat (reffub, " (Km/s)");
		OPS(inf, reffub, ivar, lvar);
		scanf("%Lf", &obj->velz);
		fflush(stdin);
		// finish the asking
		lvar[lpos]=obj->velz;
		lpos++;
		strcat(buffer, "%l\n\nInitializing of the new object complete:\nPress 0 if you are not happy of this configuration and you want to reinitialize the object\nPress 1 if you want to save this object in a file\nPress a number that is >1 to continue");
		OPS(inf, buffer, ivar, lvar);
		SafeIScan(inf, ivar);
		if(ivar[0] == 1) {
			SaveObject(inf, obj);
		}
		if(ivar[0] == 0)
			InitObject(inf, obj, Stype, n);
		return;
	}
 
/***
 * The SaveObject function save a object in a file
 */
	void SaveObject(tinf *inf, tobj *obj) {
	
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
			OPS(inf, "While saving: The object you want to save alredy exist.\nDo you want to delete the previous object and save this? [n = no | something else = y]", 0, 0);
			scanf("%s", input);
			if(strcmp(input, "n") == 0)
				return;
		}
	
		// Write the object
		dest = fopen(path, "w");
		fprintf(dest, "%s\n%s\n%d\n%d\n%d\n%.128Lf\n%.128Lf", obj->name, obj->type->name, obj->color.red, obj->color.green, obj->color.blue,  obj->radius ,obj->mass);
		fclose(dest);
	
		OPS(inf, "OBJECT SAVED WHIT SUCCESS!\n\nPress something to continue", 0, 0);
		scanf("%s", input);		
	
		return;	
	}

/***
 * InitSystem is a function that initialize a new system
 */
	tsys *InitSystem (tinf *inf, tStype *Stype) {
		
		//to give to OPS and counter
		int c;
		//the system to create
		tsys *sys = (tsys *) malloc (sizeof(tsys));
		if(sys == NULL)
			do {
				OPSML(inf, "InitSystem");
				sys = (tsys *) malloc (sizeof(tsys));
				if(sys != NULL)
					break;
			}
			while(1);
		//the buffers (dinamic and static)
		char sbuf[BUFFERSIZE];
		char dbuf[BUFFERSIZE];
		
		//set the type struct pointer
		sys->Stype = Stype;
		//set the system's time
		sys->stime.year = 0;
		sys->stime.hour = 0;
		sys->stime.day = 0;
		sys->stime.min = 0;
		sys->stime.sec = 0;
		sys->stime.millisec = 0;
		
		//set the constant of gravitation. 6.67e-11 (m*m*m)/(Kg*s*s) but whit our units (t, s and Km) is 6.67e-17
		sys->G = 667e-19;
		
		// Ask for the name of the new system
		c = NAMELUN-1;
		strcpy(sbuf, "NEW SYSTEM INITIALIZATION\n\nname");
		strcpy(dbuf, sbuf);
		strcat(dbuf, " of the system:\n&tdIsn't allowed any spaces and can be of a maximum of %i characters");
		OPS (inf, dbuf, &c, 0);
		scanf("%s", sys->name);
		strcat(sbuf, ":    ");
		strcat(sbuf, sys->name);
		//ask for the precision
		strcat(sbuf, "\n\nprecision");
		strcpy(dbuf, sbuf);
		strcat(dbuf, " of the simulation:\n&tdMeans how often the simulator recalculate the data to produce more precise simulation. A simulation whit precision 2 mean that every two in-simulation-second the phisic motor rework the datas");
		OPS (inf, dbuf, 0, 0);
		scanf("%Lf", &sys->precision);
		strcat(sbuf, ":    %l\n\n\n");
		// ask if initialize new objects
		strcat(sbuf, "Configuration of the system complete. But the system doesn't have any object to work on yet. Type the number of object do you want to create now. You can press zero to go directly to the new system created whitout create any new object, however you can create, modify and delete object later, while the simulation is going");
		OPS(inf, sbuf, 0, &sys->precision);
		SafeIScan(inf, &sys->nactive);
		sys->nalloc = sys->nactive;
		for (; ;) {
			if(sys->nactive >= 0)
				break;
			OPSE (inf, "Wrong value: Must be put a number bigger than zero!", 0, 0);
			SafeIScan(inf, &sys->nactive);
		}
		
		//alloc the object array
		sys->o = (tobj *) malloc ( sizeof(tobj) * sys->nactive );
			
		// Initialize the objects
		for (c=0; c!=sys->nactive; c++)
			InitObject(inf, &sys->o[c], sys->Stype, c+1);
	 
	 	return sys;
	}
	
	
	/***
	 * This function reduce the object buffer size
	 */
	 
	void ReduceObjBuf(tsys *sys, tinf *inf) {
		
		tobj *newo;		//(new o)bject buffer
		int c;			//(c)ounter
		
		// create a new buffer whit less objects
		newo = (tobj *) malloc (sizeof(tobj) * (sys->nalloc-OBJBUFSIZE));
		do{
			if(newo != NULL)
				break;
			else {
				OPSML(inf, "ReduceObjBuf");
				newo = (tobj *) malloc (sizeof(tobj) * (sys->nalloc + OBJBUFSIZE));
			}	
		}
		while(1);
		// update counter
		sys->nalloc -= OBJBUFSIZE;
		// copy what is stored in the old buffer in the new buffer
		for(c=0; c!= sys->nalloc-1; c++)
			newo[c] = sys->o[c];
		// delete the old buffer
		free(sys->o);
		// point sys->o at the new buffer
		sys->o = newo;
		//if can be reduced more, recall itself
		if(sys->nalloc - sys->nactive >= OBJBUFSIZE)
			ReduceObjBuf(sys, inf);
	
		free(newo);
		return;
	}
	
	/***
	 * This function make the object buffer size bigger
	 */
	void ExtendObjBuf(tsys *sys, tinf *inf){
	
		tobj *newo;		//(new o)bject buffer
		int c;			//(c)ounter
		// create a new buffer whit more objects
		newo = (tobj *) malloc (sizeof(tobj) * (sys->nalloc + OBJBUFSIZE));
		do{
			if(newo != NULL)
				break;
			else {
				do{
					OPSML(inf, "ExtendObjBuf");
					newo = (tobj *) malloc (sizeof(tobj) * (sys->nalloc + OBJBUFSIZE));
				}
				while(newo == NULL);
			}
		}
		while(1);
		// copy what is stored in the old buffer in the new buffer
		for(c=0; c!= sys->nalloc; c++)
			newo[c] = sys->o[c];
		// update counter
		sys->nalloc += OBJBUFSIZE;
		// delete the old buffer
		free(sys->o);
		// point sys->o at the new buffer
		sys->o = newo;
		return;
	}
	
	/***
	 * Save a system in the directory Systems/
	 */
	void SaveSys(tsys *sys, tinf *inf){
		
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
			OPS(inf, "While saving: The system you want to save alredy exist.\nDo you want to delete the previous system and save this? [n = no | something else = y]", NULL, NULL);
			scanf("%s", input);
			if(strcmp(input, "n") == 0)
				return;
		}
	
		// Write the object
		dest = fopen (path, "w");
		// Write information about the system
		fprintf (dest, "%.128Lf\n%d\n%.128Lf\n",  sys->precision, sys->nactive, sys->G);
		fprintf (dest, "%d\n%d\n%d\n%d\n%d\n%d\n", sys->stime.year, sys->stime.day, sys->stime.hour, sys->stime.min, sys->stime.sec, sys->stime.millisec);	//the time
		// write the system's object's datas
		for(i=0; i!=sys->nactive; i++) {
			fprintf(dest, "%s\n%s\n%d\n%d\n%d\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n", sys->o[i].name, sys->o[i].type->name, sys->o[i].color.red, sys->o[i].color.green, sys->o[i].color.blue, sys->o[i].radius ,sys->o[i].mass ,sys->o[i].x ,sys->o[i].y ,sys->o[i].z ,sys->o[i].velx ,sys->o[i].vely ,sys->o[i].velz);
		}
		fclose(dest);
	
		OPS(inf, "SYSTEM SAVED WHIT SUCCESS!\n\nPress something to continue", NULL, NULL);
		scanf("%s", input);		
	
		return;
	}
	/**
	 * Load a system from a file
	 * create a new system and return his pointer
	 */
	tsys *LoadSystem(tinf *inf, tStype *Stype){
	
		//the system
		tsys *sys = (tsys *) malloc (sizeof(tsys));
		if(sys == NULL)
			do {
				OPSML(inf, "InitSystem");
				tsys *sys = (tsys *) malloc (sizeof(tsys));
				if(sys != NULL)
					break;
			}
			while(1);
		char path[NAMELUN+12];	// the file of the system
		FILE *dest;				// the file of the system
		int i;					// counter
		//ask which system
		OPS(inf, "LOAD SYSTEM\n\nWhat is the name of the system you want to load?", NULL, NULL);
		scanf("%s", sys->name);
		//write the path
		strcpy (path, "Systems/");
		strcat (path, sys->name);
		strcat (path, ".sys");
		//open the file
		dest = fopen(path, "r");
		if (dest == NULL) {
			OPSE(inf, "A system whit that name doesn't exist! Type something to continue and return to the menù", NULL, NULL);
			scanf("%s", path);
			free(sys);
			return NULL;
		}
		//scanf system's informations
		fscanf (dest, "%Lf\n%d\n%Lf\n", &sys->precision, &sys->nactive, &sys->G);
		fscanf (dest, "%d\n%d\n%d\n%d\n%d\n%d\n", &sys->stime.year, &sys->stime.day, &sys->stime.hour, &sys->stime.min, &sys->stime.sec, &sys->stime.millisec);
		//alloc memory
		sys->nalloc = sys->nactive;
		do{
			sys->o = (tobj *) malloc (sizeof(tobj) * sys->nalloc);
			if (sys->o != NULL)
				break;
			OPSML(inf, "LoadSystem");
		}
		while(1);
		//fscanf for objects datas
		for(i=0; i!=sys->nactive; i++) {
			ScanFString(sys->o[i].name, dest);
			ScanFString(path, dest);
			fscanf(dest, "%d\n%d\n%d\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n", &sys->o[i].color.red, &sys->o[i].color.green, &sys->o[i].color.blue, &sys->o[i].radius, &sys->o[i].mass, &sys->o[i].x, &sys->o[i].y, &sys->o[i].z, &sys->o[i].velx, &sys->o[i].vely, &sys->o[i].velz);
			sys->o[i].type = typeSearchName(Stype, path);
		}
		
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
	
