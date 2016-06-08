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
		for(sys->stime.millisec=sys->precision*1000; sys->stime.millisec>=1000; ) {
			sys->stime.sec++;
			sys->stime.millisec -= 1000;
		}
		for(; sys->stime.sec>=60; ) {
			sys->stime.min++;
			sys->stime.sec -= 60;
		}
		for(; sys->stime.min>=60; ) {
			sys->stime.hour++;
			sys->stime.min -= 60;
		}
		for(; sys->stime.hour>=24; ) {
			sys->stime.day++;
			sys->stime.hour -= 24;
		}
		for(; sys->stime.day>=365;) {
			sys->stime.year++;
			sys->stime.day -= 365;
		}
		
		
		return;
		}
	
	/***
	 * this function chek which of the time structure given is the farest ( 1 january 2015 farest than 12 december 1942)
	 * return 0 if is the first
	 * 		  1 if is the second
	 * 		  2 if are =
	 * NOTE:
	 * the times must is written correctlty (for example not 1024 hour and 71 minutes)
	 */
		int GetBiggerStime(ttime *o, ttime *t) {
			if(o->year > t->year)
				return 0;
			if (o->year < t->year)
				return 1;
			if(o->day > t->day)
				return 0;
			if (o->day < t->day)
				return 1;
			if(o->hour > t->hour)
				return 0;
			if (o->hour < t->hour)
				return 1;
			if(o->min > t->min)
				return 0;
			if (o->min < t->min)
				return 1;
			if(o->sec > t->sec)
				return 0;
			if (o->sec < t->sec)
				return 1;
			if(o->millisec > t->millisec)
				return 0;
			if (o->millisec < t->millisec)
				return 1;
			return 2;
		}
	
