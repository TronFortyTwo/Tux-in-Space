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
 * This is the motor that emules the phisic law
 * 
 * Now the side effect that this function generated on struct obj are caused by:
 *		-Gravity force
 * 		-Inertia of mass
 *
 */

	void Pmotor (tsys *sys) {
	
		// Counters for loops
		int i, l;
		// Distance between objects, and his ortogonal components
		long double dist, distx, disty, distz;
		// the force
		long double f, fx, fy, fz;
		// the aceleration
		long double ax, ay, az;
		
		// Gravity force
		// a loop that operate var active for var active
		for(i=0; i!=sys->nactive; i++) {
			// a loop that consider every planet (i+1 because whit l<i is alredy made, and whit i=l the two objects are the same)
			for (l=i+1; l!= sys->nactive; l++) {
				//calculate the axis' distance (always >0)
				distx = sys->o[i].x - sys->o[l].x;
				disty = sys->o[i].y - sys->o[l].y;
				distz = sys->o[i].z - sys->o[l].z;
				//calculate the distance whit pitagora
				dist = sqrtl (distx*distx + disty*disty);
				dist = sqrtl (distz*distz + dist*dist);
				//the force and his ortogonal component
				f  = sys->G * sys->o[i].mass * sys->o[l].mass / (dist * dist);
				fx = f * distx / dist;		// fx : f = distx : dist
				fy = f * disty / dist;
				fz = f * distz / dist;
				// the aceleration of i(F = m * a -> a = F / m)
				ax = fx / sys->o[i].mass;
				ay = fy / sys->o[i].mass;
				az = fz / sys->o[i].mass;
				// update the velocity of i
				sys->o[i].velx = sys->o[i].velx + ax * sys->precision;
				sys->o[i].vely = sys->o[i].vely + ay * sys->precision;
				sys->o[i].velz = sys->o[i].velz + az * sys->precision;
				//the aceleration of l
				ax = fx / sys->o[l].mass;
				ay = fy / sys->o[l].mass;
				az = fz / sys->o[l].mass;
				// update the velocity of l
				sys->o[l].velx = sys->o[l].velx + ax * sys->precision;
				sys->o[l].vely = sys->o[l].vely + ay * sys->precision;
				sys->o[l].velz = sys->o[l].velz + az * sys->precision;
			}
		}
		// move the objects
		for (i=0; i!=sys->nactive; i++) {
			sys->o[i].x = sys->o[i].x + sys->o[i].velx * sys->precision;
			sys->o[i].y = sys->o[i].y + sys->o[i].vely * sys->precision;
			sys->o[i].z = sys->o[i].z + sys->o[i].velz * sys->precision;
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
	
	
	
	
	
