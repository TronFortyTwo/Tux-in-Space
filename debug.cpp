/*
#############################################################################
#    CSpace - space simulator												#
#    Copyright (C) 2016-2017 emanuele.sorce@hotmail.com		 				#
#																			#
#    This program is free software; you can redistribute it and/or modify	#
#    it under the terms of the GNU General Public License as published by	#
#    the Free Software Foundation, version 3 or compatibles.				#
#																			#
#    This program is distributed in the hope that it will be useful,		#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of			#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the			#
#    GNU General Public License for more details.							#
#																			#
#    You should have received a copy of the GNU General Public License		#
#    along with this program; if not, write to the Free Software			#
#    Foundation, Inc.														#
#############################################################################
 *
 * In this file there are some debug functions
 * 
 * If you are programming a new function and is buggy, why write debug function from scratch? here there are some optimized, nice and useful 
 * debugging function that you can call from everywhere easily 
 */

#include "debug.h"
#include "object.h"
#include "type.h"
#include "typeSTR.h"

using namespace std;

#if DEBUG

void debug_Init(){
	ofstream file(DEBUG_FILE);
}

/***
 * Print a type
 */
void debug_Type(const type& t) {
	
	debug_Printf("\nName:");
	debug_Printf(t.name);
	debug_Printf("Description:");
	debug_Printf(t.description);
	debug_Printf("Product:");
	debug_Printf(t.product->name);
	debug_Printf("Parent:");
	debug_Printf(t.parent->name);
}

/***
 * Print an int in the debug file
 */
void debug_Int(int n) {
		
	char buffer[32];
	snprintf(buffer, 32, "%d", n);
	debug_Printf(buffer);
}


/***
 * Print a double in the debug file
 */
void debug_Double(double n) {
	
	char buffer[32];
	snprintf(buffer, 32, "%lf", n);
	debug_Printf(buffer);
}

/***
 * Print in the debug file the attributes of an object
 */
void debug_Object(const object& o) {
		
	// a string
	std::string buffer;
	std::ostringstream ob;
		
	// the name
	buffer = "NAME:\t\t\t";
	buffer += o.name;
	debug_Printf(buffer);
	// the mass
	buffer = "MASS:\t\t\t";
	ob << o.mass;
	buffer += ob.str();
	debug_Printf(buffer);
	// the radius
	buffer = "RADIUS:\t\t\t";
	ob << o.radius;
	buffer += ob.str();
	debug_Printf(buffer);
	// the color
	buffer = "COLOR:\t\t\t";
	ob << o.colour.blue << ' ' << o.colour.green << ' ' << o.colour.red;
	buffer += ob.str();
	debug_Printf(buffer);
	// type
	buffer = "TYPE:\t\t\t";
	buffer += o.typ->name;
	debug_Printf(buffer);
	// coordinates
	buffer = "COORDINATES:\t";
	ob << o.pos.x << ' ' << o.pos.y << ' ' << o.pos.z;
	buffer += ob.str();
	debug_Printf(buffer);
	// velocity
	buffer = "VELOCITY:\t";
	ob << o.vel.x << ' ' << o.vel.y << ' ' << o.vel.z;
	buffer += ob.str();
	debug_Printf(buffer);
}

/***
 * This function print the Stype structure
 */
void debug_Stype(const typeSTR& stype) {

	std::string buffer;
		
	debug_Printf("\n\nSTYPE PRINTING -- types found:");
	debug_Int(stype.t.size());
	debug_Printf("\n");
	
	for (unsigned int i=0; i!=stype.t.size(); i++) {
		
		buffer = "NAME:\t\t\t";
		buffer += stype.t[i].name;
		
		buffer += "\nDESCRPTION:\t\t";
		buffer += stype.t[i].description;
		
		buffer += "\nPARENT:\t\t\t";
		buffer += stype.t[i].parent->name;
		
		buffer += "\nMASS MIN:\t\t";
		debug_Printf(buffer);
		debug_Double(stype.t[i].mass_min);
		debug_Printf("MASS MAX:\t\t");
		debug_Double(stype.t[i].mass_max);
		
		debug_Printf("BLUE RANGE\t\t");
		debug_Int(stype.t[i].color_min.blue);
		debug_Int(stype.t[i].color_max.blue);
		
		debug_Printf("GREEN RANGE\t\t");
		debug_Int(stype.t[i].color_min.green);
		debug_Int(stype.t[i].color_max.green);
		
		debug_Printf("RED RANGE\t\t");
		debug_Int(stype.t[i].color_min.red);
		debug_Int(stype.t[i].color_max.red);
		
		buffer = "HUNTED:\t\t\t";
		if (stype.t[i].hunted == true)
			buffer += "YES";
		else
			buffer += "NO";
		
		buffer += "\nHUNTER:\t\t\t";
		if (stype.t[i].hunter == false)
			buffer += "YES";
		else
			buffer += "NO";
		
		buffer += "\nPRODUCT:\t\t";
		buffer += stype.t[i].product->name;
		debug_Printf(buffer);
		debug_Printf("\n");
	}
}

/***
 * This function write in the debug support (a file, stderr or something else) what is called to write
 */
void debug_Printf(const string& txt) {
	
	ofstream file(DEBUG_FILE, ios_base::app);
	if(!file) {
		cout << "\n " IRREGULARITY "  DEBUG BROKEN!! \n";
		return;
	}
	// write what is requested
	file << txt << "\n"; 
}

void debug_Signal(const signal& sig){
	
	switch(sig){
		case signal::aborted:
			debug_Printf("aborted");

		case signal::corrupted:
			debug_Printf("corrupted");

		case signal::create:
			debug_Printf("create");

		case signal::file_err:
			debug_Printf("file error");

		case signal::good:
			debug_Printf("good");
		
		case signal::load:
			debug_Printf("load");
	}
}

#endif
