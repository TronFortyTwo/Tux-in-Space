/*
#############################################################################################
#    Tux in Space - space simulator															#
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

using namespace std;

/**
 * The function sync time make the time right, for example whitout 72 mins(max mins are 59), -444 hours...
 * Fields that aren't in the range are corrected putting the extra in the next fields
 * Fields <0 are setted to 0
 */
void time_sim::Sync() {
	
	while( sec >= 60.0 ) {
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
 * return major if t is minor
 * 		  minor if t is major
 * 		  else equal
 */
comparison time_sim::Compare(const time_sim& t) {
	if (year > t.year)
		return comparison::major;
	else if (year < t.year)
		return comparison::minor;
	if (day > t.day)
		return comparison::major;
	else if (day < t.day)
		return comparison::minor;
	if (hour > t.hour)
		return comparison::major;
	else if (hour < t.hour)
		return comparison::minor;
	if (min > t.min)
		return comparison::major;
	else if (min < t.min)
		return comparison::minor;
	if (sec > t.sec)
		return comparison::major;
	else if (sec < t.sec)
		return comparison::minor;
	return comparison::equal;
}

// Sum operator
time_sim time_sim::operator+ (const time_sim& t) {
	
	time_sim sum(t.year + year,
				t.day + day,
				t.hour + hour,
				t.min + min,
				t.sec + sec);

	sum.Sync();

	return sum;
}

// Return a string with the current time
string time_sim::String(){
	
	string time = "Year ";
	time += to_string(year);
	time += " day ";
	time += to_string(day);
	time += " | ";
	time += to_string(hour);
	time += ":";
	time += to_string(min);
	time += ":";
	time += to_string(sec);
	
	return time;
}
