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
#include "time.h"

// Pi
#define PI M_PI

#define RadiusestoVolume(x, y) (pow((x * x * x + y * y * y).value(), 1/3.0))

int math_RandomI (int, int);

class tmass;
class tlength;
class tforce;
class timpulse;
class tposition;
class tvelocity;
class tacceleration;
class tarea;
class tvolume;
class tguc;

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
		
		// return the direction of the vector (the same vector with length 1)
		vec3<T> direction() const {
			long double l = length();
			
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
		inline vec3(const vec3<T>& direction, const long double& len) {
			long double ratio = len / direction.length();
			x = direction.x * ratio;
			y = direction.y * ratio;
			z = direction.z * ratio;
		}
		
		// operators
		inline vec3<T> operator+ (const vec3<T>& s) {
			return vec3<T>(s.x+x, s.y+y, s.z+z);
		}
		inline vec3<T> operator- (const vec3<T>& s) {
			return vec3<T>(s.x-x, s.y-y, s.z-z);
		}
		inline vec3<T> operator- (void) {
			return vec3<T>(-x, -y, -z);
		}
		inline vec3<T> operator* (const long double& m) const {
			return vec3<T>(x*m, y*m, z*m);
		}
		inline vec3<T> operator/ (const long double& d) const {
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
		inline void operator *= (const long double& s){
			x *= s;
			y *= s;
			z *= s;
		}
};


//
// Classes about physiscal quantities
//

class tlength {
	// unit = kilometre
	
	protected:
		long double m;
	
	public:

		inline void operator= (const long double& _m) {
			m = _m;
		}
		inline void operator-= (const tlength& l) {
			m -= l.m;
		}
		inline void operator+= (const tlength& l) {
			m += l.m;
		}
		inline tlength operator+ (const tlength& l) const {
			return tlength(m + l.m);
		}
		inline tlength operator- (const tlength& l) const {
			return tlength(m - l.m);
		}
		inline bool operator== (const tlength& l) const {
			if (l.m == m)
				return true;
			return false;
		}
		inline void operator>> (std::ostream& s){
			s << std::to_string(m);
		}
		inline bool operator> (const tlength& t) const {
			if (m > t.m)
				return true;
			return false;
			
		}
		inline bool operator< (const tlength& t) const {
			if (m < t.m)
				return true;
			return false;
			
		}
		inline bool operator<= (const tlength& t) const {
			if (m <= t.m)
				return true;
			return false;
			
		}
		inline tlength operator* (const long double& n){
			return tlength(m * n);
		}
		tarea operator* (const tlength& l);
		inline long double operator/ (const tlength& l){
			return m/l.m;
		}
		
		inline long double value() const {
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
		
		inline tvolume operator+ (const tvolume& v){
			return tvolume(m + m);
		}
		inline tvolume operator* (const long double& n) {
			return tvolume(m * n);
		}
		inline tvolume operator/ (const long double& n) {
			return tvolume(m / n);
		}
		inline void operator+= (const tvolume& v){
			m += v.m;
		}
		inline void operator-= (const tvolume& v){
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
		
		inline long double value(){
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

class tmass {
	// unit = kilogram^1000
	
	protected:
		double m;
	
	public:
	
		inline void operator= (const tmass& t) {
			m = t.m;
		}
		inline void operator>> (std::ostream& s){
			s << std::to_string(m);
		}
		inline void operator+= (const tmass& t) {
			m += t.m;
		}
		inline void operator*= (const long double& pure) {
			m *= pure;
		}
		inline tmass operator* (const long double& pure) {
			return tmass(m * pure);
		}
		inline long double operator/ (const tmass& t) {
			return m / t.m;
		}
		inline tmass operator+ (const tmass& t) {
			return tmass(m + t.m);
		}
		inline bool operator >(const tmass& t) {
			if(m > t.m)
				return true;
			return false;
		}
		inline bool operator <(const tmass& t){
			if(m < t.m)
				return true;
			return false;
		}
		inline long double value() const {
			return m;
		}
		
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
	
	
	private:
		
		vec3<long double> v;
		
	public:
	
		tposition operator/ (const tmass& m);
		inline tpositionmass operator+ (const tpositionmass& pm){
			return tpositionmass(v - pm.v);
		}
		
		inline tpositionmass (const vec3<long double> _v) {
			v = _v;
		}
};



class tposition {

	protected:
		
		vec3<long double> v;

	public:
	
		inline tposition operator- (const tposition& p) {
			return tposition(v - p.v);
		}
		inline void operator+= (const tposition& p) {
			v += p.v;
		}
		inline tpositionmass operator* (const tmass& m){
			return tpositionmass(v * m.m);
		}
		
		inline tlength length() const {
			return tlength(v.length());
		}
		inline long double module() const {
			return v.length();
		}
		inline vec3<long double> direction() const{
			return v.direction();
		}
		inline long double x() { return v.x;}
		inline long double y() { return v.y;}
		inline long double z() { return v.z;}
		
		inline tposition(const vec3<long double>& _v){
			v = _v;
		}
		inline tposition(){
			v.zero();
		}
		
};



class tspeed {
	
	private:
		long double m;
	
	public:
		inline tspeed (const long double& _m){
			m = _m;
		}
	
	friend tvelocity;
};



class tvelocity {
	
	private:
		vec3<long double> v;
	
	public:
	
		inline void operator+= (const tvelocity& t){
			v += t.v;
		}
		inline tposition operator* (const time_raw& t) {
			return tposition(v * t.time());
		}
		inline tspeed speed(){
			return tspeed(v.length());
		}
		timpulse operator* (const tmass& m);
		
		inline long double x() { return v.x;}
		inline long double y() { return v.y;}
		inline long double z() { return v.z;}
		
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


class tacceleration_scalar {
	private:
		
		long double m;
	
	public:
	
		inline tacceleration_scalar(const long double& a){
			m = a;
		}
	
	friend tacceleration;
};



class tacceleration {
	
	private:
		vec3<long double> v;
		
	public:
	
		tforce operator* (const tmass& m) const; 
		
		inline long double value() {
			return v.length();
		}
				
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



class timpulse {
	// Kg m / s
	
	private:
		vec3<long double> v;
		
	public:
	
		inline tvelocity operator/ (const tmass& m) {
			return tvelocity(v / m.value());
		}
		inline timpulse operator+ (const timpulse& i){
			return timpulse(v + i.v);
		}
	
		inline timpulse(){
			v.zero();
		}
		inline timpulse(const vec3<long double>& m){
			v = m;
		}
};



class tforce {
	
	private:
		vec3<long double> v;
	
	public:
	
		inline tforce operator+ (const tforce& f) {
			return tforce(v + f.v);
		}
		inline tforce operator- (const tforce& f) {
			return tforce(v - f.v);
		}
		inline void operator+= (const tforce& f) {
			v += f.v;
		}
		inline tforce operator* (const long double& pure){
			return tforce(v * pure);
		}
		inline tacceleration operator/ (const tmass& m) {
			return tacceleration(v / m.value());
		}
		inline timpulse operator* (const time_raw& t){
			return timpulse(v * t.time());
		}
		inline tforce operator- (void){
			return tforce(-v);
		}
		
		inline void zero() {
			v.zero();
		}
		inline long double value(){
			return v.length();
		}
		
		inline tforce(const vec3<long double>& _v) {
			v = _v;
		}
		inline tforce(const vec3<long double>& dir, const long double& len) {
			v = vec3<long double>(dir, len);
		}
		inline tforce() {
			v.zero();
		}
		inline tforce(const tacceleration& a, const tmass& m){
			v = (a * m).v;
		}
};


// about time see time.h

#endif
