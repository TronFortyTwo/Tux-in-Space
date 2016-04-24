/*
#############################################################################################
#    CSpace - space simulator																#
#    Copyright (C) 2016  emanuele.sorce@hotmail.com											#
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
*/

/***
 * This is CSpace's header file
 * 
 * Contein even the definition of constant
 */

// External standard library
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include <string.h>
	
// Prototype of some function function
	int OPS(tinf *inf, char *, int *, long double *);
	
// CSpace's functions sorted by dependance (so DON'T MODIFY the order if you don't want to fight dozen of gcc's error)
	#include "string functions.c"
	#include "type.c"
	#include "system functions.c"
	#include "mathematical functions.c"
	#include "OnlyPrintfSystem.c"
	#include "OPSo.c"
	#include "menù.c"
	#include "pmotor.c"
	#include "Parser.c"
	#include "shell.c"

