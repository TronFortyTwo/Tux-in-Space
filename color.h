/*
#############################################################################
#    Tux in Space - space exploration game									#
#    Copyright (C) 2016-2017  emanuele.sorce@hotmail.com					#
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
 * In this file there are things correlated whit colors (very few)
 *
 *	HEADER FILE
 */

#ifndef colorh
#define colorh

#include "generic.h"
#include "in.h"
class setting;

class color {
	public:
		unsigned int red;
		unsigned int green;
		unsigned int blue;
		
		void Scan(const setting&, const color&, const color&);	// An interface to create a color using OPS
		bool CheckRange(const color&, const color&);			// Check if the color is in a range of colours given (a color max and a color min)

		bool operator== (const color& c) const;
		bool operator!= (const color& c) const;
		
		color(){
			red = green = blue = 0;
		}
};

#include "OnlyPrintfSystem.h"

#endif
