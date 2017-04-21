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
#include "debug.h"

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
};

/* a vector in the plane
template<class T> class vec2{
	public:
		T x, y;
		
		T length();
		
		// absolute value
		inline vec2<T> absolute() {
			return vec2<T>(abs(x), abs(y));
		}
		// return the greatest axis
		signal greatest();
		
		// constructors
		inline vec2(const T& nx, const T& ny){
			x = nx;
			y = ny;
		}
		inline vec2(){
			x = 0;
			y = 0;
		}
		inline vec2(const vec2<T>& v){
			*this = v;
		}
		
		// operators
		inline vec2<T> operator+ (vec2<T> s) {
			return vec2<T>(s.x+x, s.y+y);
		}
		inline vec2<T> operator- (vec2<T> s) {
			return vec2<T>(s.x-x, s.y-y);
		}
		inline vec2<T> operator* (const long double m) {
			return vec2<T>(x*m, y*m);
		}
		inline vec2<T> operator/ (const long double d) {
			return vec2<T>(x/d, y/d);
		}
		inline T& operator[] (axis n) {
			if(n == x)
				return x;
			if(n == y)
				return y;
			
			#if DEBUG
			debug_Printf("Request for wrong element in the vec2 class using the operator[]");
			#endif
			return x;
		}
};
*/

// functions implementation
template<class T> T vec3<T>::length() {
	return sqrtl (z*z + pow(sqrtl(x*x + y*y), 2));
}
/*
template<class T> T vec2<T>::length() {
	return sqrtl (x*x + y*y);
}
*/
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
/*
template<class T> axis vec2<T>::greatest(){
	if (x > y)
		return X_AXIS;
	else
		return Y_AXIS;
}
*/

#endif
