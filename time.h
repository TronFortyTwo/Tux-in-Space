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
	
	private:
		int year;
		int day;
		int hour;
		int min;
		float sec;
	
		void Sync();
	
	public:
	
		inline const int& Year(){
			return year;
		}
		inline const int& Day(){
			return day;
		}
		inline const int& Hour(){
			return hour;
		}
		inline const int& Minute(){
			return min;
		}
		inline const float& Second(){
			return sec;
		}
		
		inline void AddSec(float s){
			sec += s;
			Sync();
		}
		
		BYTE Compare(const time_sim&);	// return 0 if the given is bigger 1 if is smaller and 2 if are equal
		
		time_sim operator+ (const time_sim& t);
		
		inline time_sim(const time_sim& t) {
			*this = t;
		}
		
		inline time_sim(int nyear, int nday, int nhour, int nmin, float nsec) {
			year = nyear;
			day = nday;
			hour = nhour;
			min = nmin;
			sec = nsec;
			
			Sync();
		}
		
		inline time_sim() {
			year = 0;
			day = 0;
			hour = 0;
			min = 0;
			sec = 0.0;
		}

};
#endif
