/*
 * HERE we have functions that help whit the system of the program 
 * 
 */

//Prototypes
	void SaveObject(tinf *, tobj *);

/***
 * UpdateActive update the active list and the nactive var
 * 
 */
	void UpdateActive(tsys *sys);
	void UpdateActive(tsys *sys) {
		
		//counters
		short i;
		
		//reset the number of object active
		sys->nactive=0;
		
		//loop
		for (i=0; i!=NUMOGG; i++) {
			//if the object is active(!=0 so even error statuses) add it at the list and update the counters
			if(sys->o[i].type != 0) {
				sys->active[sys->nactive] = i;
				sys->nactive++;
			}
		}
	
	
		return;
	}
 
 

/*** Update Maxoutput is a function that update maxoutput
 * 
 *	*/
	void Setmaxoutput(tinf *inf);
	void Setmaxoutput(tinf *inf) {
		inf->maxoutput = (inf->width - 2 * FRAMELUN) * (inf->height - 2 * FRAMELUN -1);
		return;
	}


/***
 * 	This function InitObject initialize a new object and ask information about it
 * 
 * 	n is the number of the object to initialize, if in a list
 * 	
 * 	NOTE:
 * 	-this function is a bit :| Poker Face
 * 	-this is a recursive function
 */

	void InitObject (tinf *inf, tobj *obj, short n);
	
	void InitObject (tinf *inf, tobj *obj, short n) {
		
		// What is going to be printed. If the function go in segmentation fault, increase it
		char buffer [BUFFERSIZE];
		char reffub [BUFFERSIZE];
		// name of the object to load
		char name[NAMELUN+18];
		// object to load
		FILE *objfile;
		// array to give to Rmotor whit counters
		int ivar[2];
		short ipos = 0;
		long double lvar[7];
		short lpos=0;
	
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
		strcat (reffub, "\n\nDo you want to load a saved object?\nDigit the name of the object you want to load or 'n' if you not want to create a new object.\n");
		OPS(inf, reffub, ivar, lvar);
		scanf("%s", reffub);
		if(0 != strcmp(reffub, "n")) {
			//add the extension (.object) and the path objects/
			strcat(reffub, ".object");
			strcpy(name, "Objects/");
			strcat(name, reffub);
			objfile = fopen(name, "r");
			if(objfile==NULL) {
				OPS(inf, "ERROR!\n\nThe file you would to load doesn't exist! Restarting initialization sequence\nPress a number to continue", 0, 0);
				SafeIScan(inf, &ivar[0]);
				InitObject(inf, obj, n);
				return;
			}
			// Read name, type and mass
			fscanf(objfile, "%s\n%d\n%Lf", obj->name, &obj->type, &obj->mass);
			fclose(objfile);
			//tell name, type and mass whitout ask
			strcat(buffer, "\n\n\nname:    ");
			strcat(buffer, obj->name);
			strcat(buffer, "\n\ntype of the object:  ");
			ExtractType(obj->type, reffub);
			strcat(buffer, reffub);
			strcat(buffer, "\n\nmass:  ");
		}
		//if not
		else {
			// some space and ask about the name
			strcat (buffer, "\n\n\nname:    ");
			strcpy (reffub, buffer);
			strcat (reffub, "\nThe name of the object must be of a maximum of %i characters and spaces are not allowed");
			ivar[ipos] = NAMELUN-1;
			OPS(inf, reffub, ivar, lvar);
			scanf("%s", obj->name);
			fflush(stdin);
			// ask about the type
			strcat(buffer, obj->name); 
			strcat(buffer, "\n\ntype of the object:  ");
			strcpy(reffub, buffer);
			strcat(reffub, "\n1  = Spaceship\n2  = Sun\n3  = Planet (generic)\n4  = Planet (Rock)\n5  = Planet (Giant Gas)\n6  = Natural satellite\n7  = Asteroid\n8  = Comet\n9  = Black Hole\n10 = Space station\n");
			OPS(inf, reffub, ivar, lvar);
			SafeIScan(inf, &obj->type);
			// ask about the mass
			ExtractType(obj->type, reffub);
			strcat(buffer, reffub);
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
			InitObject(inf, obj, n);
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
			OPS(inf, "ERROR WHILE SAVING\n\nThe object you want to save alredy exist.\nDo you want to delete the previous object and save this? [n = no | everyother = y]", 0, 0);
			scanf("%c", &input);
			fflush(stdin);
			if(input == 'n')
				return;
		}
	
		// Write the object
		dest = fopen(path, "w");
		fprintf(dest, "%s\n%d\n%Lf", obj->name, obj->type, obj->mass);
		fclose(dest);
	
		OPS(inf, "OBJECT SAVED WHIT SUCCESS!\n\nPress something to continue", 0, 0);
		scanf("%c", &input);
		fflush(stdin);
		
	
		return;	
	}
