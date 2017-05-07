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
 *	Low level math functions 
 *	
 * HEADER FILE
 */
#ifndef mathh
#define mathh

#include "generic.h"

// Pi
#define PI M_PI
#define RadiusestoVolume(x, y) (pow(x * x * x + y * y * y, 1/3.0))
int math_RandomI (int, int);

// a vector in the space
template<class T> class vec3 {
	public:
		T x, y, z;
		
		T length();
		
		// absolute value
		inline vec3<T> absolute() {
			return vec3<T>(abs(x), abs(y), abs(z));
		}
		
		inline void zero() {
			x = 0;
			y = 0;
			z = 0;
		}
		
		// return the direction of the vector (the same vector with length 1)
		vec3<T> direction() {
			long double l = length();
			
			return vec3<T>(x/l, y/l, z/l);
		}
		
		// return the greatest axis
		axis3 greatest();
		
		// constructors
		inline vec3(const T& nx, const T& ny, const T& nz){
			x = nx;
			y = ny;
			z = nz;
		}
		inline vec3(){
			x = 0;
			y = 0;
			z = 0;
		}
		inline vec3(const vec3<T>& v){
			*this = v;
		}
		
		// operators
		inline vec3<T> operator+ (const vec3<T>& s) {
			return vec3<T>(s.x+x, s.y+y, s.z+z);
		}
		inline vec3<T> operator- (const vec3<T>& s) {
			return vec3<T>(s.x-x, s.y-y, s.z-z);
		}
		inline vec3<T> operator- (void) {
			return vec3<T>(-x, -y, -z);
		}
		inline vec3<T> operator* (const long double& m) {
			return vec3<T>(x*m, y*m, z*m);
		}
		inline vec3<T> operator/ (const long double& d) {
			return vec3<T>(x/d, y/d, z/d);
		}
		inline T& operator[] (axis3 n) {
			if(n == axis3::x)
				return x;
			if(n == axis3::y)
				return y;
			return z;
		}
		inline void operator+= (const vec3<T>& s){
			x += s.x;
			y += s.y;
			z += s.z;
		}
};

// functions implementation
template<class T> T vec3<T>::length() {
	return sqrtl (z*z + pow(sqrtl(x*x + y*y), 2));
}

template<class T> axis3 vec3<T>::greatest(){
	if (x > y) {
		if(x > z)
			return axis3::x;
		else
			return axis3::y;
	}
	else {
		if(y > z)
			return axis3::y;
		else
			return axis3::z;
	}
}


#endif
