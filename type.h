/*
#############################################################################################
#    Tux in Space - space simulator																#
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
 * In this file there are functions that manage types and type.typ file
 * 
 *	(header file)
 */
 
#ifndef typeh
#define typeh

#include "generic.h"
#include "color.h"

// The structure that represent a type of a object
class type {
	public:
		std::string name;
		std::string description;
		
		type *parent;
		type *product;
		
		double mass_min;		// Mass range
		double mass_max;
		
		color color_max;		// Color range
		color color_min;
		
		bool hunted;			// if is hunted
		bool hunter;			// if hunts
};

#endif
