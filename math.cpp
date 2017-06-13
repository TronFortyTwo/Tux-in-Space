/*
#############################################################################################
#    Tux in Space - space exploration game													#
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
#include "math.h"

/***
 * Return a "random" int in a range given, but the gap can't be greater than 100
 */
int math_RandomI (int min, int max) {
	srand(time(nullptr));
	return (rand() % (max - min)) + min;
}


tforce tacceleration::operator* (const tmass& m) const{
		return tforce(v * m.m);
};

tmomentum tvelocity::operator* (const tmass& m)  {
	return tmomentum(v * m.m);
}

tposition tpositionmass::operator/ (const tmass& m){
	return tposition(v / m.m);
}

tvolume tarea::operator* (const tlength& l){
	return tvolume(m * l.m);
}

tarea tlength::operator* (const tlength& l){
	return tarea(m * l.m);
}

tforce tguc::newton(const tmass& mass1, const tmass& mass2, const tposition& dist) {
	// apply the newton law of gravitation
	tforce f(
		dist.direction(),
		m * mass1.m * mass2.m / (dist.module() * dist.module())
	);
	return f;
}
