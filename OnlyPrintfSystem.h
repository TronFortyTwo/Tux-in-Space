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
 * The function OnlyPrintfSystem: print words in a simple behavior that adapts on the value of width and height
 *
 * 	HEADER FILE
 */
#ifndef OPSh
#define OPSh
#include "generic.h"

// global functions
void OPS(char *, void *[]);			// Use it to print things
void OPS_Error(char *, void *[]);	// Use it to signal errors
void OPS_MemLack(char *);			// Call it when you can't alloc more RAM (for example when a malloc return NULL)

#endif