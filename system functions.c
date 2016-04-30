/*
 * HERE we have functions that help whit the system of the program 
 * 
 */

//Prototypes
	void SaveObject(tinf *, tobj *);
	void Setmaxoutput(tinf *inf);
	void InitObject (tinf *inf, tobj *obj, tSkind *knd, short n);
	void InitSystem (tsys *sys, tinf *inf);

/*** Update Maxoutput is a function that update maxoutput
 * 
 *	*/
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
	void InitObject (tinf *inf, tobj *obj, tSkind *knd, short n) {
		
		// What is going to be printed. If the function go in segmentation fault, increase it
		char buffer [BUFFERSIZE];
		char reffub [BUFFERSIZE];
		// name of the object to load and the name of a kind of object
		char name[NAMELUN+17];
		char input[DESCRIPTIONSIZE];
		// object to load
		FILE *objfile;
		// array to give to Rmotor whit counters
		int ivar[2];
		short ipos = 0;
		long double lvar[7];
		short lpos=0;
		//counter
		short i;
		short w;
	
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
		// if the user don't want to load an object
		if(0 != strcmp(reffub, "n")) {
			//add the extension (.object) and the path objects/
			strcat(reffub, ".object");
			strcpy(name, "Objects/");
			strcat(name, reffub);
			objfile = fopen(name, "r");
			if(objfile==NULL) {
				OPSE(inf, "The file you would to load doesn't exist!\nRestart initialization sequence", 0, 0);
				SafeIScan(inf, &ivar[0]);
				InitObject(inf, obj, knd, n);
				return;
			}
			// Read name, kind and mass and close the file
			fscanf(objfile, "%s\n%s\n%Lf", obj->name, obj->kind, &obj->mass);
			fclose(objfile);
			//tell name, kind and mass whitout ask
			strcat(buffer, "\n\n\nname:    ");
			strcat(buffer, obj->name);
			strcat(buffer, "\n\ntype of the object:  ");
			strcat(buffer, obj->kind);
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
			strcat(buffer, obj->name);
			// ask about the kind (categoria throught subcategoria)
			strcat(buffer, "\n\ntype of the object:  ");
			strcpy(name, "NULL");
			// the loop that ask for the kind browsing throught the gerarchic kind structure
			do {
				// reset the temp buffer
				strcpy(reffub, buffer);
				//make a line of space
				strcat(reffub, "\n");
				// the loop that choose right kinds
				for (i=0, w=0; i!=knd->number; i++) {
					// if name variable is = knd->kind[i]->parent add it at the reffub 
					if(strcmp(name, knd->kind[i].parent) == 0) {
						strcat (reffub, "\n-");
						strcat (reffub, knd->kind[i].name);
						w++;
					}
				}
				//if the kind hasn't any subtype exit the loop remembing name as kind
				if (w == 0){
					strcpy(obj->kind, name);
					break;
				}
				//else add the back and the description button
				else {
					strcat(reffub, "\n---back\n---for a short description type descr");
				}
				// print the reffub and scanf the user answer
				OPS(inf, reffub, ivar, lvar);
				scanf("%s", input);
				//if the user choose back make name NULL
				if(strcmp(input, "back") == 0) {
					strcpy(name, "NULL");
				}
				//if the user ask a description show a description of the object
				else if(strcmp(input, "descr") == 0) {
					OPS(inf, "OBJECT DESCRIPTION\n\nOf which kind of object do you want an explaination?", ivar, lvar);
					scanf("%s", input);
					strcpy(reffub, "OBJECT DESCRIPTION: ");
					strcat(reffub, input);
					strcat(reffub, "\n\n");
					KindDescriptionFromName (knd, input);
					strcat(reffub, input);
					strcat(reffub, "\n\nThis kind of object is under the category: ");
					strcat(reffub, KindParentFromName(knd, input) );
					strcat(reffub, "\n\nPress a button to continue");
					OPS(inf, reffub, ivar, lvar);
					scanf("%s", input);
				}
				//else assign to the name the input
				else
					strcpy(name, input);
			} while(1);
			
			// ask about the mass
			strcat(buffer, obj->kind);
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
			InitObject(inf, obj, knd, n);
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
		fprintf(dest, "%s\n%s\n%Lf", obj->name, obj->kind, obj->mass);
		fclose(dest);
	
		OPS(inf, "OBJECT SAVED WHIT SUCCESS!\n\nPress something to continue", 0, 0);
		scanf("%c", &input);
		fflush(stdin);
		
	
		return;	
	}

/***
 * InitSystem is a function that initialize a new system
 */
	void InitSystem (tsys *sys, tinf *inf) {
		
			//counter for loops
			short l;
			//to give to OPS
			int c;
		
			//reset the system's time
			sys->year = 0;
			sys->hour = 0;
			sys->day = 0;
			sys->min = 0;
			sys->sec = 0;
			sys->millisec = 0;
		
			// Ask the name of the new system
			c = NAMELUN-1;
			OPS (inf, "NEW SYSTEM INITIALIZATION\n\nWhat is the name of this new system? [no spaces] [max %i characters]", &c, 0);
			scanf("%s", sys->name);
			fflush(stdin);

			// Ask the user how many object initialize now.
			OPS(inf, "NEW SYSTEM INITIALIZATION\n\ndo you want to configure some object of the system now?\nDigit the number of object you want to set up now\n\n (you could add, remove and modify objects in the system later, in runtime)", 0, 0);
			SafeIScan(inf, &sys->nactive);
			for (; ;) {
				if(sys->nactive >= 0)
					break;
				OPSE (inf, "Wrong value: Must be put a number bigger than zero!", 0, 0);
				SafeIScan(inf, &sys->nactive);
			}
			
			//alloc the object array
			sys->o = (tobj *) malloc ( sizeof(tobj) * sys->nactive );
			
			// Initialize the objects
			for (l=0; l!=sys->nactive; l++)
				InitObject(inf, &sys->o[l], sys->Skind, l+1);
	 
		return;
	}

