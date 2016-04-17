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
 * 	This function initialize a new object and ask information
 * 
 * 	n is the number of the object to initialize
 */

	void InitObject (tinf *inf, tobj *obj, short n);
	void InitObject (tinf *inf, tobj *obj, short n) {
		
		// What is going to be printed
		char buffer[128];
		// char variable array
		char cvar[NAMELUN+1];
		int ivar[1];
		long double lvar[1];
		// character writed in buffer
		int position;
	
		
		
		return;
	}
