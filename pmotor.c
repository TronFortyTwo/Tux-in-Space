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

void Pmotor (tsys *sys) {
	
		// Counters for loops
		int i, l;
		// Distance between objects, and his ortogonal components
		long double dist, distx, disty, distz;
		// Tempoany variables
		long double temp1, temp2, temp3;
		
		// Gravity force
		// a loop that operate var active for var active
		for(i=0; i!=sys->nactive; i++) {
			// a loop that consider every planet (i+1 because whit l<i is alredy made, and whit i=l the two objects are the same)
			for (l=i+1; l!= sys->nactive; l++) {
				// First: must be individuated the baricenter of the sistem of obj i and obj (see Information.txt at the voice Pmotor)
				distx = sys->o[i].x - sys->o[l].x;
				disty = sys->o[i].y - sys->o[l].y;
				distz = sys->o[i].z - sys->o[l].z;
				dist  = pow ( (distx*distx + disty*disty + distz*distz) , 1/3);
				// individuate the intensity of acceleration
				temp1 = (sys->o[i].mass * sys->o[l].mass * sys->G) / (dist*dist);
				// for the calculate of the module F of i, I use this:		x : intensity of attraction = mass l : (mass i + mass l)  ||| then, x = (mass l * intensity of attraction) /intensity of attraction
				temp2 = sys->o[l].mass * temp1 / ( sys->o[l].mass + sys->o[i].mass );
				// then the same thing, turning the number (for l)
				temp3 = sys->o[i].mass * temp1 / ( sys->o[l].mass + sys->o[i].mass);
				// now sum the vel [i] whit:		number to sum [i] : distx = vector(temp2) : dist		then repeate for others coordinates
				sys->o[i].velx = sys->o[i].velx + temp2 * distx / dist;
				sys->o[i].vely = sys->o[i].vely + temp2 * disty / dist;
				sys->o[i].velz = sys->o[i].velz + temp2 * distz / dist;
				sys->o[l].velx = sys->o[l].velx + temp3 * distx / dist;
				sys->o[l].vely = sys->o[l].vely + temp3 * disty / dist;
				sys->o[l].velz = sys->o[l].velz + temp3 * distz / dist;
			}
		}
		// move the objects
		for (i=0; i!=sys->nactive; i++) {
			sys->o[i].x = (sys->o[i].x + sys->o[i].velx) * sys->precision ;
			sys->o[i].y = (sys->o[i].y + sys->o[i].vely) * sys->precision ;
			sys->o[i].z = (sys->o[i].z + sys->o[i].velz) * sys->precision ;
			}
	
		// update the time
		for(sys->millisec=sys->precision*1000; sys->millisec>=1000; ) {
			sys->sec++;
			sys->millisec=sys->millisec-1000;
		}
		for(; sys->sec>=60; ) {
			sys->min++;
			sys->sec=sys->sec-60;
		}
		for(; sys->min>=60; ) {
			sys->hour++;
			sys->min=sys->min-60;
		}
		for(; sys->hour>=24; ) {
			sys->day++;
			sys->hour=sys->hour-24;
		}
		for(; sys->day>=365;) {
			sys->year++;
			sys->day=sys->day-365;
		}
		
		
		return;
		}
