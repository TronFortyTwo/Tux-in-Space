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
 *	Object oriented file where Create a "class" object, giving a coerent and fast API to the program
 * 
 * 	all these function have the obj_ prefix
 * 
 */

#include "object.h"

using namespace std;

/***
 * Put in *b the address of the biggest object
 * i and l are the two objects,
 */
// how much an object must be bigger to another to be considered so.
#define BIGGER_TOLERANCE 1.21

void object::GetBigger (object& obj, object *& ptr) {
	
	// an object is bigger if has mass much bigger
	if (Mass() > obj.Mass()*BIGGER_TOLERANCE)
		ptr = this;
	else if (Mass() > obj.Mass()*BIGGER_TOLERANCE)
		ptr = &obj;
	// if no one is much bigger than the other, pick one randomly, but considering the mass
	else {
		srand(time(nullptr));
		if 		( (rand()/RAND_MAX) > (Mass()/(Mass()+obj.Mass())) )
			ptr = &obj;
		else
			ptr = this;
	}
}

/***
 * 	The function initialize a new object and ask information about it
 * 
 * 	n is the number of the object to initialize, if in a list
 * 	return ABORTED_SIG if the new object isn't initialized
 */
object::object (const setting& set, typeSTR& stype, signal& result) {
	
	int input;
	string comment;				// This is a buffer that contein comment of what is just been done
	string mass_irregularity;	// assume the value IRREGULARITY if the mass is out of range
	string color_irregularity;	// assume the value IRREGULARITY if the color is out of range
	string name_irregularity;	// assume the value IRREGULARITY if there is no name
	
	// Initialize the object
	name.clear();
	typ = stype.Search("Object");
	colour.blue = 0;
	colour.red = 0;
	colour.green = 0;
	
	// the loop
	while(1) {
		// check for IRREGALARITY
		// irregularity: MASS
		if ((Mass() > typ->mass_min) && (Mass() < typ->mass_max)) {
			mass_irregularity.clear();
		}
		else {
			mass_irregularity = IRREGULARITY;
			comment += "\n" IRREGULARITY " mass out of range";
		}
		// irregularity: COLOR
		if (colour.CheckRange(typ->color_min, typ->color_max) == true)
			color_irregularity.clear();
		else {
			color_irregularity = IRREGULARITY;
			comment += "\n" IRREGULARITY " color out of range";
		}
		// irregularity: NAME
		if (name.length())
			name_irregularity.clear();
		else {
			name_irregularity = IRREGULARITY;
			comment += "\n" IRREGULARITY " name not given yet";
		}
		
		// Print the actual state and scan the desire of the user
		vec3<long double> p (Pos());
		vec3<long double> v (Vel());
		stringstream ss;
		ss << "CREATE A NEW OBJECT\n\n%r-1) name:         "
			<< name << name_irregularity
			<< "\n%r-2) type:         " << typ->name
			<< "\n&ti7" << typ->description
			<< "&t0\n%r-3) color:        red: " << colour.red
			<< "   " << color_irregularity << "&ti7\ngreen: "
			<< colour.green << "\nblue: " << colour.blue
			<< "&t0\n%r-4) mass:         " << Mass() << "   "
			<< mass_irregularity << "\n%r-5) radius:       "
			<< Radius() << "\n%r-6) coordinates:  x: "
			<< p.x << "&ti7\ny: " << p.y << "\nz: " << p.z
			<< "&t0\n%r-7) velocity:     x: " << v.x
			<< "&ti7\ny: " << v.y << "\nz: " << v.z
			<< "&t0\n%r-8) LOAD  the object from a file\n%r-9) SAVE  "
			<< "this object to a file\n%r-10) DONE\n11) EXIT whitout saving\n\n"
			<< comment;
			
		OPS(set, ss.str());
		input = in_i();
		
		// reset previous comment
		comment.clear();
	
		switch(input) {
			// Name
			case 1:
				OPS (set, "INITIALIZE A NEW OBJECT\n\nInsert the name of the new object:");
				in_s(name);
				// apply the new name
				comment += "\nNew name assigned succefully!";
				break;
		// Type
			case 2:
				typ = &stype.Browse(set, "Choose a new type for your new object");
				comment += "\nNew type assigned succefully!";
				break;
		// Color
			case 3:
				colour.Scan(set, typ->color_min, typ->color_max);
				comment += "\nNew color assigned succefully!";
				break;
		// Mass
			case 4:
				ss.clear();
				ss.str("");
				ss << "Create A NEW OBJECT\n\nInsert the mass of the new object: (t)\n&tdThe mass's legal values are between " << typ->mass_min << " and " << typ->mass_max;
				OPS (set, ss.str());
				SetMass(in_ld());
				comment += "\nNew mass assigned succefully!";
				break;
		// Radius
			case 5:
				OPS (set, "Create A NEW OBJECT\n\nInsert the radius of the new object: (Km)");
				SetRadius(in_ld());
				comment += "\nNew radius assigned succefully!";
				break;
		// Coordiates
			case 6: {
					vec3<long double> p;
					OPS (set, "Create A NEW OBJECT\n\nInsert the position in the x axis of the new object: (Km)");
					p.x = in_ld();
					OPS (set, "Create A NEW OBJECT\n\nInsert the position in the y axis of the new object: (Km)");
					p.y = in_ld();
					OPS (set, "Create A NEW OBJECT\n\nInsert the position in the z axis of the new object: (Km)");
					p.z = in_ld();
					SetPos(p);
					comment += "\nNew coordinates assigned succefully!";
					break;
				}
		// Velocity
			case 7: {
					vec3<long double> v;
					OPS (set, "Create A NEW OBJECT\n\nInsert the velocity in the x axis of the new object: (Km/s)");
					v.x = in_ld();
					OPS (set, "Create A NEW OBJECT\n\nInsert the velocity in the y axis of the new object: (Km/s)");
					v.y = in_ld();
					OPS (set, "Create A NEW OBJECT\n\nInsert the velocity in the z axis of the new object: (Km/s)");
					v.z = in_ld();
					SetVel(v);
					comment += "\nNew velocity assigned succefully!";
					break;
				}
		// LOAD
			case 8: {
					// load the object in a temporany variable
					signal result;
					object temp(stype, name, result);
					if (result == signal::good) {
						// move kinematic stats
						MoveKinematic(temp);
						// move the temp(the new) object in this
						(*this) = temp;
						comment += "New object loaded succefully!";
					}
					// negative comment if fail
					else {
						comment += "\nCan't load the object! ";
						if (result == signal::file_err)
							comment += "No object whit that name found!";
						else if (result == signal::corrupted)
							comment += "File corrupted or outdated!";
					}
				}
				break;
		// SAVE
			case 9:
				Save(set);
				comment += "\nNew object saved succefully!";
				break;
		// DONE
			case 10:
				if (!(!mass_irregularity.compare(IRREGULARITY)) || (!color_irregularity.compare(IRREGULARITY)) || (!name_irregularity.compare(IRREGULARITY))) {
					result = signal::good;
					return;
				}
				else
					comment += "\nCannot exit! Fix irregularity first";
				break;
		// EXIT WHITOUT SAVE
			case 11:
				// quit
				result = signal::aborted;
				return;
		}
	}
	return;
}

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
	
	return signal::good;
}

signal object::ReadComplete (ifstream& stream, typeSTR& stype) {
	// read basic info
	if(Read(stream, stype) == signal::corrupted)
		return signal::corrupted;
	// read complete stuff
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
	stream << Radius() << "\n";
	stream << Mass() << "\n";
}

void object::WriteComplete (ofstream& stream) {
	// write basic infos
	Write(stream);
	// write additional stuff
	stream << Pos().x << "\n";
	stream << Pos().y << "\n";
	stream << Pos().z << "\n";
	stream << Vel().x << "\n";
	stream << Vel().y << "\n";
	stream << Vel().z << "\n";
}

/***
 *  The AI of the hunters
 */
#define HUNTER_ACCELERATION 0.002	// The acceleration of a hunter (will be moved to objdata)

void object::AI_Hunter(system_c& sys) {
	
	// if there is only him, exit
	if(sys.o.size() == 1)
		return;
	
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
	// TODO: not optimal solution!
	
	AddForce (Distance(*closest).direction() * HUNTER_ACCELERATION * Mass());
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
	GetBigger(obj, bigger);
	if(this == bigger)
		smaller = &obj;
	else
		smaller = this;
	// The new object mantein the name of the bigger. The new object is written in the this position
	if(bigger != this)
		name = obj.name;
	// the type is the type of the bigger
	typ = bigger->typ;
	// the color is the average, but considering the radius and the type's range
	colour.blue = ((bigger->colour.blue * bigger->Radius() *COLOR_PREDOMINANCE) + (smaller->colour.blue * smaller->Radius())) / (bigger->Radius()*COLOR_PREDOMINANCE + smaller->Radius());
	colour.green = ((bigger->colour.green * bigger->Radius() *COLOR_PREDOMINANCE) + (smaller->colour.green * smaller->Radius())) / (bigger->Radius()*COLOR_PREDOMINANCE + smaller->Radius());
	colour.red = ((bigger->colour.red * bigger->Radius() *COLOR_PREDOMINANCE) + (smaller->colour.red * smaller->Radius())) / (bigger->Radius()*COLOR_PREDOMINANCE + smaller->Radius());
	
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
	debug_Object(newobj);
	
	*this = newobj;
}


/***
 * This function simulate when an hunter 'eats' a hunted object
 * 
 * this must be the object huntER
 * hed must the object huntED
 */
void object::Impact_Hunting(object& hed) {
	
	// a random number that is the (p)ercentage that the hunter eats of the hunted /100
	float p;
	// a variable that store the volume of an object
	double volum;
	// the velocity of the hunter in three axis
	vec3<long double> v;
	
	// set p (over 50, under 92)
	// over 50 because elsewhere the hunter could collide in the hunted after this impact
	p = (float) math_RandomI(50, 92);
	p /= 100.0;
	
	hed.typ = hed.typ->product;
	
	// move a percentage p of ed mass in er
	SetMass( Mass() + hed.Mass() * p);
	hed.SetMass( hed.Mass() * (1 - p) );
	
	// decrease the radius of the hunted and increase the rasius of the hunter -- keep in mind that: r^3 = V * 3 / (4 * PI) -- V = 4 * PI * r^3 / 3
	// the hunter volume before
	volum = 4/3 * PI * Radius() * Radius() * Radius();
	// the hunter volume after
	volum +=  (4/3 * PI * hed.Radius() * hed.Radius() * hed.Radius()) * p;	// volum += volum_eated
	// the hunter radius compute from the new volume
	SetRadius ( pow(volum * 3 / (4 * PI), 1/3.0) );
	
	// the hunted volume before (v = 4/3 * PI * r^3)
	volum = 4/3 * PI * hed.Radius() * hed.Radius() * hed.Radius();
	// reduce the hunted volume
	volum -= volum * p;
	hed.SetRadius ( pow(volum * 3 / (4 * PI), 1/3.0) );
	
	// move the hunted a bit away and give him some velocity from the hunter
	// to decrease hunter velocity, launch the hunted in the direction the hunter is going faster
	// We use the absolute value of the velocity
	
	
	
	/*
	
	// indicate in which direction the hunter is faster
	axis3 faster;
	
	v = body.GetVel().absolute();
	
	faster = v.greatest();

	if(hed.pos[faster] > pos[faster])
		hed.pos[faster] += hed.radius + radius + 0.01 + Distance(hed);
	else
		hed.pos[faster] -= hed.radius + radius + 0.01 + Distance(hed);
	
	f = vel[faster] * mass /2;
	hed.vel[faster] = f / hed.mass;
	vel[faster] /= 2;
	*/
}
