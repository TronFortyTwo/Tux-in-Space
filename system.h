/*
#########################################################################################
#    CSpace - space simulator															#
#    Copyright (C) 2016-2017  emanuele.sorce@hotmail.com								#
#																						#
#    This program is free software; you can redistribute it and/or modify				#
#    it under the terms of the GNU General Public License as published by				#
#    the Free Software Foundation, version 3 or compatibles.							#
#																						#
#    This program is distributed in the hope that it will be useful,					#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of						#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						#
#    GNU General Public License for more details.										#
#																						#
#    You should have received a copy of the GNU General Public License					#
#    along with this program; if not, write to the Free Software						#
#    Foundation, Inc.																	#
#########################################################################################
 *
 * Here we have functions that manage objects
 * 
 * 	(header file)
 */

#ifndef systemh
#define systemh

#include "generic.h"
#include "object.h"
#include "type.h"
#include "time.h"
#include "debug.h"
#include "math.h"

class typeSTR;
class object;

// system structure
class system_c {
	public:
		std::string name;
		time_sim stime;			// the time of the simulation
		std::vector<object> o;	// the object vector
		tguc G;				// the universal gravitation constant
		typeSTR *stype;			// The pointer at the structure that contein all the types
		time_raw precision;		// Precision of the simulation
		
		object *SearchObj	(const std::string&);	// Search for an object in the system from his name
		void RemoveObj 		(object&);				// Remove an object from a system
		void Save			(const setting& set);	// Save an object in a file
		signal NewObj		(const setting& set);	// Create a new object, put it in the system and initialize it
		
		// old pengine
		void Physic	(time_sim& dest);		// Apply the physic to the object
		
		// constructor
		system_c (const setting&, typeSTR&);			// Init the system
		system_c (const setting&, typeSTR&, signal&);	// Init the system loading it from a file
		system_c () = default;
	
	private:
	
		// internal functions
		void Physic_Inertia();	// apply the law: inertia
		void Physic_Gravity();	// "     "    " : gravity
		void Hunter_AI	   ();	// activate the hunter AIs and make them influence the system
		void physic_Impacts();	// Compute impacts between objects
		
		void Write(std::ofstream&);					// Write in an already opened ofstream the system
		signal Read(std::ifstream&, std::string&);	// Read in an already opened ofstream the system
};


#endif
