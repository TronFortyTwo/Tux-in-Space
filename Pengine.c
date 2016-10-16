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
 
#include "generic.h"
#include "pengine.h"
#include "time.h"
#include "OnlyPrintfSystem.h"
#include "object.h"
#include "math.h"
#include "system.h"
#include "debug.h"

// internal functions
void pe_Gravity			(tsys *);
void pe_Inertia			(tsys *);
void pe_Impacts			(tsys *);
void pe_HunterIA		(tsys *);
void pe_HunterIA_Single	(tsys *, tobj *);
tobj pe_AnaelasticImpact(tobj *, tobj *);
void pe_HuntingImpact	(tStype *, tobj *, tobj *);
void pe_ElasticImpact	(tobj *, tobj *);

// internal constants
#define COLOR_PREDOMINANCE 1.35
#define HUNTER_ACCELERATION 0.002	// The acceleration of a hunter (Km/s)


/****
 * The main engine function
 */
void Pengine (tsys *sys, ttime dest) {
	
	while (time_GetBigger (&dest, &sys->stime) == 0) {
		
		// GRAVITY
		pe_Gravity(sys);
		
		// HUNTER IA
		pe_HunterIA(sys);
		
		// IMPACTS
		pe_Impacts(sys);
		
		// INERTIA
		pe_Inertia(sys);
		
		// TIME
		sys->stime.millisec += sys->precision * 1000;
		time_Update(&sys->stime);
	}
}
	
/***
 * INERTIA
 * Move the objects
 */
void pe_Inertia(tsys *sys) {
	int i;
	for (i=0; i!=sys->nactive; i++) {
		sys->o[i].x += sys->o[i].velx * sys->precision;
		sys->o[i].y += sys->o[i].vely * sys->precision;
		sys->o[i].z += sys->o[i].velz * sys->precision;
	}
}

/***
 * HunterIA
 * The monster search for human buildt things and destroy them
 * 
 * 		THERE IS MUCH WORK TO DO HERE TO MAKE MONSTERS SMARTER
 */
void pe_HunterIA(tsys *sys) {
	
	// counter
	int i;
		
	// Search the monster
	for(i=0; i!=sys->nactive; i++)
		if(sys->o[i].type->hunter == ON)
			pe_HunterIA_Single(sys, &sys->o[i]);
}
	
void pe_HunterIA_Single(tsys *sys, tobj *mon) {
	
	// counter
	int i;
	// an object pointer array
	tobj **list = (tobj **) malloc(sizeof(tobj *[sys->nactive-1]));
	while (list == NULL) {
		OPS_MemLack("HunterIA");
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
		if( obj_Distance(mon, closest) > obj_Distance(mon, list[i]) )
			closest = list[i];
	
	// PART TWO, FOLLOW THE OBJECT
	// move the hunter in the direction of the closest
	// velx : distance x = vel : distance
	temp = HUNTER_ACCELERATION * sys->precision / obj_Distance(mon, closest);
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
void pe_Gravity(tsys *sys) {
		
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
			// calculate the distance whit math_Pitagora3D
			dist = math_Pitagora3D(distx, disty, distz);
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
void pe_Impacts(tsys *sys) {
		
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
			// calculate the distance whit math_Pitagora3D
			dist = obj_Distance(&sys->o[i], &sys->o[l]);
			// if doesn't hit continue
			if (sys->o[i].radius + sys->o[l].radius < dist)
				continue;
			impacts = YES;
			
			// Call the appropriate impact simulator
			// If is an hunter that hunts an hunted (if the first is an hunter and the second an hunted or viceversa)
			
			if((sys->o[i].type->hunter == YES) && (sys->o[l].type->hunted == YES))
				pe_HuntingImpact(sys->Stype, &sys->o[l], &sys->o[i]);
			else if((sys->o[i].type->hunted == YES) && (sys->o[l].type->hunter == YES))
				pe_HuntingImpact(sys->Stype, &sys->o[i], &sys->o[l]);
				
			// regular impact whit merging
			else {
				tobj temp = pe_AnaelasticImpact (&sys->o[i], &sys->o[l]);
				// write the new object in the first of the two position
				// then move the new object in the last of the two position
				if (i < l) {
					obj_Move(&temp, &sys->o[i]);
					sys_RemoveObj(sys, &sys->o[l]);
				}
				else {
					obj_Move(&temp, &sys->o[l]);
					sys_RemoveObj(sys, &sys->o[i]);
				}
			}
		}
	}
	// If some impacts happened, restart to recheck for impact from start
	if (impacts == YES)
		pe_Impacts(sys);
}
	
/***
 * This function Create a new object from the impact of two objects given, as they are two liquid balls whit a coesion very very very high
 */
tobj pe_AnaelasticImpact(tobj *oi, tobj *ol) {
	
	// the new object
	tobj newobj;
	// the two objects
	tobj *bigger;			// the bigger is the object that, relatively, is being hit by the smaller
	tobj *smaller;			// the smaller is the object that fuse whit the bigger and lose personality
	
	// Low level initialization of newobj
	obj_LowInit(&newobj);
	// set the bigger and the smaller
	obj_MoveBigger(oi, ol, bigger);
	if(oi == bigger)
		smaller = ol;
	else
		smaller = oi;
	// The new object mantein the name of the bigger. The new object is written in the bigger position
	obj_Rename(&newobj, bigger->name);
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
	
	#if DEBUG
	debug_Printf("Anaelastic Impact: Created this new object:");
	debug_Object(&newobj);
	#endif
	
	return newobj;
}
	
/***
 * This function simulate an elastic hit
 * 
 * Coming soon! (I need to study them... ;)
 */
void pe_ElasticImpact(tobj *o, tobj *u) {
}

/***
 * This function simulate when an hunter 'eats' a hunted object
 * 
 * sys->o[er] is the object huntER
 * sys->o[ed] is the object huntED
 */
void pe_HuntingImpact(tStype *Stype, tobj *ed, tobj *er) {
	
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
	p = (float) math_RandomI(50, 92);
	p /= 100.0;
	
	// the hunted one is reduced to his product
	#if DEBUG
	debug_Object(ed);
	#endif
	obj_SetType (ed, Stype, ed->type->product);
	
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
	
	// the hunted volume before (v = 4/3 * PI * r^3)
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
			ed->x += ed->radius + er->radius + 0.01 + obj_Distance(ed, er);
		else
			ed->x -= ed->radius + er->radius + 0.01 + obj_Distance(ed, er);
		// transimit half of the hunter fast on the hunted (f = m*a)
		f = er->velx * er->mass /2;
		ed->velx = f / ed->mass;
		er->velx /= 2;
		
	}
	// if y is the fastest
	else if(faster == Y_AXIS) {
		// move the hunted away from the hunter enought to not touch it
		if(ed->y > er->y)
			ed->y += ed->radius + er->radius + 0.01 + obj_Distance(ed, er);
		else
			ed->y -= ed->radius + er->radius + 0.01 + obj_Distance(ed, er);
		// transimit half of the hunter fast on the hunted (f = m*a)
		f = er->vely * er->mass / 2;
		ed->vely = f / ed->mass;
		er->vely /= 2;
	}
	// if z is the fastest
	else {
		// move the hunted away from the hunter enought to not touch it
		if(ed->z > er->z)
			ed->z += ed->radius + er->radius + 0.01 + obj_Distance(ed, er);
		else
			ed->z -= ed->radius + er->radius + 0.01 + obj_Distance(ed, er);
		// transimit half of the hunter fast on the hunted	(f = m*a)
		f = er->velz * er->mass /2;
		ed->velz = f / ed->mass;
		er->velz /= 2;
	}
}
