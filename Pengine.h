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
#include "time.h"

// The physic entity
// TODO: add orientation, torque and other angular datas
class PEntity {
	
	private:
	
		tposition pos;
	
		tvelocity vel;
		
		tforce acc_force;	// accumuled in the simulation slice
	
		tmass mass;
	
		tlength radius;
	
	protected:
		
		inline void SetMass(tmass m) {
			mass = m;
		}
	
		inline void SetRadius(tlength r) {
			radius = r;
		}
	
		inline void SetPos(const tposition& _pos){
			pos = _pos;
		}
		
		inline void SetVel(const tvelocity& _vel){
			vel = _vel;
		}
	
	public:
	
		inline tmass Mass() const {
			return mass;
		}
		
		inline tlength Radius() const {
			return radius;
		}
		
		inline tposition Pos() const {
			return pos;
		}
		
		inline tvelocity Vel() const {
			return vel;
		}
		
		// add a force to the entity
		inline void AddForce(const tforce& force){
			acc_force += force;
		}
		
		// Move all the stats about position and kinematic elements to a dest PEntity
		inline void MoveKinematic(PEntity& destination){
			destination.pos = pos;
			destination.vel = vel;
			destination.acc_force = acc_force;
		}
		
					
		inline tposition Distance(const PEntity& e) {
			return tposition(pos - e.pos);
		}
		
		// Do the simulation for the time slice given
		void Simulation(const time_raw& delta);
		
		inline PEntity(const tposition& _pos, const tvelocity& _vel){
			mass = 0.0;
			radius = 0.0;
			pos = _pos;
			vel = _vel;
		}
		
		inline PEntity(const tposition& _pos,
			const tvelocity& _vel,
			const tmass& _mass,
			const tlength& _radius)
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
