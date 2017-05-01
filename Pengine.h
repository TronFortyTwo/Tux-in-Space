/*
#############################################################################
#    CSpace - space simulator												#
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
 * see information file for more info
 */

#ifndef PENGINEH
#define PENGINEH

#include "generic.h"
#include "math.h"

// The physic entity
// TODO: add orientation, torque and other angular datas

class PEntity {
	
	private:
	
		vec3<long double> pos;	// position
	
		vec3<long double> vel;	// velocity
		
		vec3<long double> acc_force;	// force accumuled in the simulation slice [T/s^2]
		
	public:
		
		double mass;
	
		double radius;
		
		// add a force to the entity
		inline void AddForce(const vec3<long double>& force){
			acc_force += force;
		}
		
		// Do the simulation for the time slice given
		void Simulation(const float delta);
		
		inline PEntity(const vec3<long double>& _pos, const vec3<long double>& _vel){
			mass = 0;
			radius = 0;
			pos = _pos;
			vel = _vel;
		}
		
		PEntity(const vec3<long double>& _pos,
			const vec3<long double>& _vel,
			const double& _mass,
			const double& _radius)
		{
			mass = _mass;
			radius = _radius;
			pos = _pos;
			vel = _vel;
		}
};

#endif
