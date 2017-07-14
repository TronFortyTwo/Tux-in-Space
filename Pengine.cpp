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


// TODO: over an amount of force, the object could have side effects
void PEntity::Simulation(const time_raw& delta) {
	
	// apply the force
	if(acc_force > force_sum_tolerance)
	  vel += (acc_force * delta) / mass;
	acc_force.zero();
	
	// move the entity
	pos += vel * delta;
}


bool PEntity::operator== (const PEntity& o){
	return
		(pos == o.pos) &&
		(vel == o.vel) &&
		(acc_force == o.acc_force) &&
		(force_single_tolerance == o.force_single_tolerance) &&
		(force_sum_tolerance == o.force_sum_tolerance) &&
		(mass == o.mass) &&
		(radius == o.radius);
}

bool PEntity::operator!= (const PEntity& o){
	return
		(pos != o.pos) ||
		(vel != o.vel) ||
		(acc_force != o.acc_force) ||
		(force_single_tolerance != o.force_single_tolerance) ||
		(force_sum_tolerance != o.force_sum_tolerance) ||
		(mass != o.mass) ||
		(radius != o.radius);
}
