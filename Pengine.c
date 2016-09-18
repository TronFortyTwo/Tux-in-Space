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
 * This is the engine that emules the phisic law
 * 
 * Now the side effect that this function generated on objects are caused by:
 *		- Gravity force
 * 		- Inertia of mass
 *		- impacts beetween them
 * 		- 'Intelligence' of the hunters
 */
 
#include "CS_header.h"
 
	void Pengine (tsys *sys, ttime dest) {
		DebugPrint("Pengine");
		
		while (GetBiggerStime (&dest, &sys->stime) == 0) {
		
			// GRAVITY
			Gravity(sys);
		
			// HUNTER IA
			HunterIA(sys);
		
			// IMPACTS
			Impacts(sys);
		
			// INERTIA
			Inertia(sys);
		
			// TIME
			sys->stime.millisec += sys->precision * 1000;
			UpdateTime(&sys->stime);
		}
		return;
	}
	
	/***
	 * INERTIA
	 */
	void Inertia(tsys *sys) {
		
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
	void HunterIA(tsys *sys) {
		
		// counter
		int i;
		
		// Search the monster
		for(i=0; i!=sys->nactive; i++)
			if(sys->o[i].type->hunter == ON)
				HunterIA_single(sys, &sys->o[i]);
		
		return;
	}
	
	void HunterIA_single(tsys *sys, tobj *mon) {
		
		// counter
		int i;
		// an object pointer array
		tobj **list = (tobj **) malloc(sizeof(tobj *[sys->nactive-1]));
		while (list == NULL) {
			OPSML("HunterIA");
			list = (tobj **) malloc(sizeof(tobj *[sys->nactive-1]));
		}
		// the number of things to destroy
		int num = 0;
		// the closest object to hunt
		tobj *closest;
		// A temp variable
		long double temp;
		
		// if there is only him, exit
		if(sys->nactive == 1) {
			free(list);
			return;
		}
		// PART ONE: SEARCH FOR THE CLOSER HUNTABLE OBJECT
		// search for huntable objects
		for(i=0; i!=sys->nactive; i++) {
			if(sys->o[i].type->hunted == ON) {
				list[num] = &sys->o[i];
				num++;
			}
		}
		// if there isn't any huntable object, return
		if (!num) {		// num == 0
			free(list);
			return;
		}
		// search the closest one: assume that the closest is the first. Then watch the next. If is closer, assume it as closest. Restart
		closest = list[0];
		for(i=1; i!=num; i++)
			if( Distance(mon, closest) > Distance(mon, list[i]) )
				closest = list[i];
		
		// PART TWO, FOLLOW THE OBJECT
		// move the hunter in the direction of the closest
		// velx : distance x = vel : distance
		temp = HUNTER_ACCELERATION * sys->precision / Distance(mon, closest);
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
	void Gravity(tsys *sys) {
		
		// counters
		int i,l;
		// the dist, and his ortogonal components, the force and a temporany variable
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
	 * 	- elastics hits (WIP)
	 * 	- hit that take time
	 * 	- partial hit
	 * 	- creation of moon, asteroids, debris and other objects from hits
	 * 	- special hit mechanics depending on the types of the objects (Partial)
	 */
	void Impacts(tsys *sys) {
		
		// counters for loops
		int i, l;
		// the distance
		long double dist;
		// if is been computed some impact
		BYTE impacts = NO;
		
		for(i=0; i < sys->nactive; i++) {
			for (l=0; l < sys->nactive; l++) {
				// if are the same object continue
				if(l == i)
					continue;
				// calculate the distance whit pitagora
				dist = Distance(&sys->o[i], &sys->o[l]);
				// if doesn't hit continue
				if (sys->o[i].radius + sys->o[l].radius < dist)
					continue;
				impacts = YES;
				
				// Call the appropriate impact simulator
				// If is an hunter that hunts an hunted (if the first is an hunter and the second an hunted or viceversa)
				
				if((sys->o[i].type->hunter == YES) && (sys->o[l].type->hunted == YES))
					Hunting_Impact(sys->Stype, &sys->o[l], &sys->o[i]);
				else if((sys->o[i].type->hunted == YES) && (sys->o[l].type->hunter == YES))
					Hunting_Impact(sys->Stype, &sys->o[i], &sys->o[l]);
					
				// regular impact whit merging
				else {
					tobj temp = MergeObject_Impact (&sys->o[i], &sys->o[l]);
					// write the new object in the first of the two position
					// then move the new object in the last of the two position
					if (i < l) {
						MoveObject(&temp, &sys->o[i]);
						MoveObject(&sys->o[--sys->nactive], &sys->o[l]);
					}
					else {
						MoveObject(&temp, &sys->o[l]);
						MoveObject(&sys->o[--sys->nactive], &sys->o[i]);
					}
					UpdateObjBuf(sys);
				}
			}
		}
		// If some impacts happened, restart to recheck for impact from start
		if (impacts == YES)
			Impacts(sys);
	}
	
	/***
	 * This function create a new object from the impact of two objects given, as they are two liquid balls whit a coesion very very very high
	 */
	tobj MergeObject_Impact(tobj *oi, tobj *ol) {
		
		// the new object
		tobj newobj;
		// the two objects
		tobj *bigger;			// the bigger is the object that, relatively, is being hit by the smaller
		tobj *smaller;			// the smaller is the object that fuse whit the bigger and lose personality
		
		// set the bigger and the smaller
		ComputeBigger(oi, ol, &bigger);
		if(oi == bigger)
			smaller = ol;
		else
			smaller = oi;
		// The new object mantein the name of the bigger. The new object is written in the bigger position
		newobj.name = (char *) malloc (sizeof(char[strlen(bigger->name)]));
		strcpy(newobj.name, bigger->name);
		// the type is the type of the bigger
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
		// to calculate the radius we calculate the volum of the two object,
		newobj.radius = RadiusestoVolume(oi->radius, ol->radius);
		
		return newobj;
	}
	
	/***
	 * This function simulate an elastic hit
	 * 
	 * Coming soon!
	 */
	void ElasticImpact(tobj *o, tobj *u) {
	}

	/***
	 * This function simulate when an hunter 'eats' a hunted object
	 * 
	 * sys->o[er] is the object huntER
	 * sys->o[ed] is the object huntED
	 */
	void Hunting_Impact(tStype *Stype, tobj *ed, tobj *er) {
		
		// a random number that is the (p)ercentage that the hunter eats of the hunted /100
		float p;
		// a variable that store the volume of an object
		double volum;
		// a force variable
		long double f;
		// indicate in which direction the hunter is faster
		BYTE faster;
		// the velocity of the hunter in three axis
		long double vx, vy, vz;
		
		// set p (over 50, under 92)
		// over 50 because elsewhere the hunter could collide in the hunted after this impact
		p = (float) RandomInt(50, 92);
		p /= 100.0;
		
		// the hunted one is reduced to his product
		DebugObject(ed);
		ed->type = typeSearchName(Stype, ed->type->product);
		
		// move a percentage p of ed mass in er
		er->mass += ed->mass * p;
		ed->mass -= ed->mass * p;
		
		// decrease the radius of the hunted and increase the rasius of the hunter -- keep in mind that: r^3 = V * 3 / (4 * PI) -- V = 4 * PI * r^3 / 3
		// the hunter volume before
		volum = 4/3 * PI * er->radius * er->radius * er->radius;
		// the hunter volume after
		volum +=  (4/3 * PI * ed->radius * ed->radius * ed->radius) * p;	// volum += volum_eated
		// the hunter radius compute from the new volume
		er->radius = pow(volum * 3 / (4 * PI), 1.0/3.0);
		
		// the hunted volume before
		volum = 4/3 * PI * ed->radius * ed->radius * ed->radius;
		// reduce the hunted volume
		volum -= volum * p;
		ed->radius = pow(volum * 3 / (4 * PI), 1.0/3.0);
		
		// move the hunted a bit away and give him some velocity from the hunter
		// to decrease hunter velocity, launch the hunted in the direction the hunter is going faster
		// We use the absolute value of the velocity
		vx = er->velx;
		if(vx < 0)
			vx = -vx;
		vy = er->vely;
		if(vy < 0)
			vy = -vy;
		vz = er->velz;
		if(vz < 0)
			vz = -vz;
		if (vx > vy) {
			if(vx > vz)
				faster = X_AXIS;
			else
				faster = Z_AXIS;
		}
		else {
			if(vy > vz)
				faster = Y_AXIS;
			else
				faster = Z_AXIS;
		}
		// if x is the fastest
		if(faster == X_AXIS) {
			// move the hunted away from the hunter enought to not touch it
			if(ed->x > er->x)
				ed->x += ed->radius + er->radius + 0.01 + Distance(ed, er);
			else
				ed->x -= ed->radius + er->radius + 0.01 + Distance(ed, er);
			// transimit half of the hunter fast on the hunted (f = m*a)
			f = er->velx * er->mass /2;
			ed->velx = f / ed->mass;
			er->velx /= 2;
			
		}
		// if y is the fastest
		else if(faster == Y_AXIS) {
			// move the hunted away from the hunter enought to not touch it
			if(ed->y > er->y)
				ed->y += ed->radius + er->radius + 0.01 + Distance(ed, er);
			else
				ed->y -= ed->radius + er->radius + 0.01 + Distance(ed, er);
			// transimit half of the hunter fast on the hunted (f = m*a)
			f = er->vely * er->mass /2;
			ed->vely = f / ed->mass;
			er->vely /= 2;
		}
		// if z is the fastest
		else {
			// move the hunted away from the hunter enought to not touch it
			if(ed->z > er->z)
				ed->z += ed->radius + er->radius + 0.01 + Distance(ed, er);
			else
				ed->z -= ed->radius + er->radius + 0.01 + Distance(ed, er);
			// transimit half of the hunter fast on the hunted	(f = m*a)
			f = er->velz * er->mass /2;
			ed->velz = f / ed->mass;
			er->velz /= 2;
		}
	}





  //////////////////////////////////////////////////////////////////////////////////
// THESE ARE MATHEMATICAL AND SYSTEM MANAGER FUNCTION THAT HELP GENERICALLY			//
  //////////////////////////////////////////////////////////////////////////////////
	
	/***
	 * This function compute the distance between the core of two objects
	 */
	long double Distance(tobj *i, tobj *l){
		return Pitagora(i->x - l->x, i->y - l->y, i->z - l->z);
	}

	/***
	 * This function decides which of the two objects given is the bigger
	 * i and l are the two objects,
	 * b the variable address to set = at the bigger
	 */
	void ComputeBigger(tobj *i, tobj *l, tobj **b){
		
		tobj *bigger;	//the bigger
		
		// an object is bigger if has mass much bigger, else make the bigger a random one, but whit advantages (see below at the else)
		if (i->mass > l->mass*BIGGER_TOLERANCE)
			bigger = i;
		else if (l->mass > i->mass*BIGGER_TOLERANCE)
			bigger = l;
		// if no one of the two have the requisites, pick one randomly, but considering the mass
		else {
			srand(time(NULL));
			if 		( (rand()/RAND_MAX) > (i->mass/(l->mass+i->mass)) )
				bigger = l;
			else
				bigger = i;
		}
		//set the bigger and exit
		*b = bigger;
		return; 
	}

	/***
	 * This function compute the radius of a sphere from the radius of two sphere of equal mass if summed
	 *
	 * 	 V = 4 * PI * r^3 / 3
	 * 		|
	 * 		v
	 * 	r^3 = V * 3 / (4 * PI)
	 */
	long double RadiusestoVolume (long double r1, long double r2) {
		return pow(r1 * r1 * r1 + r2 * r2 * r2, 1.0/3.0);
	}
	 

	/***
	 * Pitagora functions calculate a diagonal distance from ortogonal component
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
