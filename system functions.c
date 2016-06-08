/*
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
		
		// What is going to be printed. If the buffers go in overflow increase its size
		char buffer [BUFFERSIZE];
		char reffub [BUFFERSIZE];
		// name of the object to load and the name of a type of object
		char name[NAMELUN+17];
		char input[DESCRIPTIONSIZE];
		// object to load
		FILE *objfile;
		// array to give to Rmotor whit counters
		int ivar[2];
		int ipos = 0;
		long double lvar[7];
		int lpos=0;
	
		// Title
		strcpy(buffer, "NEW OBJECT INITIALIZATION:\n\n");
		// A number
		if(n >= 0){
			strcat(buffer, "object number %i");
			ivar[ipos] = n;
			ipos++;
		}
		// Ask user if he want to load a preexistent object
		strcpy (reffub, buffer);
		strcat (reffub, "\n\n\nDo you want to load a saved object?\nDigit the name of the object you want to load or 'n' if you don't want to create a new object.\n");
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
			// Read name, type and mass and close the file
			ScanFString(obj->name, objfile);
			ScanFString(input, objfile);
			obj->type = typeSearchName(Stype, input);
			fscanf(objfile, "%Lf", &obj->mass);
			fclose(objfile);
			//tell name, type and mass whitout ask
			strcat(buffer, "\n\n\nname:    ");
			strcat(buffer, obj->name);
			strcat(buffer, "\n\ntype of the object:  ");
			strcat(buffer, obj->type->name);
			strcat(buffer, "\n\nmass:  ");
		}
		//if the user doesn't want to load from a file an object
		else {
			// some space and ask about the name
			strcat (buffer, "\n\n\nname:    ");
			strcpy (reffub, buffer);
			strcat (reffub, "\nThe name of the object must be of a maximum of %i characters and spaces are not allowed");
			ivar[ipos] = NAMELUN-1;
			OPS(inf, reffub, ivar, lvar);
			scanf("%s", obj->name);
			strcat(buffer, obj->name);
			// ask about the type
			obj->type = TypeBrowser(inf, Stype, "Let's choose the type of object for your new object");
			strcat(buffer, "\n\ntype:    ");
			strcat(buffer, obj->type->name);
			// ask about the mass
			strcat(buffer, "\n\nmass:  ");
			strcpy(reffub, buffer);
			strcat(reffub, " (t) 1 ton = 1000 Kg");
			OPS(inf, reffub, ivar, lvar);
			scanf("%Lf", &obj->mass);
			fflush(stdin);
		}
		// ask about the x
		lvar[lpos]=obj->mass;
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
		char input;
		FILE *dest;
		
		//Write the path
		strcpy(path, "Objects/");
		strcat(path, obj->name);
		strcat(path, ".object");
		
		//control that the file isn't alredy existent
		dest = fopen(path, "r");
		if(dest != NULL) {
			fclose(dest);
			OPS(inf, "While saving: The object you want to save alredy exist.\nDo you want to delete the previous object and save this? [n = no | everyother = y]", 0, 0);
			scanf("%c", &input);
			fflush(stdin);
			if(input == 'n')
				return;
		}
	
		// Write the object
		dest = fopen(path, "w");
		fprintf(dest, "%s\n%s\n%Lf", obj->name, obj->type->name, obj->mass);
		fclose(dest);
	
		OPS(inf, "OBJECT SAVED WHIT SUCCESS!\n\nPress something to continue", 0, 0);
		scanf("%s", &input);
		fflush(stdin);
		
	
		return;	
	}

/***
 * InitSystem is a function that initialize a new system
 */
	tsys *InitSystem (tinf *inf, tStype *Stype) {
		
			//to give to OPS and counter
			int c;
			//the system to create
			static tsys sys;
			//the buffers (dinamic and static)
			char sbuf[BUFFERSIZE];
			char dbuf[BUFFERSIZE];
		
			//set the type struct pointer
			sys.Stype = Stype;
			//set the system's time
			sys.stime.year = 0;
			sys.stime.hour = 0;
			sys.stime.day = 0;
			sys.stime.min = 0;
			sys.stime.sec = 0;
			sys.stime.millisec = 0;
			
			//set the constant of gravitation. 6.67e-11 (m*m*m)/(Kg*s*s) but whit our units (t, s and Km) is 6.67e-17
			sys.G = 667e-19;
			
			// Ask for the name of the new system
			c = NAMELUN-1;
			strcpy(sbuf, "NEW SYSTEM INITIALIZATION\n\nname");
			strcpy(dbuf, sbuf);
			strcat(dbuf, " of the system:\n    Isn't allowed any spaces and can be of a maximum of %i characters");
			OPS (inf, dbuf, &c, 0);
			scanf("%s", sys.name);
			strcat(sbuf, ":    ");
			strcat(sbuf, sys.name);
			//ask for the precision
			strcat(sbuf, "\n\nprecision");
			strcpy(dbuf, sbuf);
			strcat(dbuf, " of the simulation:\n    Means how often the simulator recalculate the data to produce more precise simulation. A simulation whit precision 2 mean that every two in-simulation-second the phisic motor rework the datas");
			OPS (inf, dbuf, 0, 0);
			scanf("%Lf", &sys.precision);
			strcat(sbuf, ":    %l\n\n\n");
			// ask if initialize new objects
			strcat(sbuf, "Configuration of the system complete. But the system doesn't have any object to work on yet. Type the number of object do you want to create now. You can press zero to go directly to the new system created whitout create any new object, however you can create, modify and delete object later, while the simulation is going");
			OPS(inf, sbuf, 0, &sys.precision);
			SafeIScan(inf, &sys.nactive);
			sys.nalloc = sys.nactive;
			for (; ;) {
				if(sys.nactive >= 0)
					break;
				OPSE (inf, "Wrong value: Must be put a number bigger than zero!", 0, 0);
				SafeIScan(inf, &sys.nactive);
			}
			
			//alloc the object array
			sys.o = (tobj *) malloc ( sizeof(tobj) * sys.nactive );
			
			// Initialize the objects
			for (c=0; c!=sys.nactive; c++)
				InitObject(inf, &sys.o[c], sys.Stype, c+1);
	 
		return &sys;
	}
	
	
	/***
	 * This function resize the buffer of object
	 */
	 
	void ResizeObject(tStype *Stype, tinf *inf, tobj **pointer, int old_size, int new_size) {
		//counter for loop and input
		int i;
		//the new buffer whit control whit RAM overload
		tobj *new_pointer = (tobj *) malloc (sizeof(tobj) * new_size);
		if (new_pointer == NULL) {
			for(; pointer != NULL;){
				OPSML(inf);
				ResizeObject(Stype, inf, pointer, old_size, new_size);
			}
		}
		//put in the new buffer the old buffer content
		for(i=0; i!=old_size; i++)
			new_pointer[i] = *pointer[i];
		//delete the old buffer
		free(*pointer);
		//set the new object
		for(i=old_size; i!=new_size; i++) {
			ResetObject(Stype, &new_pointer[i]);
		}
		//put in the old pointer the new address
		*pointer = new_pointer;
		
		return;
	}
	
	/***
	 * This function reset a object destroying his attribute
	 */
	void ResetObject(tStype *Stype, tobj *obj) {
		
		//reset !!!
		strcpy(obj->name, "\0");
		obj->type = typeSearchName(Stype, "Void");
		
		return;
	}
	

