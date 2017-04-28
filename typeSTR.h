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
 * the big type class
 *  header file
 */

#ifndef typeSTRh
#define typeSTRh

#include "generic.h"
#include "type.h"

class type;
class setting;

// The structure whit all the types

class typeSTR {
	public:
		std::vector<type> t;					// the types
		
		type&	Browse	(const setting&, const std::string&);	// Browse and choose a type (give a title to the page)
		type	*Search	(const std::string&);	// Search a type from the name
		
		// constructor
		typeSTR(signal& result);
};

#endif
