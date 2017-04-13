/*
#############################################################################################
#    CSpace - space simulator																#
#    Copyright (C) 2016-2017  emanuele.sorce@hotmail.com									#
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
 *	Object oriented file where Create a "class" object, giving a coerent and fast API to the program
 * 
 * 	all these function have the obj_ prefix.
 * 	You can't modify a object whitout pass throught a obj_ function
 *
 *	HEADER FILE
 */


#ifndef objecth
#define objecth

#include "generic.h"
#include "color.h"
#include "object_data.h"
#include "math.h"
#include "typeSTR.h"
#include "in.h"
#include "system.h"

class type;
class system_c;

class object {
	private:
		void 		WipeData		();							// Wipe the data struct of an object
			
	public:
		objdata data;		// the data about the object
		std::string name;	// the name
		type *typ;			// the type of object
		long double	radius;	// the object for now are sphere
		long double mass;
		vec3<long double> pos;	// position
		vec3<long double> vel;	// velocity
		color colour;

		void 		GetBigger 		(object&, object *&);		// Put the address of the bigger of the two object in the third position
		void 		Save			(const setting&);			// Save the object in a file
		double 		Distance		(const object&);			// Compute the distance between this objects and another one
		BYTE 		Read 			(std::ifstream&, typeSTR&);	// Read from a file an object
		BYTE 		ReadComplete 	(std::ifstream&, typeSTR&);	// Read from a file an object whit coordinates
		void 		Write 			(std::ofstream&);			// Write in a file an object already opened
		void 		WriteComplete	(std::ofstream&);			// Write in a file an object already opened whit coordinates
		void		UpdateFast		(double);					// Update x, y, z of an object accordingly to his fast and the simulation precision
		
		void 	AI_Hunter 	(system_c&);		// the hunter object will behaviour in the system given
		
		void	Impact_Anaelastic(object&);	// create a new object from an impact with another one
		void	Impact_Hunting(object&);	// "        " " "  "        "  hunting impact (the hunted is given)
		
		// CONSTRUCTOR:
		object (typeSTR&, const std::string&, BYTE&);	// Load from a file (UI)
		object (const setting&, typeSTR&, BYTE&);		// Init using an UI
		object () {;}									// init a free object
};

#endif
