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
 * This function compute the distance between the center of two objects
 */
double object::Distance(const object& obj) {
	return vec3<long double>(pos - obj.pos).length();
}

/***
 * Put in *b the address of the biggest object
 * i and l are the two objects,
 */
// how much an object must be bigger to another to be considered so.
#define BIGGER_TOLERANCE 1.21

void object::GetBigger (object& obj, object *& ptr) {
	
	// an object is bigger if has mass much bigger
	if (mass > obj.mass*BIGGER_TOLERANCE)
		ptr = this;
	else if (mass > obj.mass*BIGGER_TOLERANCE)
		ptr = &obj;
	// if no one is much bigger than the other, pick one randomly, but considering the mass
	else {
		srand(time(nullptr));
		if 		( (rand()/RAND_MAX) > (mass/(mass+obj.mass)) )
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
object::object (const setting& set, typeSTR& stype, BYTE& result) {
		
	//variables
	void *var[19];
	int input;
	string comment;				// This is a buffer that contein comment of what is just been done
	string mass_irregularity;	// assume the value IRREGULARITY if the mass is out of range
	string color_irregularity;	// assume the value IRREGULARITY if the color is out of range
	string name_irregularity;	// assume the value IRREGULARITY if there is no name
	
	// Initialize the object
	name.clear();
	typ = stype.Search("Object");
	mass = 0;
	radius = 0;
	colour.blue = 0;
	colour.red = 0;
	colour.green = 0;
	
	// the loop
	while(1) {
		// check for IRREGALARITY
		// irregularity: MASS
		if ((mass > typ->mass_min) && (mass < typ->mass_max)) {
			mass_irregularity.clear();
		}
		else {
			mass_irregularity = IRREGULARITY;
			comment += "\n" IRREGULARITY " mass out of range";
		}
		// irregularity: COLOR
		if (colour.CheckRange(typ->color_min, typ->color_max) == GOOD_SIG)
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
		var[0] = &name;
		var[1] = &name_irregularity;
		var[2] = &typ->name;
		var[3] = &typ->description;
		var[4] = &colour.red;
		var[5] = &color_irregularity;
		var[6] = &colour.green;
		var[7] = &colour.blue;
		var[8] = &mass;
		var[9] = &mass_irregularity;
		var[10] = &radius;
		var[11] = &pos.x;
		var[12] = &pos.y;
		var[13] = &pos.z;
		var[14] = &vel.x;
		var[15] = &vel.y;
		var[16] = &vel.z;
		var[17] = &comment;
		OPS(set, "CREATE A NEW OBJECT\n\n%f-1) name:         %s%s\n%f-2) type:         %s\n&ti7%s&t0\n%f-3) color:        red: %i   %s&ti7\ngreen: %i\nblue: %i&t0\n%f-4) mass:         %l   %s\n%f-5) radius:       %l\n%f-6) coordinates:  x: %l&ti7\ny: %l\nz: %l&t0\n%f-7) velocity:     x: %l&ti7\ny: %l\nz: %l&t0\n%f-8) LOAD  the object from a file\n%f-9) SAVE  this object to a file\n%f-10) DONE\n11) EXIT whitout saving\n\n%s", var);
		cin >> input;
		
		// reset previous comment
		comment.clear();
	
		switch(input) {
			// Name
			case 1:
				OPS (set, "INITIALIZE A NEW OBJECT\n\nInsert the name of the new object:", nullptr);
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
				var[0] = & typ->mass_min;
				var[1] = & typ->mass_max;
				OPS (set, "Create A NEW OBJECT\n\nInsert the mass of the new object: (t)\n&tdThe mass's legal values are between %l and %l", var);
				cin >> mass;
				comment += "\nNew mass assigned succefully!";
				break;
		// Radius
			case 5:
				OPS (set, "Create A NEW OBJECT\n\nInsert the radius of the new object: (Km)", nullptr);
				cin >> radius;
				comment += "\nNew radius assigned succefully!";
				break;
		// Coordiates
			case 6:
				OPS (set, "Create A NEW OBJECT\n\nInsert the position in the x axis of the new object: (Km)", nullptr);
				cin >> pos.x;
				OPS (set, "Create A NEW OBJECT\n\nInsert the position in the y axis of the new object: (Km)", nullptr);
				cin >> pos.y;
				OPS (set, "Create A NEW OBJECT\n\nInsert the position in the z axis of the new object: (Km)", nullptr);
				cin >> pos.z;
				comment += "\nNew coordinates assigned succefully!";
				break;
		// Velocity
			case 7:
				OPS (set, "Create A NEW OBJECT\n\nInsert the velocity in the x axis of the new object: (Km/s)", var);
				cin >> vel.x;
				OPS (set, "Create A NEW OBJECT\n\nInsert the velocity in the y axis of the new object: (Km/s)", var);
				cin >> vel.y;
				OPS (set, "Create A NEW OBJECT\n\nInsert the velocity in the z axis of the new object: (Km/s)", var);
				cin >> vel.z;
				comment += "\nNew velocity assigned succefully!";
				break;
		// LOAD
			case 8: {
					// load the object in a temporany variable
					BYTE result;
					object temp(stype, name, result);
					if (result == GOOD_SIG) {
						// move cinematic stats
						temp.pos = pos;
						temp.vel = vel;
						// move the temp(the new) object in this
						(*this) = temp;
						comment += "New object loaded succefully!";
					}
					// negative comment if fail
					else {
						comment += "\nCan't load the object! ";
						if (result == FILE_ERR_SIG)
							comment += "No object whit that name found!";
						else if (result == CORRUPTED_SIG)
							comment += "File corrupted or outdated!";
						else {
							comment += "Unregognized error signal, i am a bug! signal me please :)";
							#if DEBUG
							debug_Printf("obj_Init: obj_Load returned a signal not parsable. Update the error parser!");
							debug_Int(result);
							#endif
						}
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
					result = GOOD_SIG;
					return;
				}
				else
					comment += "\nCannot exit! Fix irregularity first";
				break;
		// EXIT WHITOUT SAVE
			case 11:
				// quit
				result = ABORTED_SIG;
				return;
		}
	}
	
	result = BAD_SIG;
	return;
}

/***
 * This constructor loads from a file the object
 */
object::object(typeSTR& stype, const string& name, BYTE& result) {
		
	// From the name, get the file address
	string path;
		
	path = OBJECT_PATH;
	path += name;
	path += ".object";
		
	// open the file
	ifstream file(path);
	if(!file){
		result = FILE_ERR_SIG;
		#if DEBUG
		debug_Printf(IRREGULARITY" Canno't read the object! File not found!");
		debug_Printf(name);
		#endif
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
		OPS(set, "While saving: The object you want to save alredy exist.\nDo you want to delete the previous object and save this? [n = no | something else = y]", nullptr);
		in_s(input);
		if(!input.compare("n"))
			return;
	}
	
	// Write the object
	Write(file);
}



BYTE object::Read (ifstream& stream, typeSTR& stype) {
	// scan the name
	in_fs(name, stream);
	// scan the type
	string buffer;
	in_fs(buffer, stream);
	typ = stype.Search(buffer);
	if (typ == nullptr)
		return CORRUPTED_SIG;
	// scan all the other things
	stream >> colour.red;
	stream >> colour.green;
	stream >> colour.blue;
	stream >> radius;
	stream >> mass;
	
	return GOOD_SIG;
}

BYTE object::ReadComplete (ifstream& stream, typeSTR& stype) {
	// scan the name
	in_fs(name, stream);
	// scan the type
	string buffer;
	in_fs(buffer, stream);
	typ = stype.Search(buffer);
	if (typ == nullptr)
		return CORRUPTED_SIG;
	// scan all the other things
	stream >> colour.red;
	stream >> colour.green;
	stream >> colour.blue;
	stream >> radius;
	stream >> mass;
	stream >> pos.x;
	stream >> pos.y;
	stream >> pos.z;
	stream >> vel.x;
	stream >> vel.y;
	stream >> vel.z;
	
	return GOOD_SIG;
}


void object::Write (ofstream& stream) {
	stream << name << endl;
	stream << typ->name << endl;
	stream << colour.red << endl;
	stream << colour.green << endl;
	stream << colour.blue << endl;
	stream << radius << endl;
	stream << mass << endl;
}

void object::WriteComplete (ofstream& stream) {
	stream << name << endl;
	stream << typ->name << endl;
	stream << colour.red << endl;
	stream << colour.green << endl;
	stream << colour.blue << endl;
	stream << radius << endl;
	stream << mass << endl;
	stream << pos.x << endl;
	stream << pos.y << endl;
	stream << pos.z << endl;
	stream << vel.x << endl;
	stream << vel.y << endl;
	stream << vel.z << endl;
}

/***
 *  The AI of the hunters
 */
#define HUNTER_ACCELERATION 0.002	// The acceleration of a hunter (will be moved to objdata)

void object::AI_Hunter(system_c& sys) {
	
	// an object pointer array
	vector<object *> targets;
	
	// if there is only him, exit
	if(sys.o.size() == 1)
		return;
	// PART ONE: SEARCH FOR THE CLOSER HUNTABLE OBJECT
	// search for huntable objects
	for(unsigned int i=0; i!=sys.o.size(); i++) {
		if(sys.o[i].typ->hunted == ON) {
			targets.push_back(&sys.o[i]);
		}
	}
	// if there isn't any target, return
	int targets_num = targets.size();
	if (!targets_num)
		return;
	// search the closest one: assume that the closest is the first. Then watch the next. If is closer, assume it as closest. Restart
	object *closest = targets[0];
	for(int i=1; i!=targets_num; i++)
		if( Distance(*closest) > Distance(*targets[i]) )
			closest = targets[i];
	
	// PART TWO, FOLLOW THE OBJECT
	// move the hunter in the direction of the closest
	// velx : distance x = vel : distance
	long double temp = HUNTER_ACCELERATION * sys.precision / Distance(*closest);
	vel.x -= (pos.x - closest->pos.x) * temp;
	vel.y -= (pos.y - closest->pos.y) * temp;
	vel.z -= (pos.z - closest->pos.z) * temp;
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
	colour.blue = ((bigger->colour.blue * bigger->radius *COLOR_PREDOMINANCE) + (smaller->colour.blue * smaller->radius)) / (bigger->radius*COLOR_PREDOMINANCE + smaller->radius);
	colour.green = ((bigger->colour.green * bigger->radius *COLOR_PREDOMINANCE) + (smaller->colour.green * smaller->radius)) / (bigger->radius*COLOR_PREDOMINANCE + smaller->radius);
	colour.red = ((bigger->colour.red * bigger->radius *COLOR_PREDOMINANCE) + (smaller->colour.red * smaller->radius)) / (bigger->radius*COLOR_PREDOMINANCE + smaller->radius);
	
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
	mass = obj.mass + mass;
	// the coordinates are the average
	pos.x = ((pos.x * mass) + (obj.pos.x * obj.mass)) / (obj.mass + mass);
	pos.y = ((pos.y * mass) + (obj.pos.y * obj.mass)) / (obj.mass + mass);
	pos.z = ((pos.z * mass) + (obj.pos.z * obj.mass)) / (obj.mass + mass);
	// the velocity
	vel.x = ((vel.x * mass) + (obj.vel.x * obj.mass)) / (obj.mass + mass);
	vel.y = ((vel.y * mass) + (obj.vel.y * obj.mass)) / (obj.mass + mass);
	vel.z = ((vel.z * mass) + (obj.vel.z * obj.mass)) / (obj.mass + mass);
	// to calculate the radius we calculate the volum of the two object,
	radius = RadiusestoVolume(radius, obj.radius);
	
	#if DEBUG
	debug_Printf("Anaelastic Impact: Created this new object:");
	debug_Object(newobj);
	#endif
	
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
	// a force variable
	long double f;
	// indicate in which direction the hunter is faster
	BYTE faster;
	// the velocity of the hunter in three axis
	vec3<long double> v;
	
	// set p (over 50, under 92)
	// over 50 because elsewhere the hunter could collide in the hunted after this impact
	p = (float) math_RandomI(50, 92);
	p /= 100.0;
	
	hed.typ = hed.typ->product;
	
	// move a percentage p of ed mass in er
	mass += hed.mass * p;
	hed.mass -= hed.mass * p;
	
	// decrease the radius of the hunted and increase the rasius of the hunter -- keep in mind that: r^3 = V * 3 / (4 * PI) -- V = 4 * PI * r^3 / 3
	// the hunter volume before
	volum = 4/3 * PI * radius * radius * radius;
	// the hunter volume after
	volum +=  (4/3 * PI * hed.radius * hed.radius * hed.radius) * p;	// volum += volum_eated
	// the hunter radius compute from the new volume
	radius = pow(volum * 3 / (4 * PI), 1/3.0);
	
	// the hunted volume before (v = 4/3 * PI * r^3)
	volum = 4/3 * PI * hed.radius * hed.radius * hed.radius;
	// reduce the hunted volume
	volum -= volum * p;
	hed.radius = pow(volum * 3 / (4 * PI), 1/3.0);
	
	// move the hunted a bit away and give him some velocity from the hunter
	// to decrease hunter velocity, launch the hunted in the direction the hunter is going faster
	// We use the absolute value of the velocity
	v = vel.absolute();
	
	faster = v.greatest();
	
	// if x is the fastest
	if(faster == X_AXIS) {
		// move the hunted away from the hunter enought to not touch it
		if(hed.pos.x > pos.x)
			hed.pos.x += hed.radius + radius + 0.01 + Distance(hed);
		else
			hed.pos.x -= hed.radius + radius + 0.01 + Distance(hed);
		// transimit half of the hunter fast on the hunted (f = m*a)
		f = vel.x * mass /2;
		hed.vel.x = f / hed.mass;
		vel.x /= 2;
		
	}
	// if y is the fastest
	else if(faster == Y_AXIS) {
		// move the hunted away from the hunter enought to not touch it
		if(hed.pos.y > pos.y)
			hed.pos.y += hed.radius + radius + 0.01 + Distance(hed);
		else
			hed.pos.y -= hed.radius + radius + 0.01 + Distance(hed);
		// transimit half of the hunter fast on the hunted (f = m*a)
		f = vel.y * mass / 2;
		hed.vel.y = f / hed.mass;
		vel.y /= 2;
	}
	// if z is the fastest
	else {
		// move the hunted away from the hunter enought to not touch it
		if(hed.pos.z > pos.z)
			hed.pos.z += hed.radius + radius + 0.01 + Distance(hed);
		else
			hed.pos.z -= hed.radius + radius + 0.01 + Distance(hed);
		// transimit half of the hunter fast on the hunted	(f = m*a)
		f = vel.z * mass /2;
		hed.vel.z = f / hed.mass;
		vel.z /= 2;
	}
}

void object::UpdateFast (double t){
	pos.x += vel.x * t;
	pos.y += vel.y * t;
	pos.z += vel.z * t;
}
