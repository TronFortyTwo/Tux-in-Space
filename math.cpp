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
 * Low level math functions
 *
 */

#include <cstdlib>
#include <cmath>
#include <ctime>

/***
 * This function return a "random" int in a range given, but the gap can't be greater than 100
 */
int math_RandomI (int min, int max) {
	srand(time(nullptr));
	return (rand() % (max - min)) + min;
}

/***
 * math_Pitagora3D functions calculate a diagonal distance from ortogonal component
 */
long double math_Pitagora3D(long double a, long double b, long double c){
	long double t = sqrtl (a*a + b*b);	//(t)emp
	return sqrtl (c*c + t*t);
}

long double math_Pitagora2D(long double a, long double b) {
	return sqrtl (a*a + b*b);
}
