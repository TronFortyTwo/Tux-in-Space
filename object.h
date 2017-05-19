/*
#############################################################################################
#    Tux in Space - space simulator															#
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
#include "typeSTR.h"
#include "in.h"
#include "system.h"
#include "math.h"
#include "Pengine.h"

class type;
class system_c;

class object : public PEntity {
			
	public:
		std::string name;	// the name
		type *typ;			// the type of object
		color colour;

		void 		GetBigger 		(object&, object *&);		// Put the address of the bigger of the two object in the third position
		void 		Save			(const setting&);			// Save the object in a file
		signal 		Read 			(std::ifstream&, typeSTR&);	// Read from a file an object
		signal 		ReadComplete 	(std::ifstream&, typeSTR&);	// Read from a file an object whit coordinates
		void 		Write 			(std::ofstream&);			// Write in a file an object already opened
		void 		WriteComplete	(std::ofstream&);			// Write in a file an object already opened whit coordinates
		
		void 	AI_Hunter 	(system_c&);		// the hunter object will behaviour in the system given
		
		void	Impact_Anaelastic(object&);	// create a new object from an impact with another one
		void	Impact_Hunting(object&);	// "        " " "  "        "  hunting impact (the hunted is given)
		
		inline void Sim (const time_raw& delta){
			Simulation(delta);
		}
		
		
		// CONSTRUCTOR:
		inline object (const std::string& n,
			const PEntity& e,
			type* const& t,
			const color& c)
		{
			(PEntity)*this = e;
			name = n;
			colour = c;
			typ = t;
		}
		object (typeSTR&, const std::string&, signal&);		// Load from a file (UI)
		object (const setting&, typeSTR&, const std::vector<object>& entity, signal&);	// Init using an UI
		object () {;}										// init a free object
		
		friend class system_c;
};

#endif
