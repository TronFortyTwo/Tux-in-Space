/*
 * HERE we have functions that help whit the system of the program 
 * 
 * 
 */



/*** A function that update the inf.active array
 *
 *  */ 
	void UpdateActive (tsys *sys);
	void UpdateActive (tsys *sys) {
		short c = 0;	// c(ounter)
		short a = 0;	// a(ctive)
		for (; c!=NUMOGG; c++) {
			if ( (sys->o[c].type > 11)|(sys->o[c].type < 0) ) {
				sys->active[a] = c;
				a++;
			}
		}
		sys->active[NUMOGG] = a;
	
		return;
	}

/*** Update Maxoutput is a function that update maxoutput
 * 
 *	*/
	void Setmaxoutput(tinf *inf);
	void Setmaxoutput(tinf *inf) {
		inf->maxoutput = (inf->column - 2 * FRAMELUN) * (inf->line - 2 * FRAMELUN -1);
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
		char buffer[BUFFERSIZE];
		// char variable array
		char cvar[NAMELUN];
		int ivar[1];
		short ipos=0;
		long double lvar[7];
		short lpos=0;
		// character writed in buffer and a character counter variable whit similar objective
		int position;
	
		//Clear the string from some unexpected '\0'
		ClearString(buffer, BUFFERSIZE, ' '); 
	
		// Title
		position = Was(buffer, "NEW OBJECT INITIALIZATION:\n\n", 0);
		printf("%d", position);
		// A number
		if(n >= 0){
			position = position + Was(buffer, "object number %i", position);
			ivar[ipos]=n;
			ipos++;
		}
		// some space and ask about the name
		position = position + Was(buffer, "\n\n\nname:", position);
		Was (buffer, "[max %i character][only one word]\0\0", position);
		ivar[ipos] = NAMELUN-1;
		Rmotor(0, inf, 0, buffer, ivar, lvar, cvar);
		scanf("%s", obj->name);
		// ask about the type
		strcpy(cvar, obj->name);
		ClearString(buffer+position, BUFFERSIZE-position, ' '); 
		position = position + Was(buffer, "%s\ntype of the object:", position);
		Was(buffer, "\n1  = Spaceship\n2  = Sun\n3  = Planet (generic)\n4  = Planet (Rock)\n5  = Planet (Giant Gas)\n6  = Natural satellite\n7  = Asteroid\n8  = Comet\n9  = Black Hole\n10 = Space station\0", position);
		Rmotor(0, inf, 0, buffer, ivar, lvar, cvar);
		scanf("%d", &obj->type);
		// ask about the mass
		ivar[ipos]=obj->type;
		ipos++;
		ClearString(buffer+position, BUFFERSIZE-position, ' '); 
		position = position + Was(buffer, "%i\nmass:", position);
		Was(buffer, " (Kg)\0",position);
		Rmotor(0, inf, 0, buffer, ivar, lvar, cvar);
		scanf("%Lf", &obj->mass);
		// ask about the x
		lvar[lpos]=obj->mass;
		lpos++;
		ClearString(buffer+position, BUFFERSIZE-position, ' '); 
		position = position + Was(buffer, "%l\nposition of the object in the x axis:", position);
		Was(buffer, " (Km)\0", position);
		Rmotor(0, inf, 0, buffer, ivar, lvar, cvar);
		scanf("%Lf", &obj->x);
		// ask about the y
		lvar[lpos]=obj->x;
		lpos++;
		ClearString(buffer+position, BUFFERSIZE-position, ' '); 
		position = position + Was(buffer, "%l\nposition of the object in the y axis:", position);
		Was(buffer, " (Km)\0", position);
		Rmotor(0, inf, 0, buffer, ivar, lvar, cvar);
		scanf("%Lf", &obj->y);
		// ask about the z
		lvar[lpos]=obj->y;
		lpos++;
		ClearString(buffer+position, BUFFERSIZE-position, ' '); 
		position = position + Was(buffer, "%l\nposition of the object in the z axis:", position);
		Was(buffer, " (Km)\0", position);
		Rmotor(0, inf, 0, buffer, ivar, lvar, cvar);
		scanf("%Lf", &obj->z);
		// ask about the x's fast
		lvar[lpos]=obj->z;
		lpos++;
		ClearString(buffer+position, BUFFERSIZE-position, ' '); 
		position = position + Was(buffer, "%l\nfast of the object on the x axis:", position);
		Was(buffer, " (Km/s)\0", position);
		Rmotor(0, inf, 0, buffer, ivar, lvar, cvar);
		scanf("%Lf", &obj->velx);
		// ask about the y's fast
		lvar[lpos]=obj->velx;
		lpos++;
		ClearString(buffer+position, BUFFERSIZE-position, ' '); 
		position = position + Was(buffer, "%l\nfast of the object on the y axis:", position);
		Was(buffer, " (Km/s)\0", position);
		Rmotor(0, inf, 0, buffer, ivar, lvar, cvar);
		scanf("%Lf", &obj->vely);
		// ask about the z's fast
		lvar[lpos]=obj->vely;
		lpos++;
		ClearString(buffer+position, BUFFERSIZE-position, ' '); 
		position = position + Was(buffer, "%l\nfast of the object on the z axis:", position);
		Was(buffer, " (Km/s)\0", position);
		Rmotor(0, inf, 0, buffer, ivar, lvar, cvar);
		scanf("%Lf", &obj->velz);
		// finish the asking
		lvar[lpos]=obj->velz;
		lpos++;
		ClearString(buffer+position, BUFFERSIZE-position, ' '); 
		position = position + Was(buffer, "%l\n\nInitializing complete. Digit 42 to intialize the object again or anythig else to continue\0", position);
		Rmotor(0, inf, 0, buffer, ivar, lvar, cvar);
		scanf("%d", ivar);
		if(ivar[0]==42)
			InitObject(inf, obj, n);
		
		return;
	}
