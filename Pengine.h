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
 * see information file for more info
 */

#ifndef PENGINEH
#define PENGINEH

#include "generic.h"
#include "math.h"
#include "time.h"

// The physic entity
// TODO: add orientation, torque and company
class PEntity {
	
	private:
	
		tposition pos;
		tvelocity vel;
		
		tforce acc_force;		// accumuled in the simulation slice
		
		tforce_scalar force_single_tolerance;	// if a force applyed is littler than this is ignored
		tforce_scalar force_sum_tolerance;		// if acc_force is littler than this will not be applyed to the object
	
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
		
		inline void SetFrcSingleTolerance (const tforce_scalar& frc){
			force_single_tolerance = frc;
		}
		
		inline void SetFrcSumTolerance (const tforce_scalar& frc){
			force_sum_tolerance = frc;
		}
	
	public:
	
		inline tforce_scalar FrcSumTolerance() const {
			return force_sum_tolerance;
		}
		
		inline tforce_scalar FrcSingleTolerance() const {
			return force_single_tolerance;
		}
	  
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
			if(force > force_single_tolerance)
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
		
		// Does the two object touch?
		bool touch(const PEntity& e) {
			return Distance(e).length() <= (e.radius + radius);
		}
		
		// Do the simulation for the time slice given
		void Simulation(const time_raw& delta);
		
		inline PEntity(const tposition& _pos, const tvelocity& _vel){
			pos = _pos;
			vel = _vel;
		}
		
		inline PEntity(const tposition& _pos,
			const tvelocity& _vel,
			const tforce_scalar& _tol_single,
			const tforce_scalar& _tol_sum,
			const tmass& _mass,
			const tlength& _radius)
		{
			mass = _mass;
			radius = _radius;
			force_single_tolerance = _tol_single;
			force_sum_tolerance = _tol_sum;
			pos = _pos;
			vel = _vel;
		}
		
		inline PEntity(){};
};

#endif
