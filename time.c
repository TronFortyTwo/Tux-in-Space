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
 * Time stuff
 */

#include "generic.h"
#include "time.h"

/**
 * The function update time make the time right, for example whitout 72 mins(max mins are 59), 42 hours(max hours are 23)...
 */
void time_Update(ttime *stime) {
	
	while( stime->millisec>=1000 ) {
		stime->sec++;
		stime->millisec -= 1000;
	}
	while( stime->sec >= 60 ) {
		stime->min++;
		stime->sec -= 60;
	}
	while( stime->min >= 60 ) {
		stime->hour++;
		stime->min -= 60;
	}
	while( stime->hour>=24 ) {
		stime->day++;
		stime->hour -= 24;
	}
	while( stime->day >= 365 ) {
		stime->year++;
		stime->day -= 365;
	}
	return;
}
	
/***
 * this function chek which of the time structure given is the farest ( 1 january 2015 is farest than 12 december 1942)
 * return 0 if is the first
 * 		  1 if is the second
 * 		  2 if are =
 * NOTE:
 * the times must is written correctlty (for example not 1024 hour and 71 minutes)
 */
BYTE time_GetBigger(ttime *o, ttime *t) {
	if(o->year > t->year)
		return 0;
	if (o->year < t->year)
		return 1;
	if(o->day > t->day)
		return 0;
	if (o->day < t->day)
		return 1;
	if(o->hour > t->hour)
		return 0;
	if (o->hour < t->hour)
		return 1;
	if(o->min > t->min)
		return 0;
	if (o->min < t->min)
		return 1;
	if(o->sec > t->sec)
		return 0;
	if (o->sec < t->sec)
		return 1;
	if(o->millisec > t->millisec)
		return 0;
	if (o->millisec < t->millisec)
		return 1;
	return 2;
}
