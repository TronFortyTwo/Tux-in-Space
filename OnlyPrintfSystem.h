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
 * OnlyPrintfSystem: print words in a simple way, with some nice feature
 *
 * 	HEADER FILE
 */

/*
	ONLY PRINTF SYSTEM API

	todo




*/


#ifndef OPSh
#define OPSh

#include "generic.h"
#include "debug.h"
#include "setting.h"
#include "in.h"

class setting;

// global functions
void OPS		(const setting&, const std::string&);	// Use it to print things
void OPS_Error	(const setting&, const std::string&);	// Use it to signal errors
void OPS_MemLack(const std::string&);					// Call it when you can't alloc more RAM (for example when a malloc return nullptr)

#endif
