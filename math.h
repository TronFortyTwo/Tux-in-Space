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
 *	Low level math functions 
 *	
 * HEADER FILE
 */
#ifndef mathh
#define mathh

#include "generic.h"
#include "time.h"

// Pi
#define PI M_PI

#define RadiusestoVolume(x, y) (pow((x * x * x + y * y * y).value(), 1/3.0))

int math_RandomI (int, int);

class tspeed;
class tmass;
class tlength;
class tforce;
class tforce_scalar;
class tmomentum;
class tmomentum_scalar;
class tangular_momentum;
class tposition;
class tvelocity;
class tacceleration;
class tarea;
class tvolume;
class tguc;
class tacceleration_scalar;
class tenergy;

// a vector in the space
template<class T> class vec3 {
	public:
		T x, y, z;
		
		T length() const {
			return sqrtl (z*z + pow(sqrtl(x*x + y*y), 2));
		};
		// absolute value
		inline vec3<T> absolute() {
			return vec3<T>(abs(x), abs(y), abs(z));
		}
		inline void zero() {
			x = 0;
			y = 0;
			z = 0;
		}
		// return the project on another vector
		inline vec3<T> projection(const vec3<T>& v) const{
			
		}
		// return the direction of the vector (the same vector with length 1)
		vec3<T> direction() const {
			T l = length();
			return vec3<T>(x/l, y/l, z/l);
		}
		
		// return the greatest axis
		axis3 greatest() const {
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
		};
		
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
		// the vector passing for a point, of a given direction
		inline vec3(const vec3<T>& direction, const T& len) {
			T ratio = len / direction.length();
			x = direction.x * ratio;
			y = direction.y * ratio;
			z = direction.z * ratio;
		}
		
		// operators
		inline vec3<T> operator+ (const vec3<T>& s) const{
			return vec3<T>(s.x+x, s.y+y, s.z+z);
		}
		inline vec3<T> operator- (const vec3<T>& s) const{
			return vec3<T>(s.x-x, s.y-y, s.z-z);
		}
		inline vec3<T> operator- (void) const {
			return vec3<T>(-x, -y, -z);
		}
		inline vec3<T> operator* (const T& m) const {
			return vec3<T>(x*m, y*m, z*m);
		}
		inline vec3<T> operator/ (const T& d) const {
			return vec3<T>(x/d, y/d, z/d);
		}
		inline T& operator[] (axis3 n) {
			if(n == axis3::x)
				return x;
			if(n == axis3::y)
				return y;
			return z;
		}
		inline void operator+= (const vec3<T>& s) {
			x += s.x;
			y += s.y;
			z += s.z;
		}
		inline void operator-= (const vec3<T>& s) {
			x -= s.x;
			y -= s.y;
			z -= s.z;
		}
		inline void operator *= (const T& s){
			x *= s;
			y *= s;
			z *= s;
		}
		inline void operator /= (const T& s){
			x /= s;
			y /= s;
			z /= s;
		}
};

class tspeed {
	// tvelocity scalar
	
	private:
		long double m;
	
	public:
		inline tspeed (const long double& _m){
			m = _m;
		}
		
		long double value() const;
		
		tspeed operator* (const long double& a) const;
		tspeed operator/ (const long double& a) const;
		tspeed operator+ (const tspeed& s) const;
		tspeed operator- (const tspeed& s) const;
		void operator+= (const tspeed& s);
		void operator-= (const tspeed& s);
		tacceleration_scalar operator/ (const time_raw& t) const;
	
	friend tvelocity;
};




//
// Classes about physiscal quantities
//

class tlength {
	// unit = kilometre
	
	protected:
		long double m;
	
	public:

		void operator= (const long double& _m) {
			m = _m;
		}
		void operator-= (const tlength& l) {
			m -= l.m;
		}
		void operator+= (const tlength& l) {
			m += l.m;
		}
		tlength operator+ (const tlength& l) const {
			return tlength(m + l.m);
		}
		tlength operator- (const tlength& l) const {
			return tlength(m - l.m);
		}
		bool operator== (const tlength& l) const {
			if (l.m == m)
				return true;
			return false;
		}
		void operator>> (std::ostream& s){
			s << std::to_string(m);
		}
		bool operator> (const tlength& t) const {
			if (m > t.m)
				return true;
			return false;
			
		}
		bool operator< (const tlength& t) const {
			if (m < t.m)
				return true;
			return false;
			
		}
		inline bool operator<= (const tlength& t) const {
			if (m <= t.m)
				return true;
			return false;
			
		}
		tlength operator* (const long double& n){
			return tlength(m * n);
		}
		tarea operator* (const tlength& l);
		long double operator/ (const tlength& l){
			return m/l.m;
		}
		
		long double value() const {
			return m;
		}
		
		inline tlength(const long double& _m){
			m = _m;
		}
		inline tlength(){
			m = 0;
		}
		
	friend tarea;
};



class tarea {
	
	private:
		long double m;
		
	public:
		
		tvolume operator* (const tlength& l);
			
		inline tarea (const long double& _m){
			m = _m;
		}
};

class tvolume {
	
	private:
		long double m;
		
	public:
		
		tvolume operator+ (const tvolume& v){
			return tvolume(m + m);
		}
		tvolume operator* (const long double& n) {
			return tvolume(m * n);
		}
		tvolume operator/ (const long double& n) {
			return tvolume(m / n);
		}
		void operator+= (const tvolume& v){
			m += v.m;
		}
		void operator-= (const tvolume& v){
			m -= v.m;
		}
		
		inline long double value(){
			return m;
		}
		
		inline tvolume (const long double& _m){
			m = _m;
		}
		inline tvolume (){
			m = 0;
		}
};
class tguc{	// gravitational universal constant (m^3/(Kg*s*s))
	
	private:
		long double m;
		
	public:
		
		long double value(){
			return m;
		}
		// helpful to not starve with dozens of classes
		tforce newton(
			const tmass& mass1,
			const tmass& mass2,
			const tposition& dist
		);
		
		inline tguc(){
			m = 0;
		}
		inline tguc(const long double& _m) {
			m = _m;
		}
};

class tacceleration_scalar {
	private:
		
		long double m;
	
	public:
		tacceleration_scalar operator/ (const long double& n) const;
		tacceleration_scalar operator* (const long double& n) const;
		
		inline long double value() const;
		
		inline tacceleration_scalar(const long double& a){
			m = a;
		}
	
	friend tacceleration;
};


// represent the module of a force
class tforce_scalar{
	private:
		long double m;
		
	public:
		
		long double value() const;
		
		inline tforce_scalar(const long double& _m){
			m = _m;
		}
		inline tforce_scalar(){
			m = 0;
		}
};


class tmomentum_scalar {
	private:
		
		long double m;
	
	public:
	
		tmomentum_scalar operator/ (const long double& n) const;
		tmomentum_scalar operator* (const long double& n) const;
		tmomentum_scalar operator+ (const tmomentum_scalar& s) const;
		tenergy operator* (const tspeed& s) const;
		tforce_scalar operator/ (const time_raw& t) const;
		
		inline tmomentum_scalar(const long double& a){
			m = a;
		}
	
};


class tmass {
	// unit = kilogram^1000
	
	protected:
		double m;
	
	public:
		void operator= (const tmass& t);
		void operator>> (std::ostream& s);
		void operator+= (const tmass& t);
		void operator*= (const long double& pure);
		tmass operator* (const long double& pure) const;
		tforce_scalar operator* (const tacceleration_scalar& a) const;
		tmomentum_scalar operator* (const tspeed& v) const;
		long double operator/ (const tmass& t) const;
		tmomentum operator* (const tvelocity& vel) const;
		tmass operator/ (const long double& n) const;
		tmass operator+ (const tmass& t) const;
		bool operator> (const tmass& t) const;
		bool operator< (const tmass& t) const;
		long double value() const;
		
		inline tmass(){
			m = 0;
		}
		inline tmass(const long double& _m){
			m = _m;
		}
	
	friend class tvelocity;
	friend class tpositionmass;
	friend class tposition;
	friend class tguc;
	friend class tacceleration;
};



class tpositionmass {
	// position * mass
	// TODO: consider if keep this
	
	private:
		
		vec3<long double> v;
		
	public:
	
		tposition operator/ (const tmass& m);
		tpositionmass operator+ (const tpositionmass& pm){
			return tpositionmass(v - pm.v);
		}
		
		tpositionmass (const vec3<long double> _v) {
			v = _v;
		}
};



class tposition {

	protected:
		
		vec3<long double> v;

	public:
	
		tposition operator- (const tposition& p) const;
		void operator+= (const tposition& p);
		tpositionmass operator* (const tmass& m) const;
		tlength scalar() const;
		vec3<long double> direction() const;
		inline tlength x() { return v.x;}
		inline tlength y() { return v.y;}
		inline tlength z() { return v.z;}
		vec3<long double> value() const;
		
		inline tposition(const vec3<long double>& _v){
			v = _v;
		}
		inline tposition(){
			v.zero();
		}
		
};


class tvelocity {
	
	private:
		vec3<long double> v;
	
	public:
	
		void operator+= (const tvelocity& t);
		tposition operator* (const time_raw& t) const;
		tmomentum operator* (const tmass& m) const;
		tvelocity operator+ (const tvelocity& vel) const;
		tvelocity operator- (const tvelocity& vel) const;
		tvelocity operator- (void) const;
		tacceleration operator/ (const time_raw& t) const;
		bool operator< (const tvelocity& vel) const;
		bool operator> (const tvelocity& vel) const;
		
		tspeed x() const { return tspeed(v.x);}
		tspeed y() const { return tspeed(v.y);}
		tspeed z() const { return tspeed(v.z);}
		
		vec3<long double> value() const;
		tspeed scalar() const;
		
		inline tvelocity(const vec3<long double>& _v) {
			v = _v;
		}
		inline tvelocity(){
			v.zero();
		}
		inline tvelocity(vec3<long double> direction, tspeed intensity) {
			v = direction.direction();
			v *= intensity.m;
		}
};


class tacceleration {
	
	private:
		vec3<long double> v;
		
	public:
	
		tforce operator* (const tmass& m) const; 
		
		long double value() const;
				
		inline tacceleration(vec3<long double> _v){
			v = _v;
		}
		inline tacceleration(){
			v.zero();
		}
		inline tacceleration(vec3<long double> direction, tacceleration_scalar intensity) {
			v = direction.direction();
			v *= intensity.m;
		}
		
	friend tforce;
};



class tmomentum {
	// Kg m / s
	
	private:
		vec3<long double> v;
		
	public:
	
		tvelocity operator/ (const tmass& m) const;
		tmomentum operator+ (const tmomentum& i) const;
		tforce operator/ (const time_raw& t) const;
		
		vec3<long double> value() const;
	
		inline tmomentum(){
			v.zero();
		}
		inline tmomentum(const vec3<long double>& m){
			v = m;
		}
};

class tforce {
	
	private:
		vec3<long double> v;
	
	public:
	
		tforce operator+ (const tforce& f) {
			return tforce(v + f.v);
		}
		tforce operator- (const tforce& f) {
			return tforce(v - f.v);
		}
		void operator+= (const tforce& f) {
			v += f.v;
		}
		tforce operator* (const long double& pure){
			return tforce(v * pure);
		}
		tacceleration operator/ (const tmass& m) {
			return tacceleration(v / m.value());
		}
		tmomentum operator* (const time_raw& t){
			return tmomentum(v * t.time());
		}
		tforce operator- (void){
			return tforce(-v);
		}
		bool operator> (const tforce_scalar& f) const {
			return v.length() > f.value();
		}
		bool operator< (const tforce_scalar& f) const {
			return v.length() < f.value();
		}
		
		void zero() {
			v.zero();
		}
		long double value(){
			return v.length();
		}
		
		inline tforce(const vec3<long double>& _v) {
			v = _v;
		}
		inline tforce(const vec3<long double>& dir, const tforce_scalar& f) {
			v = vec3<long double>(dir, f.value());
		}
		inline tforce() {
			v.zero();
		}
		inline tforce(const tacceleration& a, const tmass& m){
			v = (a * m).v;
		}
};

class tangular_momentum {
	// N * m (IS NOT JOULE!!!)
	
	private:
		long double m;
		
	public:
		
		tforce_scalar operator/ (const tlength& l){
			return tforce_scalar(m/l.value());
		}
		
		
		inline tangular_momentum(const long double& n){
			m = n;
		}
		inline tangular_momentum(){
			m = 0;
		}
};

class tenergy {
	// Joule, aka Kg*m^2/s^2
	
	private:
		long double m;
		
	public:
		
		tenergy operator+ (const tenergy& e) const;
		tenergy operator- (const tenergy& e) const;
		
		long double value() const;
		
		inline tenergy (){
			m = 0;
		}
		inline tenergy (const long double& e){
			m = e;
		}
};


// about time see time.h

#endif
