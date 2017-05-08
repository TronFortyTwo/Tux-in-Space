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
	
		double mass;
	
		double radius;
	
	protected:
		
		inline void SetMass(double m) {
			mass = m;
		}
	
		inline void SetRadius(double r) {
			radius = r;
		}
	
		inline void SetPos(const vec3<long double>& _pos){
			pos = _pos;
		}
		
		inline void SetVel(const vec3<long double>& _vel){
			vel = _vel;
		}
	
	public:
	
		inline double Mass() const {
			return mass;
		}
		
		inline double Radius() const {
			return radius;
		}
		
		inline vec3<long double> Pos() const {
			return pos;
		}
		
		inline vec3<long double> Vel() const {
			return vel;
		}
		
		// add a force to the entity
		inline void AddForce(const vec3<long double>& force){
			acc_force += force;
		}
		
		// Move all the stats about position and kinematic elements to a dest PEntity
		inline void MoveKinematic(PEntity& destination){
			destination.pos = pos;
			destination.vel = vel;
			destination.acc_force = acc_force;
		}
		
					
		inline vec3<long double> Distance(const PEntity& obj) {
			return vec3<long double>(pos - obj.pos);
		}
		
		// Do the simulation for the time slice given
		void Simulation(const float delta);
		
		inline PEntity(const vec3<long double>& _pos, const vec3<long double>& _vel){
			mass = 0;
			radius = 0;
			pos = _pos;
			vel = _vel;
		}
		
		inline PEntity(const vec3<long double>& _pos,
			const vec3<long double>& _vel,
			const double& _mass,
			const double& _radius)
		{
			mass = _mass;
			radius = _radius;
			pos = _pos;
			vel = _vel;
		}
		
		inline PEntity(){
			mass = 0;
			radius = 0;
		};
};

#endif
