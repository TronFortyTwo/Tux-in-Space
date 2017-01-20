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
 *	Time stuff
 *
 * 	HEADER FILE
 */

#ifndef timeh
#define timeh

#include "generic.h"

// the time structure
class time_sim {	// the time of a simulation
	public:
		QWORD year;
		int day;
		int hour;
		int min;
		int sec;
		int millisec;
	
		BYTE Compare(time_sim&);	// return 0 if the given is bigger
								// 1 if is smaller and 2 are equal
		void Update();			// format correctly 
								// (for example from 61 sec make 1 min and 1 sec)

};
#endif
