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
 * 	This function initialize a new system and ask information
 * */

	short InitSystem ();
