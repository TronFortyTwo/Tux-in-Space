/*
#############################################################################
#    Tux in Space - space exploration game									#
#    Copyright (C) 2016-2017  emanuele.sorce@hotmail.com					#
#																			#
#    This program is free software; you can redistribute it and/or modify	#
#    it under the terms of the GNU General Public License as published by	#
#    the Free Software Foundation, version 3 or compatibles.				#
#																			#
#    This program is distributed in the hope that it will be useful,		#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of			#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the			#
#    GNU General Public License for more details.							#
#																			#
#    You should have received a copy of the GNU General Public License		#
#    along with this program; if not, write to the Free Software			#
#    Foundation, Inc.														#
#############################################################################
 *
 * phisic engine implementation
 */

#include "Pengine.h"

void PEntity::Simulation(const time_raw& delta) {
	
	// apply the force
	if(acc_force > force_sum_tolerance)
	  vel += (acc_force * delta) / mass;
	acc_force.zero();
	
	// move the entity
	pos += vel * delta;
}
