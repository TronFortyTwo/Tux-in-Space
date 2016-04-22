/*
 * Questo è il motore fisico che simula le leggi fisiche
 * This is the motor that emule the phisic law
 * 
 * Now the side effect that this function generated on struct obj are caused by:
 *		-Gravity force
 * 		-Inertia of mass
 *
 * Ora questa funzione modifica la struttura obj tramite:
 * 		-Forza di gravità
 * 		-inerzia delle masse
 */


int Pmotor (tsys *sys);

int Pmotor (tsys *sys) {
	
		// Counters for loops
		short i, l;
		// Distance between objects, and his ortogonal components
		long double dist, distx, disty, distz;
		// Tempoany variables
		long double temp1, temp2, temp3;
		
		// Gravity force
		// a loop that operate var active for var active
		for(i=0; i!=sys->nactive; i++) {
			// a loop that consider every planet (i+1 because whit l<i is alredy made, and whit i=l the two objects are the same)
			for (l=i+1; l!= sys->nactive; i++) {
				// First: must be individuated the baricenter of the sistem of obj i and obj (see Information.txt at the voice Pmotor)
				distx = sys->o[sys->active[i]].x - sys->o[sys->active[l]].x;
				disty = sys->o[sys->active[i]].y - sys->o[sys->active[l]].y;
				distz = sys->o[sys->active[i]].z - sys->o[sys->active[l]].z;
				dist  = pow ( (distx*distx + disty*disty + distz*distz) , 1/3);
				// individuate the intensity of acceleration
				temp1 = (sys->o[sys->active[i]].mass * sys->o[sys->active[l]].mass * sys->G) / (dist*dist);
				// for the calculate of the module F of i, I use this:		x : intensity of attraction = mass l : (mass i + mass l)  ||| then, x = (mass l * intensity of attraction) /intensity of attraction
				temp2 = sys->o[sys->active[l]].mass * temp1 / ( sys->o[sys->active[l]].mass + sys->o[sys->active[i]].mass );
				// then the same thing, turning the number (for l)
				temp3 = sys->o[sys->active[i]].mass * temp1 / ( sys->o[sys->active[l]].mass + sys->o[sys->active[i]].mass);
				// now sum the vel [i] whit:		number to sum [i] : distx = vector(temp2) : dist		then repeate for others coordinates
				sys->o[sys->active[i]].velx = sys->o[sys->active[i]].velx + temp2 * distx / dist;
				sys->o[sys->active[i]].vely = sys->o[sys->active[i]].vely + temp2 * disty / dist;
				sys->o[sys->active[i]].velz = sys->o[sys->active[i]].velz + temp2 * distz / dist;
				sys->o[sys->active[l]].velx = sys->o[sys->active[l]].velx + temp3 * distx / dist;
				sys->o[sys->active[l]].vely = sys->o[sys->active[l]].vely + temp3 * disty / dist;
				sys->o[sys->active[l]].velz = sys->o[sys->active[l]].velz + temp3 * distz / dist;
			}
		}
		// move the objects
		for (i=0; i!=sys->nactive; i++) {
			sys->o[sys->active[i]].x = (sys->o[sys->active[i]].x + sys->o[sys->active[i]].velx) * sys->precision ;
			sys->o[sys->active[i]].y = (sys->o[sys->active[i]].y + sys->o[sys->active[i]].vely) * sys->precision ;
			sys->o[sys->active[i]].z = (sys->o[sys->active[i]].z + sys->o[sys->active[i]].velz) * sys->precision ;
			}
	
		// update the time
		sys->millisec = 1000 * sys->precision;
		if (sys->millisec >= 1000 ) {
			for (; sys->millisec >1000; sys->sec++, sys->millisec = sys->millisec - 1000);
			if (sys->sec >= 60) {
				for (; sys->sec > 60; sys->min++, sys->sec = sys->sec-60);
				if (sys->min >= 60) {
					for (; sys->min > 60; sys->hour++, sys->min = sys->min-60);
					if (sys->hour >= 24){
						for (; sys->hour > 24; sys->day++, sys->hour = sys->hour-24);
						if (sys->day >= 365) {
							for (; sys->day > 365; sys->year++, sys->day = sys->day-365);
						}
					}
				}
			}
		}
	
		return 0;
		}
