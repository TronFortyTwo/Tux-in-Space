/*
 * HERE we have functions that help whit the system of the program 
 * 
 */

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
 * This function gave a number write in a variable the name
 * 
 */
	void ExtractType (int type, char *dest);
	void ExtractType (int type, char *dest) {
	
		if (type <= 0)
			strcpy(dest, "Error Type");
		else if (type == 0)
			strcpy(dest, "Void");
		else if (type == 1)
			strcpy(dest, "Spaceship");
		else if (type == 2)
			strcpy(dest, "Sun");
		else if (type == 3)
			strcpy(dest, "Generic Planet");
		else if (type == 4)
			strcpy(dest, "Rock Planet");
		else if (type == 5)
			strcpy(dest, "Giant Gas Planet");
		else if (type == 6)
			strcpy(dest, "Natural Satellite");
		else if (type == 7)
			strcpy(dest, "Asteroid");
		else if (type == 8)
			strcpy(dest, "Comet");
		else if (type == 9)
			strcpy(dest, "Black Hole");
		else if (type == 10)
			strcpy(dest, "Space Station");
		else if (type == 11)
			strcpy(dest, "Unknow type");
		else if (type >= 11)
			strcpy(dest, "Error Type");
	
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
		strcat(buffer, " \n\ntype of the object:  ");
		strcpy(reffub, buffer);
		strcat(reffub, "\n1  = Spaceship\n2  = Sun\n3  = Planet (generic)\n4  = Planet (Rock)\n5  = Planet (Giant Gas)\n6  = Natural satellite\n7  = Asteroid\n8  = Comet\n9  = Black Hole\n10 = Space station\n");
		OPS(inf, reffub, ivar, lvar);
		SafeIScan(inf, &obj->type);
		// ask about the mass
		ExtractType(obj->type, reffub);
		strcat(buffer, reffub);
		strcat(buffer, "\n\nmass:  ");
		strcpy(reffub, buffer);
		strcat(reffub, " (Kg)");
		OPS(inf, reffub, ivar, lvar);
		scanf("%Lf", &obj->mass);
		fflush(stdin);
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
		strcat(buffer, "%l\n\nInitializing of the new object complete:\nPress 4 if you are not happy of this configuration and you want to reinitialize the object\nPress a number that is not 4 to continue\0");
		OPS(inf, reffub, ivar, lvar);
		SafeIScan(inf, ivar);
		if(ivar[0] == 4)
			InitObject(inf, obj, n);
		return;
	}
