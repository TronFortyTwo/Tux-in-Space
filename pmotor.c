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
 *		- Gravity force
 * 		- Inertia of mass
 *		- impacts beetween them
 */
 
	///prototypes of the phisic related functions
	void Gravity(tsys *);
	void Impacts(tsys *, tinf *);
	///constant used by Impacts()
	#define BIGGER_TOLERANCE 1.217
	#define COLOR_PREDOMINANCE 1.5
	

	void Pmotor (tsys *sys, tinf *inf) {
	
		// Counters for loops
		int i;
		
		//GRAVITY
		Gravity(sys);
		
		// IMPACTS
		Impacts(sys, inf);
		
		// INERTIA
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


	/***
	 * GRAVITY
	 */
	void Gravity(tsys *sys) {
		
		// the force, and his ortogonal components
		long double dist, distx, disty, distz;
		//the force and his ortogonal component
		long double f;
		//counters
		int i,l;
		
		for(i=0; i!=sys->nactive; i++) {
			for (l=i+1; l!=sys->nactive; l++) {	
				// calculate the axis' distance
				distx = sys->o[i].x - sys->o[l].x;
				disty = sys->o[i].y - sys->o[l].y;
				distz = sys->o[i].z - sys->o[l].z;
				// calculate the distance whit pitagora
				dist = sqrtl (distx*distx + disty*disty);
				dist = sqrtl (distz*distz + dist*dist);
				// if dist = 0, is bad. so
				if(dist == 0)
				dist = 0.000000001;
				// the force and his ortogonal components
				f  = sys->G * sys->o[i].mass * sys->o[l].mass / (dist * dist);
				// fx : f = distx : dist
				// the aceleration for i(F = m * a -> a = F / m)
				// update the velocity of i(V = V + a * t)
				sys->o[i].velx = sys->o[i].velx - ((f * distx / dist) / sys->o[i].mass) * sys->precision;
				sys->o[i].vely = sys->o[i].vely - ((f * disty / dist) / sys->o[i].mass) * sys->precision;
				sys->o[i].velz = sys->o[i].velz - ((f * distz / dist) / sys->o[i].mass) * sys->precision;
				// fx : f = distx : dist
				// the aceleration for l(F = m * a -> a = F / m)
				// update the velocity of l(V = V + a * t)
				sys->o[l].velx = sys->o[l].velx + ((f * distx / dist) / sys->o[l].mass) * sys->precision;
				sys->o[l].vely = sys->o[l].vely + ((f * distx / dist) / sys->o[l].mass) * sys->precision;
				sys->o[l].velz = sys->o[l].velz + ((f * distx / dist) / sys->o[l].mass) * sys->precision;
			}
		}
		return;
	}

	/***
	 * Impacts between object
	 * HERE THERE IS MUCH MUCH MUCH WORK TO DO IT MORE REALISTIC AND ACCURATE
	 * for example:
	 * 	- elastics hits
	 * 	- hit that take time
	 * 	- partial hit
	 * 	- creation of moon, asteroids and others from hits
	 * 	- special hit mechanics depending on the type
	 */
	void Impacts(tsys *sys, tinf *inf) {
		
		// the force, and his ortogonal components
		long double dist, distx, disty, distz;
		//counters for loops
		int i, l;
		//memorize i if the bigger is i, l if the bigger is l
		int bigger;
		int smaller;
		//the new object
		tobj newobj;
		
		for(i=0; i!=sys->nactive; i++) {
			for (l=i+1; l!=sys->nactive; l++) {
				// calculate the axis' distance
				distx = sys->o[i].x - sys->o[l].x;
				disty = sys->o[i].y - sys->o[l].y;
				distz = sys->o[i].z - sys->o[l].z;
				// calculate the distance whit pitagora
				dist = sqrtl (distx*distx + disty*disty);
				dist = sqrtl (distz*distz + dist*dist);
				// if doesn't hit continue
				if (sys->o[i].radius + sys->o[l].radius < dist)
					continue;
				// an object is bigger if has mass AND radius much bigger, else make the bigger a random one, but whit advantages (see below at the else)
				if ((sys->o[i].mass > sys->o[l].mass*BIGGER_TOLERANCE) && (sys->o[i].radius > sys->o[l].radius*BIGGER_TOLERANCE))
					bigger = i;
				else if ((sys->o[l].mass > sys->o[i].mass*BIGGER_TOLERANCE) && (sys->o[l].radius > sys->o[i].radius*BIGGER_TOLERANCE))
					bigger = l;
				else {
					srand(time(NULL));
					if 		( (rand()/RAND_MAX) > (sys->o[i].mass/(sys->o[l].mass+sys->o[i].mass)) )
						bigger = l;
					else if ( (rand()/RAND_MAX) < (sys->o[i].mass/(sys->o[l].mass+sys->o[i].mass)) )
						bigger = i;
					else {
						srand(time(NULL));
						if(rand() > 49)
							bigger = i;
						else
							bigger = l;
					}
				}
				//set the smaller
				if(i == bigger)
					smaller = l;
				else
					smaller = i;
				// The new object mantein the name of the bigger. The new object is written in the bigger position
				strcpy(newobj.name, sys->o[bigger].name);
				// the type is the type of the bigger, so is alredy written
				newobj.type = sys->o[bigger].type;
				// the color is the average, but considering the radius
				sys->o[bigger].color.blue = ((sys->o[bigger].color.blue * sys->o[bigger].radius *COLOR_PREDOMINANCE) + (sys->o[smaller].color.blue * sys->o[smaller].radius)) / (sys->o[bigger].radius*COLOR_PREDOMINANCE + sys->o[smaller].radius);
				sys->o[bigger].color.green = ((sys->o[bigger].color.green * sys->o[bigger].radius *COLOR_PREDOMINANCE) + (sys->o[smaller].color.green * sys->o[smaller].radius)) / (sys->o[bigger].radius*COLOR_PREDOMINANCE + sys->o[smaller].radius);
				sys->o[bigger].color.red = ((sys->o[bigger].color.red * sys->o[bigger].radius *COLOR_PREDOMINANCE) + (sys->o[smaller].color.red * sys->o[smaller].radius)) / (sys->o[bigger].radius*COLOR_PREDOMINANCE + sys->o[smaller].radius);
				// the mass is the sum
				newobj.mass = sys->o[i].mass + sys->o[l].mass;
				// the coordinates are the average
				newobj.x = ((sys->o[i].x * sys->o[i].mass) + (sys->o[l].x * sys->o[l].mass)) / (sys->o[l].mass + sys->o[i].mass);
				newobj.y = ((sys->o[i].y * sys->o[i].mass) + (sys->o[l].y * sys->o[l].mass)) / (sys->o[l].mass + sys->o[i].mass);
				newobj.z = ((sys->o[i].z * sys->o[i].mass) + (sys->o[l].z * sys->o[l].mass)) / (sys->o[l].mass + sys->o[i].mass);
				// the velocity is the average
				newobj.velx = ((sys->o[i].velx * sys->o[i].mass) + (sys->o[l].velx * sys->o[l].mass)) / (sys->o[l].mass + sys->o[i].mass);
				newobj.vely = ((sys->o[i].vely * sys->o[i].mass) + (sys->o[l].vely * sys->o[l].mass)) / (sys->o[l].mass + sys->o[i].mass);
				newobj.velz = ((sys->o[i].velz * sys->o[i].mass) + (sys->o[l].velz * sys->o[l].mass)) / (sys->o[l].mass + sys->o[i].mass);
				// to calculate the radius we calculate the volum of the two object, we sum the two and we get the radius of the new volume  V = (4/3) r3 * PI ||| r3 = V * 3/(4*PI)
				newobj.radius = pow(((4/3 * powl(sys->o[i].radius, 3) * PI) + (4/3 * powl(sys->o[i].radius, 3) * PI)) * 3 / (4 * PI), 1/3);
				
				//write the new object in the place of i
				sys->o[i] = newobj;
				//move the last object in the place of l
				sys->o[l] = sys->o[sys->nactive-1];
				//update counter and if necessary resize the buffer
				sys->nactive--;
				if(sys->nalloc - sys->nactive >= OBJBUFSIZE)
					ReduceObjBuf(sys, inf);
			}
		}
		return;
	}

	/**
	 * The function update time make the time right, for example whitout 72 mins(max mins are 59), 42 hours(max hours are 23)...
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
	 * this function chek which of the time structure given is the farest ( 1 january 2015 is farest than 12 december 1942)
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
	
