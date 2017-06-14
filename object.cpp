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
 *	Object oriented file where Create a "class" object, giving a coerent and fast API to the program
 * 
 * 	all these function have the obj_ prefix
 * 
 */

#include "object.h"

using namespace std;

/***
 * This constructor loads from a file the object
 */
object::object(typeSTR& stype, const string& name, signal& result) {
	
	// From the name, get the file address
	string path;
		
	path = OBJECT_PATH;
	path += name;
	path += ".object";
		
	// open the file
	ifstream file(path);
	if(!file){
		result = signal::file_err;
		debug_Printf(IRREGULARITY" Canno't read the object! File not found!");
		debug_Printf(name);
		return;
	}
		
	// Read the object
	result = Read(file, stype);
}


/***
 * The obj_Save function save a object in a file
 */
void object::Save(const setting& set) {
	
	// the path where the object must be saved, an input variable and the destination file pointer
	string path;
	string input;
	
	// Write the path
	path = OBJECT_PATH;
	path += name;
	path += ".object";
	
	ofstream file(path);
	
	// if the file doesn't exist
	if(!file){
		OPS(set, "While saving: The object you want to save alredy exist.\nDo you want to delete the previous object and save this? [n = no | something else = y]");
		in_s(input);
		if(!input.compare("n"))
			return;
	}
	
	// Write the object
	Write(file);
}



signal object::Read (ifstream& stream, typeSTR& stype) {
	// scan the name
	in_fs(name, stream);
	// scan the type
	string t_name;
	in_fs(t_name, stream);
	typ = stype.Search(t_name);
	if (typ == nullptr)
		return signal::corrupted;
	// scan all the other things
	colour.red = in_fi(stream);
	colour.green = in_fi(stream);
	colour.blue = in_fi(stream);
	SetRadius(in_fld(stream));
	SetMass(in_fld(stream));
	SetFrcSingleTolerance(in_fld(stream));
	SetFrcSumTolerance(in_fld(stream));
	
	return signal::good;
}

// Like Read(), but will read also elements like position, velocity
//
signal object::ReadComplete (ifstream& stream, typeSTR& stype) {
	// read basic info
	if(Read(stream, stype) == signal::corrupted)
		return signal::corrupted;
	
	// read kinematics elements
	vec3<long double> v;
	v.x = in_fld(stream);
	v.y = in_fld(stream);
	v.z = in_fld(stream);
	SetPos(v);
	v.x = in_fld(stream);
	v.y = in_fld(stream);
	v.z = in_fld(stream);
	SetVel(v);
	
	return signal::good;
}


void object::Write (ofstream& stream) {
	stream << name << "\n";
	stream << typ->name << "\n";
	stream << colour.red << "\n";
	stream << colour.green << "\n";
	stream << colour.blue << "\n";
	stream << Radius().value() << "\n";
	stream << Mass().value() << "\n";
	stream << FrcSingleTolerance().value() << "\n";
	stream << FrcSumTolerance().value() << "\n";
}

// Like Write(), but will write also elements like position, velocity
//

void object::WriteComplete (ofstream& stream) {
	// write basic infos
	Write(stream);
	// write additional stuff
	stream << Pos().x() << "\n";
	stream << Pos().y() << "\n";
	stream << Pos().z() << "\n";
	stream << Vel().x() << "\n";
	stream << Vel().y() << "\n";
	stream << Vel().z() << "\n";
}

/***
 *  The AI of the hunters
 */
 
void object::AI_Hunter(system_c& sys) {
	
	// an object pointer array
	vector<object *> targets;
	
	// PART ONE: SEARCH FOR THE CLOSER HUNTABLE OBJECT
	// search for huntable objects
	for(unsigned int i=0; i!=sys.o.size(); i++)
		if(sys.o[i].typ->hunted == true)
			targets.push_back(&sys.o[i]);
	// if there isn't any target, return
	int targets_num = targets.size();
	if (!targets_num)
		return;
	// search the closest one: assume that the closest is the first. Then watch the next. If is closer, assume it as closest. Restart
	object *closest = targets[0];
	for(int i=1; i!=targets_num; i++)
		if( Distance(*closest).length() > Distance(*targets[i]).length() )
			closest = targets[i];
	
	// PART TWO, FOLLOW THE OBJECT
	// move the hunter in the direction of the closest
	// accelerate only if the hunter hasn't reached yet a fixed fast
	if(Vel() - closest->Vel() < tvelocity(vec3<long double>(20, 0, 0)))
		AddForce (tacceleration(Distance(*closest).direction(), tacceleration_scalar(0.01)) * Mass());
}


/***
 * This function Create a new object from the impact of two objects given, as they are two liquid balls whit a coesion very very very high
 */
#define COLOR_PREDOMINANCE 1.5

void object::Impact_Anaelastic(object& obj) {
	
	// the new object
	object newobj;
	// the two objects
	object *bigger;			// the bigger is the object that, relatively, is being hit by the smaller
	object *smaller;		// the smaller is the object that fuse whit the bigger and lose personality
	
	// set the bigger and the smaller
		
	// an object is bigger if has mass much bigger
	
	if(obj.Mass() < Mass()){
		smaller = &obj;
		bigger = this;
	}
	else{
		smaller = this;
		bigger = &obj;
	}
	// The new object mantein the name of the bigger. The new object is written in the this position
	if(bigger != this)
		name = obj.name;
	// the type is the type of the bigger
	typ = bigger->typ;
	// the color is the average, but considering the radius and the type's range
	colour.blue = ((bigger->Radius() * bigger->colour.blue * COLOR_PREDOMINANCE) + (smaller->Radius() * smaller->colour.blue)) / (bigger->Radius()*COLOR_PREDOMINANCE + smaller->Radius());
	colour.green = ((bigger->Radius() * bigger->colour.green * COLOR_PREDOMINANCE) + (smaller->Radius() * smaller->colour.green)) / (bigger->Radius()*COLOR_PREDOMINANCE + smaller->Radius());
	colour.red = ((bigger->Radius() * bigger->colour.red * COLOR_PREDOMINANCE) + (smaller->Radius() * smaller->colour.red)) / (bigger->Radius()*COLOR_PREDOMINANCE + smaller->Radius());
	
	if(colour.blue > typ->color_max.blue)
		colour.blue = typ->color_max.blue;
	else if(colour.blue < typ->color_min.blue)
		colour.blue = typ->color_min.blue;
	if(colour.red > typ->color_max.red)
		colour.red = typ->color_max.red;
	else if(colour.red < typ->color_min.red)
		colour.red = typ->color_min.red;
	if(colour.green > typ->color_max.green)
		colour.green = typ->color_max.green;
	else if(colour.green < typ->color_min.green)
		colour.green = typ->color_min.green;
	// the mass is the sum
	SetMass (obj.Mass() + Mass());
	// the coordinates are the average
	SetPos (((Pos() * Mass()) + (obj.Pos() * obj.Mass())) / (obj.Mass() + Mass()));
	// the velocity
	SetVel (((Vel() * Mass()) + (obj.Vel() * obj.Mass())) / (obj.Mass() + Mass()));
	// to calculate the radius we calculate the volum of the two object,
	SetRadius (RadiusestoVolume(Radius(), obj.Radius()));
	
	debug_Printf("Anaelastic Impact: Created this new object:");
	debug_Object(*this);
}

/*
 * Pure elastic impact
 * 
 * momentum is conserved
 * kinektic energy is coserved
 */

void object::Impact_Elastic(object& obj) {

	tmomentum momentum = Mass() * Vel() + obj.Mass() * obj.Vel();
	tenergy kinetic = Mass() * Vel().scalar() * Vel().scalar() + obj.Mass() * obj.Vel().scalar() * obj.Vel().scalar();
	
}



/***
 * This function simulate when an hunter 'eats' a hunted object
 * 
 * this must be the object huntER
 * hed must the object huntED
 */
void object::Impact_Hunting(object& hed, const time_raw& delta) {
	
	// a random number that is the (p)ercentage that the hunter eats of the hunted /100
	float p;
	
	// set p
	p = (float) math_RandomI(10, 90);
	p /= 100.0;
	
	hed.typ = hed.typ->product;
	
	// move a percentage p of ed mass in er
	SetMass( Mass() + hed.Mass() * p);
	hed.SetMass( hed.Mass() * (1 - p) );
	
	// decrease the radius of the hunted and increase the rasius of the hunter -- keep in mind that: r^3 = V * 3 / (4 * PI) -- V = 4 * PI * r^3 / 3
	// the hunter volume before
	tvolume volum = Radius() * Radius() * Radius() * (4.0/3) * PI;
	// the hunter volume after
	volum +=  (hed.Radius() * hed.Radius() * hed.Radius() * (4.0/3) * PI) * p;	// volum += volum_eated
	// the hunter radius compute from the new volume
	SetRadius ( pow((volum * 3 / (4 * PI)).value(), 1/3.0) );
	
	// the hunted volume before (v = 4/3 * PI * r^3)
	volum = hed.Radius() * hed.Radius() * hed.Radius() * 4/3 * PI;
	// reduce the hunted volume
	volum -= volum * p;
	hed.SetRadius ( pow((volum * 3 / (4 * PI)).value(), 1/3.0) );
	
	// move the hunted a away and give him some velocity from the hunter
	// to decrease hunter velocity, launch the hunted
	
	vec3<long double> direction = Distance(hed).direction();

	hed.AddForce (
		tforce (
			tacceleration(direction, tacceleration_scalar((Vel().scalar()/delta)/2)), 
			Mass()
		)
	);
	AddForce (
		tforce (
			tacceleration(-direction, tacceleration_scalar((Vel().scalar()/delta)/2)), 
			Mass()
		)
	);
}
