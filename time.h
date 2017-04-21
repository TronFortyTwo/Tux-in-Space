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
	
		inline int Year(){
			return year;
		}
		inline int Day(){
			return day;
		}
		inline int Hour(){
			return hour;
		}
		inline int Minute(){
			return min;
		}
		inline float Second(){
			return sec;
		}
		
		inline void AddSec(float s){
			sec += s;
			Sync();
		}
		
		// Return a string with the time
		std::string String();
		
		comparison Compare(const time_sim&);
		
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
