/*
#############################################################################
#    CSpace - space simulator												#
#    Copyright (C) 2016  emanuele.sorce@hotmail.com							#
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
 * In this file there are some debug functions
 * 
 *	HEADER FILE
 */

#if DEBUG
#ifndef debugh
#define debugh

#include "type.h"
#include "object.h"

// functions
void debug_Stype(tStype *);		// Print in the debug target a structure tStype given
void debug_Printf(char *);		// Print in the debug target a string
void debug_Init();				// init the debug target
void debug_Object(tobj *);		// Print in the debug target an object
void debug_Int(int);			// Print in the debug target an int number
void DebugDouble(double n);		// Print in the debug target a long double number

#endif
#endif
