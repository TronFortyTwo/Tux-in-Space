/*
#############################################################################
#    Tux in Space - space simulator												#
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

// line
void in_s	(std::string&);					// scan a string with spaces
void in_s	();								// clean the stdin reading a line but without save it anywhere
void in_inline_s(std::string&);				// scan not the whole line but only until the next space

// line in a file
void in_fs	(std::string&, std::istream&);	// scan a line in a file
void in_hfs	(std::string&, std::istream&);	// like in_fs, but jump blank lines and commented lines

// int
int in_i();
int in_inline_i();

// int in a file
int in_fi(std::istream&);

// float
float in_f();

// float in a file
float in_ff(std::istream&);

// double
double in_d();

// double in a file
double in_fd(std::istream&);

// long double
long double in_ld();

// long double in a file
long double in_fld(std::istream&);

// read all the line if there is anything else
void in_clear();

#endif
