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
 *
 *	Time stuff
 *
 * 	HEADER FILE
 */
#ifndef timeh
#define timeh

#include "generic.h"

// the time structure
typedef struct struct_time {
	QWORD year;
	int day;
	int hour;
	int min;
	int sec;
	int millisec;
} ttime;

// function that can be called from everywhere
BYTE time_GetBigger(ttime *, ttime *);				// from two times given, return 0 if the bigger is the first,
													// 1 if id the second and 2 are equal
void time_Update(ttime *);							// Make a wrong formatted time structure into a right one 
													// (for example from 61 sec make 1 min and 1 sec)

#endif