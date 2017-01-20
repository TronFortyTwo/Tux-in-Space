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
 * In this file there are functions that manage types and type.typ file
 * 
 *	(header file)
 */
#ifndef typeh
#define typeh

#include "generic.h"
#include "color.h"
#include "stdio.h"

// The different types of data (coming soon...)
#define DATA_SPACESHIP 0
#define DATA_GENERIC 1

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
		BYTE hunted;			// if is hunted (ON/OFF)
		BYTE hunter;			// if hunts (ON/OFF)
		// BYTE datatype;		// the type of the data the type has (coming  soon)
		// void *data;			// the pointer to the data, his type is defined in datatype
};

#endif
