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
 *This is the motor that emules the phisic law
 * 
 * Now the side effect that this function generated on struct obj are caused by:
 *		-Gravity force
 * 		-Inertia of mass
 *		-impacts beetween them
 */

	void Pmotor (tsys *sys, tinf *inf) {
	
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
				// calculate the axis' distance (always >0)
				distx = sys->o[i].x - sys->o[l].x;
				disty = sys->o[i].y - sys->o[l].y;
				distz = sys->o[i].z - sys->o[l].z;
				// calculate the distance whit pitagora
				dist = sqrtl (distx*distx + disty*disty);
				dist = sqrtl (distz*distz + dist*dist);
				// the force and his ortogonal component
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
				// the aceleration of l
				ax = fx / sys->o[l].mass;
				ay = fy / sys->o[l].mass;
				az = fz / sys->o[l].mass;
				// update the velocity of l
				sys->o[l].velx = sys->o[l].velx + ax * sys->precision;
				sys->o[l].vely = sys->o[l].vely + ay * sys->precision;
				sys->o[l].velz = sys->o[l].velz + az * sys->precision;
				// impact engine
				Impact(sys, inf, i, l, dist);
			}
		}
		// move the objects
		for (i=0; i!=sys->nactive; i++) {
			sys->o[i].x = sys->o[i].x + sys->o[i].velx * sys->precision;
			sys->o[i].y = sys->o[i].y + sys->o[i].vely * sys->precision;
			sys->o[i].z = sys->o[i].z + sys->o[i].velz * sys->precision;
		}
		// update the time
		sys->stime.millisec=sys->precision*1000;
		UpdateTime(&sys->stime);
		
		return;
		}
	
	/**
	 * Impact check and manage impact between objects
	 * for now only merge the two object, but advanced behavior coming soon
	 */
	void Impact (tsys *sys, tinf *inf, int i, int l, long double dist) {
		
		// if the two object don't hit return
		if (sys->o[i].radius + sys->o[l].radius > dist)
			return;
	
		tobj obj;			// the new object
		char name[NAMELUN];	// the new name (the name of the bigger)
		ttype *type;		// the new type (the type of the bigger)
		long double vol;	// the volume of the new object, used to calculate the new radius
		int bigger;			// store i if the bigger is i, else l
		
		// assign the name and the type of the bigger
		if(sys->o[i].mass > sys->o[l].mass) {
			strcpy(name, sys->o[i].name);
			type = sys->o[i].type;
			bigger = i;
		}
		else {
			strcpy(name, sys->o[l].name);
			type = sys->o[l].type;
			bigger = l;
		}
		// the volume is the sum of the two volume V = 4/3 * r^3 * Pi
		vol = ((4/3) * PI * sys->o[l].radius * sys->o[l].radius * sys->o[l].radius) + ((4/3) * PI * sys->o[i].radius * sys->o[i].radius * sys->o[i].radius);
		
		// merge the two previous object
		obj = CreateObject(
			sys->Stype,
			name,
			type,
			sys->o[i].mass + sys->o[l].mass,	// the mass is the sum of the two
			pow((vol * 3)/(4 * PI), 1.0/3),		// V = 4/3 * r^3 * Pi --> (V * 3)/(4 * PI) = r^3
			sys->o[bigger].x,					// x of the bigger
			sys->o[bigger].y,					// y of the bigger
			sys->o[bigger].z,					// z of the bigger
			(sys->o[i].velx * sys->o[i].mass) * (sys->o[l].velx * sys->o[l].mass)/(sys->o[i].mass + sys->o[l].mass),	// smart average
			(sys->o[i].vely * sys->o[i].mass) * (sys->o[l].vely * sys->o[l].mass)/(sys->o[i].mass + sys->o[l].mass),	// smart average
			(sys->o[i].velz * sys->o[i].mass) * (sys->o[l].velz * sys->o[l].mass)/(sys->o[i].mass + sys->o[l].mass)		// smart average
		);
		
		//create the new object in the place of i
		sys->o[i] = obj;
		//move the last object in the place of the place where l was
		sys->o[l] = sys->o[sys->nactive];
		//update counter
		sys->nactive--;
		//if needed, resize the array of objects
		if (sys->nalloc - sys->nactive >= OBJBUFSIZE) {
			ReduceObjBuf(sys, inf);
		}
		
		return;
	}
	
	/**
	 * The function update time make the time right, for example whitout 72 mins, 42 hour...
	 */
	void UpdateTime(ttime *stime){
		for(; stime->millisec>=1000; ) {
			stime->sec++;
			stime->millisec -= 1000;
		}
		for(; stime->sec>=60; ) {
			stime->min++;
			stime->sec -= 60;
		}
		for(; stime->min>=60; ) {
			stime->hour++;
			stime->min -= 60;
		}
		for(; stime->hour>=24; ) {
			stime->day++;
			stime->hour -= 24;
		}
		for(; stime->day>=365;) {
			stime->year++;
			stime->day -= 365;
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
	
