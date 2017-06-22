/*
#############################################################################
#    Tux in Space - space exploration game									#
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
#include <iostream>

using namespace std;

void debug_Init(){
	ofstream file(DEBUG_FILE);
	if(!file)
		cout << IRREGULARITY "DEBUG BROKEN!\n\nCan't open debug file";
}

/***
 * Print a type
 */
void debug_Type(const type& t) {
	
	std::string buffer;
	
	buffer = "NAME:\t\t\t";
	buffer += t.name;
		
	buffer += "\nDESCRPTION:\t\t";
	buffer += t.description;
		
	buffer += "\nPARENT:\t\t\t";
	buffer += t.parent->name;
		
	buffer += "\nMASS MIN:\t\t";
	debug_Printf(buffer);
	debug_Double(t.mass_min);
	debug_Printf("MASS MAX:\t\t");
	debug_Double(t.mass_max);
	
	debug_Printf("BLUE RANGE\t\t");
	debug_Int(t.color_min.blue);
	debug_Int(t.color_max.blue);
		
	debug_Printf("GREEN RANGE\t\t");
	debug_Int(t.color_min.green);
	debug_Int(t.color_max.green);
		
	debug_Printf("RED RANGE\t\t");
	debug_Int(t.color_min.red);
	debug_Int(t.color_max.red);
		
	buffer = "HUNTED:\t\t\t";
	if (t.hunted == true)
		buffer += "YES";
	else
		buffer += "NO";
	
	buffer += "\nHUNTER:\t\t\t";
	if (t.hunter == true)
		buffer += "YES";
	else
		buffer += "NO";
		
	buffer += "\nPRODUCT:\t\t";
	buffer += t.product->name;
	
	buffer += "\nMERGE:\t\t\t";
	if (t.merge == false)
		buffer += "NO";
	else
		buffer += "YES";
	debug_Printf(buffer);
	
	debug_Printf("\n");
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
	o.Mass() >> ob;
	buffer += ob.str();
	debug_Printf(buffer);
	// the radius
	buffer = "RADIUS:\t\t\t";
	o.Radius() >> ob;
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
	ob << o.Pos().x().value() << '\n';
	ob << o.Pos().y().value() << '\n';
	ob << o.Pos().z().value() << '\n';
	buffer += ob.str();
	debug_Printf(buffer);
	// velocity
	buffer = "VELOCITY:\t";
	ob << o.Vel().x().value() << '\n';
	ob << o.Vel().y().value() << '\n';
	ob << o.Vel().z().value() << '\n';
	buffer += ob.str();
	debug_Printf(buffer);
}

/***
 * This function print the Stype structure
 */
void debug_Stype(const typeSTR& stype) {
		
	debug_Printf("\n\nSTYPE PRINTING -- types found:");
	debug_Int(stype.t.size());
	
	for (unsigned int i=0; i!=stype.t.size(); i++) {
		debug_Printf(" ");
		debug_Type(stype.t[i]);
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
