/*
#################################################################################
#    CSpace - space simulator													#
#    Copyright (C) 2016-2017  emanuele.sorce@hotmail.com						#
#																				#
#    This program is free software; you can redistribute it and/or modify		#
#    it under the terms of the GNU General Public License as published by		#
#    the Free Software Foundation, version 3 or compatibles.					#
#																				#
#    This program is distributed in the hope that it will be useful,			#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of				#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				#
#    GNU General Public License for more details.								#
#																				#
#    You should have received a copy of the GNU General Public License			#
#    along with this program; if not, write to the Free Software				#
#    Foundation, Inc.															#
#################################################################################
 *
 * Here we have functions that manage objects
 * 
 */

#include "system.h"

using namespace std;

/***
 * This function prepare the object buffer for a new object and initialize it
 */
void system_c::NewObj (const setting& set) {
	
	BYTE result;
	object temp(set, *stype, result);
	if(result == GOOD_SIG)
		o.push_back(temp);
	#if DEBUG
	else {
		if(result == ABORTED_SIG)
			return;
		debug_Printf(IRREGULARITY" system_c::NewObj New object creation failed for");
		debug_Int(result);
	}
	#endif
}

/***
 * This function Delete an object from the system
 */
void system_c::RemoveObj (object& rem) {
	rem = o.back();
	o.pop_back();
}

/***
 * Save a system in the directory Systems/
 */
void system_c::Save(const setting& set){
	
	// the path where the system must be saved, an input variable and the destination file pointer
	std::string path;
	std::string input;
	
	// Write the path
	path = SYSTEM_PATH;
	path += name;
	path += ".sys";
	
	// open the file to read
	ifstream idest(path);
	if(!idest) {
		OPS(set, "While saving: The system you want to save alredy exist.\nDo you want to delete the previous system and save this? [n = no | something else = y]", nullptr);
		in_s(input);
		if(input[0] == 'n')
			return;
	}
	// open the file to write
	ofstream odest(path);
	// Write information about the system
	odest << precision << endl << o.size() << endl << G << endl << stime.year << endl << stime.day << endl << stime.hour << endl << stime.min << endl << stime.sec << endl << stime.millisec << endl;
	// write the system's object's datas
	for(unsigned int i=0; i!=o.size(); i++)
		o[i].WriteComplete(odest);
	
	OPS(set, "SYSTEM SAVED WHIT SUCCESS!\n\nPress something to continue", nullptr);
	sgetchar();
}


/***
 * Initialize a new system
 */
system_c::system_c (const setting& set, typeSTR& s) {
	
	// set the type struct pointer
	stype = &s;
	// set the system's time
	stime.year = 0;
	stime.hour = 0;
	stime.day = 0;
	stime.min = 0;
	stime.sec = 0;
	stime.millisec = 0;
	// set the constant of gravitation. 6.67e-11 (m*m*m)/(Kg*s*s) but whit our units (t, s and Km) is 6.67e-17
	G = 6.67e-17;
	
	// Ask for the name of the new system
	OPS (set, "NEW SYSTEM INITIALIZATION\n\nname of the system:", nullptr);
	// the name
	in_s(name);
	// ask for the precision
	OPS (set, "NEW SYSTEM INITIALIZATION\n\nprecision of the simulation:\n&tdIndicate how much the simulation is precise. A big value mean leess precision but lighter hardware use.\nrecommended values: < 2", nullptr);
	scanf(" %lf", &precision);
}

/**
 * Load a system from a file
 */
system_c::system_c (const setting& set, typeSTR& s, BYTE& result) {

	std::string new_name;	// the name of the system
	std::string path;		// the system file (path)
	int num_obj;
	
	// ask which system
	OPS(set, "LOAD SYSTEM\n\nWhat is the name of the system you want to load?", nullptr);
	in_s(new_name);
	// write the path
	path = SYSTEM_PATH;
	path += new_name;
	path += ".sys";
	// open the file
	ifstream sysf(path);
	if (!sysf) {
		OPS_Error(set, "A system whit that name doesn't exist! Type something to continue and return to the main menu", nullptr);
		sgetchar();
		result = FILE_ERR_SIG;
	}
	// set the name
	name = new_name;
	// scanf system's informations
	sysf >> precision;
	sysf >> num_obj;
	sysf >> G;
	sysf >> stime.year;
	sysf >> stime.day;
	sysf >> stime.hour;
	sysf >> stime.min;
	sysf >> stime.sec;
	sysf >> stime.millisec;
	// alloc memory
	o.resize(num_obj);
	// fscanf for objects datas
	for(int i=0; i!=num_obj; i++) {
		if(o[i].ReadComplete(sysf, s) == CORRUPTED_SIG) {
			#if DEBUG
			debug_Printf("(!) the system to load seem corrupted or outdated! While loading the object (read below):");
			debug_Printf(o[i].name);
			#endif
		}
	}
	stype = &s;
}

/***
 * the function search object search a object in a system whit a name and return his pointer or NULL if there isn't any object whit that name
 */
object *system_c::SearchObj(const string& tofind) {
	for (unsigned int i=0; i != o.size(); i++)
		if(o[i].name.compare(tofind))
			return &o[i];
	return nullptr;
}

// And now, physic!

#define COLOR_PREDOMINANCE 1.35

/****
 * This function will put in the system all the physic laws implemented
 * as long as the time given
 */
void system_c::Physic (time_sim& dest) {
	
	while (!dest.Compare (stime)) {
		
		// GRAVITY
		Physic_Gravity();
		
		// HUNTER IA
		Hunter_AI();
		
		// IMPACTS
		physic_Impacts();
		
		// INERTIA
		Physic_Inertia();
		
		// TIME
		stime.millisec += precision * 1000;
		stime.Update();
	}
}
	
/***
 * INERTIA
 * Move the objects
 */
void system_c::Physic_Inertia() {
	for (unsigned int i=0; i!=o.size(); i++)
		o[i].UpdateFast(precision);
}

/***
 * GRAVITY
 * 
 * WARNING: this function is heavily optimized! readability compromised! Refer to the comments
 */
void system_c::Physic_Gravity() {
		
	// counters
	unsigned int i,l;
	// the dist, and his ortogonal components, the force and a temporany variable
	long double dist, distx, disty, distz, f, temp;
	
	for(i=0; i < o.size(); i++) {
		for (l=i+1; l < o.size(); l++) {
			// calculate the axis' distance
			distx = o[i].posx - o[l].posx;
			disty = o[i].posy - o[l].posy;
			distz = o[i].posz - o[l].posz;
			// calculate the distance whit math_Pitagora3D
			dist = math_Pitagora3D(distx, disty, distz);
			// if dist = 0, is bad. so
			if(!dist)
				dist = 0.0000000001;
			// the force is f = G * m1 * m2 / dist^2
			f = G * o[i].mass * o[l].mass / (dist * dist);
			// fx : f = distx : dist
			// the aceleration for i (F = m * a -> a = F / m)
			// update the velocity of i and l(V += a * t)
			temp = f * distx * precision / dist;
			o[i].velx -= temp / o[i].mass;
			o[l].velx += temp / o[l].mass;
			temp = f * disty * precision / dist;
			o[i].vely -= temp / o[i].mass;
			o[l].vely += temp / o[l].mass;
			temp = f * distz * precision / dist;
			o[i].velz -= temp / o[i].mass;
			o[l].velz += temp / o[l].mass;
		}
	}
}

/***
 * HunterIA
 * The monster search for human buildt things and destroy them
 * 
 * 		THERE IS MUCH WORK TO DO HERE TO MAKE MONSTERS SMARTER
 */
void system_c::Hunter_AI() {
	// Search hunters
	for(unsigned int i=0; i!=o.size(); i++)
		if(o[i].typ->hunter == ON)
			o[i].AI_Hunter(*this);
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
void system_c::physic_Impacts() {
		
	// counter
	unsigned int l;
	// the distance
	long double dist;
	// if has been computed some impact
	BYTE impacts = NO;
	
	for(unsigned int i=0; i < o.size(); i++) {
		for (l=0; l < o.size(); l++) {
			// if are the same object continue
			if(l == i)
				continue;
			dist = o[i].Distance(o[l]);
			// if doesn't hit continue
			if (o[i].radius + o[l].radius < dist)
				continue;
			impacts = YES;
			
			// Call the appropriate impact simulator
			// If is an hunter that hunts an hunted (if the first is an hunter and the second an hunted or viceversa)
			
			if((o[i].typ->hunter == YES) && (o[l].typ->hunted == YES))
				o[i].Impact_Hunting(o[l]);
			else if((o[i].typ->hunted == YES) && (o[l].typ->hunter == YES))
				o[l].Impact_Hunting(o[i]);
				
			// anaelastic impact
			else {
				
				// write the new object in the first of the two position
				// then move the new object in the last of the two position
				if (i < l) {
					o[i].Impact_Anaelastic(o[l]);;
					RemoveObj(o[l]);
				}
				else {	// i > l
					o[l].Impact_Anaelastic(o[i]);
					RemoveObj(o[i]);
				}
			}
		}
	}
	// If some impacts happened, restart to recheck for impact from start
	if (impacts == YES)
		physic_Impacts();
}
