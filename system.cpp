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
	
	signal result;
	object temp(set, *stype, result);
	if(result == signal::good)
		o.push_back(temp);
	#if DEBUG
	else {
		if(result != signal::aborted){
			debug_Printf(IRREGULARITY" system_c::NewObj New object creation failed for");
			debug_Signal(result);
		}
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
 * Initialize a new system
 */
system_c::system_c (const setting& set, typeSTR& s) {
	
	// set the type struct pointer
	stype = &s;
	// set the constant of gravitation. 6.67e-11 (m*m*m)/(Kg*s*s) but whit our units (t, s and Km) is 6.67e-17
	G = 6.67e-17;
	
	// Ask for the name of the new system
	OPS (set, "NEW SYSTEM INITIALIZATION\n\nname of the system:", nullptr);
	// the name
	in_s(name);
	// ask for the precision
	precision = 1;
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
		if(!input.compare("n"))
			return;
	}
	// open the file to write
	ofstream odest(path);
	// Write information about the system
	odest << precision << "\n";
	odest << o.size() << "\n";
	odest << G << "\n";
	odest << stime.Year() << "\n";
	odest << stime.Day() << "\n";
	odest << stime.Hour() << "\n";
	odest << stime.Minute() << "\n";
	odest << stime.Second() << "\n";
	// write the system's object's datas
	for(unsigned int i=0; i!=o.size(); i++)
		o[i].WriteComplete(odest);
	OPS(set, "SYSTEM SAVED WHIT SUCCESS!\n\nPress something to continue", nullptr);
	in_s();
}

/**
 * Load a system from a file
 */
system_c::system_c (const setting& set, typeSTR& str, signal& result) {

	std::string new_name;	// the name of the system
	std::string path;		// the system file (path)
	int num_obj;
	
	result = signal::good;
	
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
		result = signal::file_err;
		return;
	}
	// set the name
	name = new_name;
	// scanf system's informations
	sysf >> precision;
	sysf >> num_obj;
	sysf >> G;
	int y, d, h, m;
	float s;
	sysf >> y;
	sysf >> d;
	sysf >> h;
	sysf >> m;
	sysf >> s;
	stime = time_sim(y, d, h, m, s);
	
	// alloc memory
	o.resize(num_obj);
	// fscanf for objects datas
	for(unsigned int i=0; i!=o.size(); i++) {
		if(o[i].ReadComplete(sysf, str) == signal::corrupted) {
			#if DEBUG
			debug_Printf("(!) the system to load seems corrupted or outdated! While loading the object (read below):");
			debug_Printf(o[i].name);
			#endif
			result = signal::corrupted;
			break;
		}
	}
	stype = &str;
}

/***
 * the function search object search a object in a system whit a name and return his pointer or nullptr if there isn't any object whit that name
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
	
	while (dest.Compare (stime) == comparison::major) {
		
		// GRAVITY
		Physic_Gravity();
		// HUNTER IA
		Hunter_AI();
		// IMPACTS
		physic_Impacts();
		// INERTIA
		Physic_Inertia();
		// TIME
		stime.AddSec(precision);
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
	// the force and a temporany variable
	long double f;
	vec3<long double> temp;
	// the distance
	vec3<long double> dist;
	
	for(i=0; i < o.size(); i++) {
		for (l=i+1; l < o.size(); l++) {
			// calculate the axis' distance
			dist = o[i].pos - o[l].pos;
			// if dist = 0, is bad. so
			if(!dist.length()){
				dist = vec3<long double>(0.000001, 0.000001, 0.000001);
			}	
			// the force is f = G * m1 * m2 / dist^2
			f = G * o[i].mass * o[l].mass / (pow(dist.length(), 2) );
			// fx : f = distx : dist
			// the aceleration for i (F = m * a -> a = F / m)
			// update the velocity of i and l(V += a * t)
			temp = dist * f * precision / dist.length();
			o[i].vel = o[i].vel - (temp / o[i].mass);
			o[l].vel = o[l].vel + (temp / o[l].mass);
			
			//temp = f * dist.x * precision / dist.length();
			//o[i].vel.x -= temp / o[i].mass;
			//o[l].vel.x += temp / o[l].mass;
			//temp = f * dist.y * precision / dist.length();
			//o[i].vel.y -= temp / o[i].mass;
			//o[l].vel.y += temp / o[l].mass;
			//temp = f * dist.z * precision / dist.length();
			//o[i].vel.z -= temp / o[i].mass;
			//o[l].vel.z += temp / o[l].mass;
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
		if(o[i].typ->hunter == true)
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
	// if has been computed some impact
	bool impacts = false;
	
	for(unsigned int i=0; i < o.size(); i++) {
		for (l=0; l < o.size(); l++) {
			// if are the same object continue
			if(l == i)
				continue;
			// if doesn't hit continue
			if (o[i].radius + o[l].radius < o[i].Distance(o[l]))
				continue;
			impacts = true;
			
			// Call the appropriate impact simulator
			// If is an hunter that hunts an hunted (if the first is an hunter and the second an hunted or viceversa)
			
			if((o[i].typ->hunter == true) && (o[l].typ->hunted == true))
				o[i].Impact_Hunting(o[l]);
			else if((o[i].typ->hunted == true) && (o[l].typ->hunter == true))
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
	// If some impacts happened, restart rechecking for impact from start
	if (impacts == true)
		physic_Impacts();
}
