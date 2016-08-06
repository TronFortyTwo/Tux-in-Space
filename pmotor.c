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
 *		- impacts beetween them
 */
 
	void Pmotor (tsys *sys, tinf *inf, ttime dest) {
		
		while (GetBiggerStime (&dest, &sys->stime) == 0) {
		
			// GRAVITY
			Gravity(sys, inf);
		
			// MONSTER IA
			HunterIA(sys, inf);
		
			// IMPACTS
			Impacts(sys, inf);
		
			// INERTIA
			Inertia(sys, inf);
		
			// TIME
			sys->stime.millisec += sys->precision * 1000;
			UpdateTime(&sys->stime);
		}
		return;
	}
	
	/***
	 * INERTIA
	 * the thread manager and the thread function
	 */
	void Inertia(tsys *sys, tinf *inf) {
		
		int i;
		
		for (i=0; i!=sys->nactive; i++) {
			sys->o[i].x += sys->o[i].velx * sys->precision;
			sys->o[i].y += sys->o[i].vely * sys->precision;
			sys->o[i].z += sys->o[i].velz * sys->precision;
		}
		return;
	}

	/***
	 * HunterIA
	 * The monster search for human buildt things and destroy them
	 * 
	 * 		THERE IS MUCH WORK TO DO HERE TO MAKE MONSTERS SMARTER
	 */
	void HunterIA(tsys *sys, tinf *inf) {
		
		// counter
		int i;
		
		// Search the monster
		for(i=0; i!=sys->nactive; i++){
			if(sys->o[i].type->hunter == ON)
				HunterIA_single(sys, inf, &sys->o[i]);
		}
		
		return;
	}
	
	void HunterIA_single(tsys *sys, tinf *inf, tobj *mon) {
		
		// counter
		int i;
		// the list
		tobj **list = (tobj **) malloc(sizeof(tobj *[sys->nactive-1]));
		while (list == NULL) {
			OPSML(inf, "HunterIA");
			list = (tobj **) malloc(sizeof(tobj *[sys->nactive-1]));
		}
		// the number of things to destroy
		int num = 0;
		// the closest object to hunt
		tobj *closest;
		// A temp variable
		long double temp;
		
		//if there is only him, exit
		if(sys->nactive == 1)
			return;
		
		// PART ONE: SEARCH FOR THE CLOSER HUNTABLE OBJECT
		// search for monsters
		for(i=0; i!=sys->nactive; i++) {
			if(sys->o[i].type->hunted == ON) {
				list[num] = &sys->o[i];
				num++;
			}
		}
		// search the closest one: assume that the closest is the first. Then watch the next. If is closer, assume it as closest. Restart
		closest = list[0];
		for(i=1; i!=num; i++)
			if( Pitagora(mon->x-closest->x, mon->y-closest->y, mon->z-closest->z) > Pitagora(mon->x-list[i]->x, mon->y-list[i]->y, mon->z-list[i]->z) )
				closest = list[i];
		
		// PART TWO, FOLLOW THE OBJECT
		// move the hunter in the direction of the closest
		// velx : distance x = vel : distance
		temp = MONSTER_ACCELERATION * sys->precision / Pitagora(mon->x-closest->x, mon->y-closest->y, mon->z-closest->z);
		mon->velx -= (mon->x - closest->x) * temp;
		mon->vely -= (mon->y - closest->y) * temp;
		mon->velz -= (mon->z - closest->z) * temp;
		
		//exit
		free(list);
		return; 
	}

	/***
	 * GRAVITY
	 * 
	 * WARNING: this function is heavy optimized! readability compromised! Refer to the comments
	 */
	void Gravity(tsys *sys, tinf *inf) {
		
		// counters
		int i,l;
		// the dist, and his ortogonal components (the dist variable is also used as temporany variable)
		long double dist, distx, disty, distz, f, temp;
		
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
				// the force is f = G * m1 * m2 / dist^2
				f = sys->G * sys->o[i].mass * sys->o[l].mass / (dist * dist);
				// fx : f = distx : dist
				// the aceleration for i (F = m * a -> a = F / m)
				// update the velocity of i and l(V += a * t)
				temp = f * distx * sys->precision / dist;
				sys->o[i].velx -= temp / sys->o[i].mass;
				sys->o[l].velx += temp / sys->o[l].mass;
				temp = f * disty * sys->precision / dist;
				sys->o[i].vely -= temp / sys->o[i].mass;
				sys->o[l].vely += temp / sys->o[l].mass;
				temp = f * distz * sys->precision / dist;
				sys->o[i].velz -= temp / sys->o[i].mass;
				sys->o[l].velz += temp / sys->o[l].mass;
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
	 * This function simulate a hit when a monster eats a hunted object
	 * 
	 * sys->o[er] is the object huntER
	 * sys->o[ed] is the object huntED
	 */
	void MonsterEat(tinf *inf, tsys *sys, int er, int ed) {
		
		
		return;
	}

	/***
	 * This function create a new object from the impact of two objects given, as they are two liquid balls whit a coesion very very very high
	 */
	tobj MergeObject_Impact(tinf *inf, tobj *oi, tobj *ol) {
		
		// the new object
		tobj newobj;
		// the two objects
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
		newobj.radius = ComputeVolume(oi->radius, ol->radius);

		return newobj;
	}



  //////////////////////////////////////////////////////////////////////////////////
// THESE ARE MATHEMATICAL AND SYSTEM MANAGER FUNCTION THAT HELP GENERICALLY			//
  //////////////////////////////////////////////////////////////////////////////////

	/***
	 * This function compute the radius of a sphere from the radius of two sphere of equal mass if summed
	 *
	 * 	 V = 4 * PI * r^3 / 3
	 * 		|
	 * 		v
	 * 	r^3 = V * 3 / (4 * PI)
	 */
	long double ComputeVolume (long double r1, long double r2) {
		return pow(r1 * r1 * r1 + r2 * r2 * r2, 1.0/3.0);
	}
	 

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
		
		while( stime->millisec>=1000 ) {
			stime->sec++;
			stime->millisec -= 1000;
		}
		while( stime->sec >= 60 ) {
			stime->min++;
			stime->sec -= 60;
		}
		while( stime->min >= 60 ) {
			stime->hour++;
			stime->min -= 60;
		}
		while( stime->hour>=24 ) {
			stime->day++;
			stime->hour -= 24;
		}
		while( stime->day >= 365 ) {
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
		
	/***
	 * the function search object search a object in a system whit a name and return his pointer or NULL if there isn't any object whit that name
	 */
	tobj *SearchObject(tsys *sys, char *name) {
		int i;
		for (i=0; i != sys->nactive; i++)
			if(strcmp(sys->o[i].name, name) == 0)
				return &sys->o[i];
		return NULL;
	}
