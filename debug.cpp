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

using namespace std;


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
	ob << o.posx << ' ' << o.posy << ' ' << o.posz;
	buffer += ob.str();
	debug_Printf(buffer);
	// velocity
	buffer = "VELOCITY:\t";
	ob << o.velx << ' ' << o.vely << ' ' << o.velz;
	buffer += ob.str();
	debug_Printf(buffer);
}

/***
 * This function print the Stype structure
 */
void debug_Stype(const typeSTR& stype) {

	std::string buffer;
	std::ostringstream ob;
		
	debug_Printf("\n\nSTYPE PRINTING -- types found:");
	debug_Int(stype.number);
	debug_Printf("\n");
	
	for (int i=0; i!=stype.number; i++) {
		buffer = "NAME:\t\t\t";
		buffer += stype.t[i].name;
		debug_Printf(buffer);
		buffer = "DESCRPTION:\t\t";
		buffer += stype.t[i].description;
		debug_Printf(buffer);
		buffer = "PARENT:\t\t\t";
		buffer += stype.t[i].parent->name;
		debug_Printf(buffer);
		buffer = "MASS MIN:\t\t";
		ob << stype.t[i].mass_min;
		buffer += ob.str();
		debug_Printf(buffer);
		buffer = "MASS MAX:\t\t";
		ob << stype.t[i].mass_max;
		buffer += ob.str();
		debug_Printf(buffer);
		buffer = "BLUE RANGE\t\t";
		ob << stype.t[i].color_min.blue << "\t\t\t\t" << stype.t[i].color_max.blue;
		buffer += ob.str();
		debug_Printf(buffer);
		buffer = "GREEN RANGE\t\t";
		ob << stype.t[i].color_min.green << "\t\t\t\t" << stype.t[i].color_max.green;
		buffer += ob.str();
		debug_Printf(buffer);
		buffer = "RED RANGE\t\t";
		ob << stype.t[i].color_min.red << "\t\t\t\t" << stype.t[i].color_max.red;
		buffer += ob.str();
		debug_Printf(buffer);
		buffer = "HUNTED:\t\t\t";
		if (stype.t[i].hunted == YES)
			buffer += "YES";
		else
			buffer += "NO";
		debug_Printf(buffer);
		buffer = "HUNTER:\t\t\t%p\t\t";
		if (stype.t[i].hunter == YES)
			buffer += "YES";
		else
			buffer += "NO";
		debug_Printf(buffer);
		buffer = "PRODUCT:\t\t%s";
		buffer += stype.t[i].product->name;
		debug_Printf(buffer);
		debug_Printf("\n");
	}
}

/***
 * This function write in the debug support (a file, stderr or something else) what is called to write
 */
void debug_Printf(const string& txt) {
	
	// for now the debug support is a file
	ofstream file(DEBUG_FILE);
	// write what is requested (whit a '\n' after)
	file << txt << endl; 
}
