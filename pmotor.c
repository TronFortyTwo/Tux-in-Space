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
 */
 /********************************************************************************
 *
 *
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
		// variables
		long double force, temp2, temp3, sum;
		
		// Gravity force
		// a loop that operate var active for var active
		for(i=0; i!=sys->nactive; i++) {
			// a loop that consider every planet (i+1 because whit l<i is alredy made, and whit i=l the two objects are the same)
			for (l=i+1; l!= sys->nactive; l++) {
				// First: must be individuated the baricenter of the sistem of obj i and obj.
				//calculate the axis' distance
				distx = sys->o[i].x - sys->o[l].x;
				disty = sys->o[i].y - sys->o[l].y;
				distz = sys->o[i].z - sys->o[l].z;
				//calculate the distance whit pitagora
				dist = sqrtl(distx*distx + disty*disty);
				dist = sqrtl(distz*distz + dist*dist);
				// individuate the intensity of acceleration (whit the formula F=G*m1*m2/d^2)
				force = (sys->o[i].mass * sys->o[l].mass * sys->G) / (dist*dist);
				// for the calculate of the module F of i, I use this:		x : force = mass l : (mass i + mass l)
				temp2 = (sys->o[l].mass + sys->o[i].mass);
				ResProp(&temp2, &force, &sys->o[l].mass, &temp2, 1);
				// then the same thing for l
				ResProp(&temp3, &force, &sys->o[i].mass, &temp2, 1);
				// now sum the vel [i] whit:		number to sum to i : distx = vector(temp2) : dist		then repeate for others coordinates
				ResProp(&sum, &distx, &temp2, &dist, 1);
				sys->o[i].velx = sys->o[i].velx + sum;
				ResProp(&sum, &disty, &temp2, &dist, 1);
				sys->o[i].vely = sys->o[i].vely + sum;
				ResProp(&sum, &distz, &temp2, &dist, 1);
				sys->o[i].velz = sys->o[i].velz + sum;
				// repeate for l
				ResProp(&sum, &distx, &temp3, &dist, 1);
				sys->o[l].velx = sys->o[l].velx + sum;
				ResProp(&sum, &disty, &temp3, &dist, 1);
				sys->o[l].vely = sys->o[l].vely + sum;
				ResProp(&sum, &distz, &temp3, &dist, 1);
				sys->o[l].velz = sys->o[l].velz + sum;
			}
		}
		// move the objects
		for (i=0; i!=sys->nactive; i++) {
			sys->o[i].x = sys->o[i].x + sys->o[i].velx * sys->precision ;
			sys->o[i].y = sys->o[i].y + sys->o[i].vely * sys->precision ;
			sys->o[i].z = sys->o[i].z + sys->o[i].velz * sys->precision ;
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
		
	/********************************************
	* 
	* The function RESolve PROPortion
	* need the address of the four members and the number of the member to find
	* 
	*/
	
	void ResProp(long double *m1, long double *m2, long double *m3, long double *m4, int x) {
		
		if (x == 1)
			(*m1)=(*m2)*(*m3)/(*m4);
		else if (x == 2)
			(*m2)=(*m1)*(*m4)/(*m3);
		else if (x == 3)
			(*m3)=(*m1)*(*m4)/(*m2);
		else if (x == 4)
			(*m4)=(*m2)*(*m3)/(*m1);
		
		return;
	};
	
	
	
	
	
