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

class time_sim;

// store time just in seconds,
// WARNING! not use for big value of times!!(use time_sim instead)
class time_raw {
	
	private:
		int sec;	// the integer nmumber of seconds
		float fs;	// the fraction of second
	
	public:
	
		inline long long int Sec() const {
			return sec;
		}
		inline long double Time() const {
			return sec + fs;
		}
	
		inline time_raw(long long int _sec, float _fs) {
			sec = _sec;
			fs = _fs;
		}
		inline time_raw(long double f) {
			fs = f;
			while(fs >= 1){		// TODO: optimize here
				sec ++;
				fs --;
			}
		}
		inline time_raw(){
			sec = 0;
			fs = 0.0;
		}
	
	friend time_sim;
};


// the time of a simulation
class time_sim {	
	
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
		
		inline void AddSec(time_raw s){
			sec += s.sec;
			sec += s.fs;
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
		
		inline time_sim(const time_raw& t) {
			sec = t.Time();
			Sync();
			
		}
		
		// transform into time_raw
		time_raw get_Raw();

};

#endif
