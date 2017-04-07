/*
#############################################################################
#    CSpace - space simulator												#
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
 * 
 * Here we have function that help whit input
 * 
 */

#ifndef inh
#define inh

#include "generic.h"

void in_s	(std::string&);					// scan a string with spaces
void in_s	();								// clean the stdin reading a line but without save it anywhere
void in_fs	(std::string&, std::istream&);	// scan as long as a '\n'
void in_hfs	(std::string&, std::istream&);	// like in_fs, but jump blank lines and commented lines

#endif
