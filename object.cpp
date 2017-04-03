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
	return math_Pitagora3D(posx-obj.posx, posy-obj.posy, posz-obj.posz);
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
		srand(time(NULL));
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
	void *var[18];
	int input;
	string comment;				// This is a buffer that contein comment of what is just been done
	string mass_irregularity;	// assume the value IRREGULARITY if the mass is out of range
	string color_irregularity;	// assume the value IRREGULARITY if the color is out of range
	
	// Initialize the object
	name = "Choose a name for your new object";
	typ = stype.Search("Object");
	mass = 0;
	radius = 0;
	colour.blue = 0;
	colour.red = 0;
	colour.green = 0;
	posx = 0;
	posy = 0;
	posz = 0;
	velx = 0;
	vely = 0;
	velz = 0;
	
	// the loop
	while(1) {
		// check for IRREGALARITY
		// irregularity: MASS
		if ((mass > typ->mass_min) && (mass < typ->mass_max)) {
			mass_irregularity.clear();
		}
		else {
			mass_irregularity = IRREGULARITY;
			comment += "\n";
			comment += IRREGULARITY;
			comment += " mass out of range";
		}
		// irregularity: COLOR
		if (colour.CheckRange(typ->color_min, typ->color_max) == GOOD_SIG)
			color_irregularity.clear();
		else {
			color_irregularity = IRREGULARITY;
			comment += "\n";
			comment += IRREGULARITY;
			comment += " color out of range";
		}
		
		// Print the actual state and scan the desire of the user
		var[0] = &name;
		var[1] = &typ->name;
		var[2] = &typ->description;
		var[3] = &colour.red;
		var[4] = &color_irregularity;
		var[5] = &colour.green;
		var[6] = &colour.blue;
		var[7] = &mass;
		var[8] = &mass_irregularity;
		var[9] = &radius;
		var[10] = &posx;
		var[11] = &posy;
		var[12] = &posz;
		var[13] = &velx;
		var[14] = &vely;
		var[15] = &velz;
		var[16] = &comment;
		OPS(set, "CREATE A NEW OBJECT\n\n%f-1) name:         %s\n%f-2) type:         %s\n&ti7%s&t0\n%f-3) color:        red: %i   %s&ti7\ngreen: %i\nblue: %i&t0\n%f-4) mass:         %l   %s\n%f-5) radius:       %l\n%f-6) coordinates:  x: %l&ti7\ny: %l\nz: %l&t0\n%f-7) velocity:     x: %l&ti7\ny: %l\nz: %l&t0\n%f-8) LOAD  the object from a file\n%f-9) SAVE  this object to a file\n%f-10) DONE\n11) EXIT whitout saving\n\n%s", var);
		cin >> input;
		
		// reset previous comment
		comment[0] = 0;
	
		// Name
		if(input == 1) {
			OPS (set, "INITIALIZE A NEW OBJECT\n\nInsert the name of the new object:\n&tdThe name can't contein spaces", nullptr);
			in_s(name);
			// apply the new name
			comment += "\nNew name assigned succefully!";
		}
		// Type
		else if(input == 2) {
			typ = &stype.Browse(set, "Choose a new type for your new object");
			comment = "\nNew type assigned succefully!";
		}
		// Color
		else if(input == 3) {
			colour.Scan(set, typ->color_min, typ->color_max);
			comment = "\nNew color assigned succefully!";
		}
		// Mass
		else if(input == 4) {
			var[0] = & typ->mass_min;
			var[1] = & typ->mass_max;
			OPS (set, "Create A NEW OBJECT\n\nInsert the mass of the new object: (t)\n&tdThe mass's legal values are between %l and %l", var);
			cin >> mass;
			comment = "\nNew mass assigned succefully!";
		}
		// Radius
		else if(input == 5) {
			OPS (set, "Create A NEW OBJECT\n\nInsert the radius of the new object: (Km)", nullptr);
			cin >> radius;
			comment = "\nNew radius assigned succefully!";
		}
		// Coordiates
		else if(input == 6) {
			OPS (set, "Create A NEW OBJECT\n\nInsert the position in the x axis of the new object: (Km)", nullptr);
			cin >> posx;
			OPS (set, "Create A NEW OBJECT\n\nInsert the position in the y axis of the new object: (Km)", nullptr);
			cin >> posy;
			OPS (set, "Create A NEW OBJECT\n\nInsert the position in the z axis of the new object: (Km)", nullptr);
			cin >> posz;
			comment += "\nNew coordinates assigned succefully!";
		}
		// Velocity
		else if(input == 7) {
			OPS (set, "Create A NEW OBJECT\n\nInsert the velocity in the x axis of the new object: (Km/s)", var);
			cin >> velx;
			OPS (set, "Create A NEW OBJECT\n\nInsert the velocity in the y axis of the new object: (Km/s)", var);
			cin >> vely;
			OPS (set, "Create A NEW OBJECT\n\nInsert the velocity in the z axis of the new object: (Km/s)", var);
			cin >> velz;
			comment = "\nNew velocity assigned succefully!";
		}
		// LOAD
		else if(input == 8) {
			// load the object in a temporany variable
			BYTE result;
			object temp(stype, name, result);
			if (result == GOOD_SIG) {
				// move cinematic stats
				temp.posx = posx;
				temp.posy = posy;
				temp.posz = posz;
				temp.velx = velx;
				temp.vely = vely;
				temp.velz = velz;
				// move the temp(the new) object in this
				(*this)=temp;
				// positive comment (resetting the previous)
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
					comment += "Unregognized error signal";
					#if DEBUG
					debug_Printf("obj_Init: obj_Load returned a signal not parsable. Update the error parser!");
					debug_Int(result);
					#endif
				}
			}
		}
		// SAVE
		else if(input == 9) {
			Save(set);
			comment = "\nNew object saved succefully!";
		}	
		// DONE
		else if(input == 10) {
			if (!(!mass_irregularity.compare(IRREGULARITY)) || (!color_irregularity.compare(IRREGULARITY)))
				break;
			else
				comment = "\nCannot exit! Fix irregularity first";
		}
		// EXIT WHITOUT SAVE
		else if(input == 11) {
			// quit
			result = ABORTED_SIG;
			return;
		}
	}
	result = GOOD_SIG;
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
	stream >> posx;
	stream >> posy;
	stream >> posz;
	stream >> velx;
	stream >> vely;
	stream >> velz;
	
	return GOOD_SIG;
}


void object::Write (ofstream& stream) {
	stream << name << endl << typ->name << endl << colour.red << endl << colour.green << endl << colour.blue << endl << radius << endl << mass << endl;
}
void object::WriteComplete (ofstream& stream) {
	stream << name << endl << typ->name << endl << colour.red << endl << colour.green << endl << colour.blue << endl << radius << endl << mass << endl << posx << endl << posy << endl << posz << endl << velx << endl << vely << endl << velz << endl;
}

/***
 *  The AI of the hunters
 */
#define HUNTER_ACCELERATION 0.002	// The acceleration of a hunter (will be moved to objdata)

void object::AI_Hunter(system_c& sys) {
	
	// an object pointer array
	vector<object *> targets;
	
	// if there is only him, exit
	if(sys.nobj == 1)
		return;
	// PART ONE: SEARCH FOR THE CLOSER HUNTABLE OBJECT
	// search for huntable objects
	for(int i=0; i!=sys.nobj; i++) {
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
	velx -= (posx - closest->posx) * temp;
	vely -= (posy - closest->posy) * temp;
	velz -= (posz - closest->posz) * temp;
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
	posx = ((posx * mass) + (obj.posx * obj.mass)) / (obj.mass + mass);
	posy = ((posy * mass) + (obj.posy * obj.mass)) / (obj.mass + mass);
	posz = ((posz * mass) + (obj.posz * obj.mass)) / (obj.mass + mass);
	// the velocity
	velx = ((velx * mass) + (obj.velx * obj.mass)) / (obj.mass + mass);
	vely = ((vely * mass) + (obj.vely * obj.mass)) / (obj.mass + mass);
	velz = ((velz * mass) + (obj.velz * obj.mass)) / (obj.mass + mass);
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
	long double vx, vy, vz;
	
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
	vx = velx;
	if(vx < 0)
		vx = -vx;
	vy = vely;
	if(vy < 0)
		vy = -vy;
	vz = velz;
	if(vz < 0)
		vz = -vz;
	if (vx > vy) {
		if(vx > vz)
			faster = X_AXIS;
		else
			faster = Z_AXIS;
	}
	else {
		if(vy > vz)
			faster = Y_AXIS;
		else
			faster = Z_AXIS;
	}
	// if x is the fastest
	if(faster == X_AXIS) {
		// move the hunted away from the hunter enought to not touch it
		if(hed.posx > posx)
			hed.posx += hed.radius + radius + 0.01 + Distance(hed);
		else
			hed.posx -= hed.radius + radius + 0.01 + Distance(hed);
		// transimit half of the hunter fast on the hunted (f = m*a)
		f = velx * mass /2;
		hed.velx = f / hed.mass;
		velx /= 2;
		
	}
	// if y is the fastest
	else if(faster == Y_AXIS) {
		// move the hunted away from the hunter enought to not touch it
		if(hed.posy > posy)
			hed.posy += hed.radius + radius + 0.01 + Distance(hed);
		else
			hed.posy -= hed.radius + radius + 0.01 + Distance(hed);
		// transimit half of the hunter fast on the hunted (f = m*a)
		f = vely * mass / 2;
		hed.vely = f / hed.mass;
		vely /= 2;
	}
	// if z is the fastest
	else {
		// move the hunted away from the hunter enought to not touch it
		if(hed.posz > posz)
			hed.posz += hed.radius + radius + 0.01 + Distance(hed);
		else
			hed.posz -= hed.radius + radius + 0.01 + Distance(hed);
		// transimit half of the hunter fast on the hunted	(f = m*a)
		f = velz * mass /2;
		hed.velz = f / hed.mass;
		velz /= 2;
	}
}

void object::UpdateFast (double t){
	posx += velx * t;
	posx += velx * t;
	posx += velx * t;
}