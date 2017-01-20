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
 * Time stuff
 */

#include "time.h"

/**
 * The function update time make the time right, for example whitout 72 mins(max mins are 59), -444 hours...
 * Fields that aren't in the range are corrected putting the extra in the next fields
 * Fields <0 are setted to 0
 */
void time_sim::Update() {
	
	// Over the range
	while( millisec>=1000 ) {
		sec++;
		millisec -= 1000;
	}
	while( sec >= 60 ) {
		min++;
		sec -= 60;
	}
	while( min >= 60 ) {
		hour++;
		min -= 60;
	}
	while( hour>=24 ) {
		day++;
		hour -= 24;
	}
	while( day >= 365 ) {
		year++;
		day -= 365;
	}
}
	
/***
 * this function chek which of the time structure given is the farest ( 1 january 2015 is farest than 12 december 1942)
 * return 0 if is the first
 * 		  1 if is the second
 * 		  2 if are =
 * NOTE:
 * the times must is written correctly (for example not 1024 hour and 71 minutes)
 */
BYTE time_sim::Compare(time_sim& t) {
	if (year > t.year)
		return 0;
	if (year < t.year)
		return 1;
	if (day > t.day)
		return 0;
	if (day < t.day)
		return 1;
	if (hour > t.hour)
		return 0;
	if (hour < t.hour)
		return 1;
	if (min > t.min)
		return 0;
	if (min < t.min)
		return 1;
	if (sec > t.sec)
		return 0;
	if (sec < t.sec)
		return 1;
	if (millisec > t.millisec)
		return 0;
	if (millisec < t.millisec)
		return 1;
	return 2;
}
