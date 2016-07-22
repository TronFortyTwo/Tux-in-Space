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
 *
 *This is the motor that emules the phisic law
 * 
 * Now the side effect that this function generated on struct obj are caused by:
 *		- Gravity force	
 * 		- Inertia of mass 
 *		- impacts beetween them (WORK IN PROGRESS)
 */
 
	///prototypes of the phisic related functions
	void Gravity(tsys *);
	void Impacts(tsys *, tinf *);
	tobj MergeObject_Impact (tinf *, tobj *, tobj *);
		

	void Pmotor (tsys *sys, tinf *inf) {
		
		DebugPrint(inf, "pmotor");
	
		// Counters for loops
		int i;
		
		// GRAVITY
		Gravity(sys);
		
		// IMPACTS
		Impacts(sys, inf);
		
		// INERTIA
		for (i=0; i!=sys->nactive; i++) {
			sys->o[i].x += sys->o[i].velx * sys->precision;
			sys->o[i].y += sys->o[i].vely * sys->precision;
			sys->o[i].z += sys->o[i].velz * sys->precision;
		}
		
		// TIME
		sys->stime.millisec += sys->precision * 1000;
		UpdateTime(&sys->stime);
		
		return;
	}


	/***
	 * GRAVITY
	 */
	void Gravity(tsys *sys) {
		
		// the force, and his ortogonal components
		long double dist, distx, disty, distz;
		//the force
		long double f;
		//counters
		int i,l;
		
		for(i=0; i < sys->nactive; i++) {
			for (l=i+1; l < sys->nactive; l++) {	
				// calculate the axis' distance
				distx = sys->o[i].x - sys->o[l].x;
				disty = sys->o[i].y - sys->o[l].y;
				distz = sys->o[i].z - sys->o[l].z;
				// calculate the distance whit pitagora
				dist = Pitagora(distx, disty, distz);
				// if dist = 0, is bad. so
				if(dist == 0)
				dist = 0.0000000001;
				// the force and his ortogonal components
				f  = sys->G * sys->o[i].mass * sys->o[l].mass / (dist * dist);
				// fx : f = distx : dist
				// the aceleration for i (F = m * a -> a = F / m)
				// update the velocity of i (V += a * t)
				sys->o[i].velx -= ((f * distx/dist) / sys->o[i].mass) * sys->precision;
				sys->o[i].vely -= ((f * disty/dist) / sys->o[i].mass) * sys->precision;
				sys->o[i].velz -= ((f * distz/dist) / sys->o[i].mass) * sys->precision;
				// fx : f = distx : dist
				// the aceleration for l (F = m * a -> a = F / m)
				// update the velocity of l (V = V + a * t)
				sys->o[l].velx += ((f * distx/dist) / sys->o[l].mass) * sys->precision;
				sys->o[l].vely += ((f * disty/dist) / sys->o[l].mass) * sys->precision;
				sys->o[l].velz += ((f * distz/dist) / sys->o[l].mass) * sys->precision;
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
	 * 	- creation of moon, asteroids and other objects from hits
	 * 	- special hit mechanics depending on the types of the objects
	 */
	void Impacts(tsys *sys, tinf *inf) {
		DebugPrint(inf, "impacts");
		
		// counters for loops
		int i, l;
		// the distance
		long double dist;
		// sys->nactive at the start of the function
		int nactivebefore = sys->nactive;
		
		for(i=0; i < sys->nactive; i++) {
			for (l=0; l < sys->nactive; l++) {
				// if are the same object continue
				if(l == i)
					continue;
				// calculate the distance whit pitagora
				dist = Pitagora (sys->o[i].x - sys->o[l].x, sys->o[i].y - sys->o[l].y, sys->o[i].z - sys->o[l].z);
				// if doesn't hit continue
				if (sys->o[i].radius + sys->o[l].radius < dist)
					continue;
				
				// For now there are only not elastic impacts.
				// write the new object in the first of the two position
				// then move the last object in the last of the two position
				if (i < l) {
					sys->o[i] = MergeObject_Impact (inf, &sys->o[i], &sys->o[l]);
					sys->o[l] = sys->o[sys->nactive-1];
				}
				else {
					sys->o[l] = MergeObject_Impact (inf, &sys->o[i], &sys->o[l]);
					sys->o[i] = sys->o[sys->nactive-1];
				}

				// update counter and if necessary resize the buffer
				sys->nactive--;
				if(sys->nalloc - sys->nactive >= OBJBUFSIZE)
					ReduceObjBuf(sys, inf);
				
				return;
			}
		}
		
		// If some objects are merged, restart to recheck for impact from start
		if (nactivebefore != sys->nactive)
			Impacts(sys, inf);
		
		return;
	}

	/***
	 * This function create a new object from the impact of two objects given, and return hit
	 */
	tobj MergeObject_Impact(tinf *inf, tobj *oi, tobj *ol) {
		DebugPrint(inf, "mergeobject_impact");
		
		// the new object
		tobj newobj;
		// variables
		tobj *bigger;
		tobj *smaller;
		
		// an object is bigger if has mass AND radius much bigger, else make the bigger a random one, but whit advantages (see below at the else)
		if ((oi->mass > ol->mass*BIGGER_TOLERANCE) && (oi->radius > ol->radius*BIGGER_TOLERANCE))
			bigger = oi;
		else if ((ol->mass > oi->mass*BIGGER_TOLERANCE) && (ol->radius > oi->radius*BIGGER_TOLERANCE))
			bigger = ol;
		else {
			srand(time(NULL));
			if 		( (rand()/RAND_MAX) > (oi->mass/(ol->mass+oi->mass)) )
				bigger = ol;
			else if ( (rand()/RAND_MAX) < (oi->mass/(ol->mass+oi->mass)) )
				bigger = oi;
			else {
				srand(time(NULL));
				if(rand() > 49)
					bigger = oi;
				else
					bigger = ol;
			}
		}
		//set the smaller
		if(oi == bigger)
			smaller = ol;
		else
			smaller = oi;
		// The new object mantein the name of the bigger. The new object is written in the bigger position
		strcpy(newobj.name, bigger->name);
		// the type is the type of the bigger, so is alredy written
		newobj.type = bigger->type;
		// the color is the average, but considering the radius and the type's range
		newobj.color.blue = ((bigger->color.blue * bigger->radius *COLOR_PREDOMINANCE) + (smaller->color.blue * smaller->radius)) / (bigger->radius*COLOR_PREDOMINANCE + smaller->radius);
		newobj.color.green = ((bigger->color.green * bigger->radius *COLOR_PREDOMINANCE) + (smaller->color.green * smaller->radius)) / (bigger->radius*COLOR_PREDOMINANCE + smaller->radius);
		newobj.color.red = ((bigger->color.red * bigger->radius *COLOR_PREDOMINANCE) + (smaller->color.red * smaller->radius)) / (bigger->radius*COLOR_PREDOMINANCE + smaller->radius);
		
		if(newobj.color.blue > newobj.type->color_max.blue)
			newobj.color.blue = newobj.type->color_max.blue;
		else if(newobj.color.blue < newobj.type->color_min.blue)
			newobj.color.blue = newobj.type->color_min.blue;
		if(newobj.color.red > newobj.type->color_max.red)
			newobj.color.red = newobj.type->color_max.red;
		else if(newobj.color.red < newobj.type->color_min.red)
			newobj.color.red = newobj.type->color_min.red;
		if(newobj.color.green > newobj.type->color_max.green)
			newobj.color.green = newobj.type->color_max.green;
		else if(newobj.color.green < newobj.type->color_min.green)
			newobj.color.green = newobj.type->color_min.green;
		// the mass is the sum
		newobj.mass = oi->mass + ol->mass;
		// the coordinates are the average
		newobj.x = ((oi->x * oi->mass) + (ol->x * ol->mass)) / (ol->mass + oi->mass);
		newobj.y = ((oi->y * oi->mass) + (ol->y * ol->mass)) / (ol->mass + oi->mass);
		newobj.z = ((oi->z * oi->mass) + (ol->z * ol->mass)) / (ol->mass + oi->mass);
		// the velocity is the average
		newobj.velx = ((oi->velx * oi->mass) + (ol->velx * ol->mass)) / (ol->mass + oi->mass);
		newobj.vely = ((oi->vely * oi->mass) + (ol->vely * ol->mass)) / (ol->mass + oi->mass);
		newobj.velz = ((oi->velz * oi->mass) + (ol->velz * ol->mass)) / (ol->mass + oi->mass);
		// to calculate the radius we calculate the volum of the two object, we sum the two and we get the radius of the new volume  V = (4/3) r3 * PI ||| r3 = V * 3/(4*PI)
		newobj.radius = pow(((4/3 * powl(oi->radius, 3) * PI) + (4/3 * powl(oi->radius, 3) * PI)) * 3 / (4 * PI), 1/3);

		return newobj;
	}



  //////////////////////////////////////////////////////////////////////////////////
// THESE ARE MATHEMATICAL AND SYSTEM MANAGER FUNCTION THAT HELP GENERICALLY			//
  //////////////////////////////////////////////////////////////////////////////////



	/***
	 * Pitagoras function calculate a diagonal distance from ortogonal component
	 */
	long double Pitagora(long double a, long double b, long double c){
		long double t = sqrtl (a*a + b*b);	//(t)emp
		return sqrtl (c*c + t*t);
	}
	long double Pitagora2D(long double a, long double b) {
		return sqrtl (a*a + b*b);
	}
	/**
	 * The function update time make the time right, for example whitout 72 mins(max mins are 59), 42 hours(max hours are 23)...
	 */
	void UpdateTime(ttime *stime) {
		
		while( stime->millisec>=1000 ){
			stime->sec++;
			stime->millisec -= 1000;
		}
		
		while( stime->sec >= 60 ){
			stime->min++;
			stime->sec -= 60;
		}
		
		while( stime->min >= 60 ){
			stime->hour++;
			stime->min -= 60;
		}
		
		while( stime->hour>=24 ){
			stime->day++;
			stime->hour -= 24;
		}
		
		while( stime->day >= 365 ){
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
	
