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
 * This is the instruction's parser. elaborate the input and do what these sentences in this strange human language would say.
 * 
 */

#include "Parser.h"

using namespace std;

// internal functions
void parser_Reask(const setting&, const string&);
void sys_Save(const setting&, system_c&);
void parser_Create(const setting&, system_c&);
void parser_Delete(const setting&, system_c&);
time_sim parser_Quit (const setting& set, system_c&, time_sim&, bool& quit);
void parser_Distance(const setting&, system_c&);
time_sim parser_Jump(const setting& set, time_sim&, long double);
time_sim parser_Wait(const setting& set, time_sim&, long double);
void parser_Information (const setting&, system_c&);

/**
 * The main function
 * of the parser
 */
time_sim Parser(setting& set, system_c& sys, bool& quit) {
		
	// what is scanned
	string input;
	// the time we want (simulation)
	time_sim t = sys.stime;
		
	// Now for every possible command call the correct command's function or simply do it if is short.
	in_s(input);
	// continue
	if ((!input.compare("step")) || (!input.compare("s"))) {
		t.AddSec(sys.precision);
	}
	// help
	else if ((!input.compare("help")) || (!input.compare("h"))) {
		OPS(set, "HELP\n\nYou have to press commands to manage the system. Insert a command to visualize his interface. Some commands are:\n-step (s)\n-create (c)\n-jump (j)\n-wait (w)\n-information (i)\n-settings\n-save\n-distance\n-quit\n-delete\n\nPress something to continue...", nullptr);
		in_s(input);
	}
	// parser_Jump
	else if ((!input.compare("jump")) || (!input.compare("j")))
		t = parser_Jump(set, sys.stime, sys.precision);
		
	// parser_Settings
	else if ((!input.compare("information")) || (!input.compare("i")) ||  (!input.compare("info")))
		parser_Information(set, sys);
	// parser_Wait
	else if ((!input.compare("wait")) || (!input.compare("w")))
		t = parser_Wait(set, sys.stime, sys.precision);
	// parser_Create
	else if (!(input.compare("create")) || (!input.compare("c")))
		sys.NewObj(set);
	// parser_Quit / exit
	else if (!(input.compare("quit")) || (!input.compare("exit")))
		t = parser_Quit(set, sys, sys.stime, quit);
	// save
	else if (!input.compare("save"))
		sys.Save(set);
	//distance
	else if (!input.compare("distance"))
		parser_Distance(set, sys);
	// delete an object
	else if (!(input.compare("delete")) || (!input.compare("remove")))
		parser_Delete(set, sys);
	// settings
	else if (!(input.compare("settings")) || (!input.compare("configuration")))
		menu_Settings(set);
	// wrong command
	else {
		parser_Reask(set, input);
		in_s();
	}
		 
	return t;
}
	
/**
 * The parser_Reask function. parser_Reask the input
 */
void parser_Reask(const setting& set, const string& command){
	void const *const var = &command;
	OPS_Error(set, "Sorry. But the command %s that you wrote is unknown. Press something to continue:", &var);
}
	
/***
 * This command calculate and show the distance between two objects
 */
void parser_Distance(const setting& set, system_c& sys){
	
	string name;
	object *o;
	object *u;
	long double distance[2];
	void *var[2];
	
	// ask which two object
	OPS(set, "DISTANCE\n\nCalculate the distance between two objects.\n\n&t2Insert the name of the first object:", nullptr);
	in_s(name);
	o = sys.SearchObj(name);
	if(o == nullptr) {
		OPS_Error(set, "There isn't any object whit that name!\n\nInsert a new command", nullptr);
		return;
	}
	OPS(set, "DISTANCE\n\nCalculate the distance between two objects.\n\n&t2Insert the name of the second object:", nullptr);
	in_s(name);
	u = sys.SearchObj(name);
	if(u == nullptr) {
		OPS_Error(set, "There isn't any object whit that name!\n\nInsert a new command", nullptr);
		in_s();
		return;
	}
	distance[0] = o->Distance(*u);
	distance[1] = (o->pos+o->vel-u->pos-u->vel).length() - distance[0];
	var[0] = distance;
	var[1] = &distance[1];
	OPS(set, "DISTANCE\n\nThe distance between the two object is:\n&td%l Km\n&t0And, if the two object take constant velocity, the distance will change at a velocity of\n&td%l km/s\n\n&t0Press something to continue...", var);
	in_s();
}
	
/***
 * This function prepare the parser to parser_Quit
 */
time_sim parser_Quit (const setting& set, system_c& sys, time_sim& now, bool& quit){
		
	time_sim t;	 	//this is the escape time
	string input;		
	// ask for confirm to parser_Quit
	OPS(set, "QUIT\n\nAre you sure you want to quit? [y/n]\nOr you want to save before go? [s]", nullptr);
	in_s();
	// if doesn't want to parser_Quit return now
	if (input[0] == 's') {
		sys.Save(set);
		return now;
	}
	else if (input[0] != 'y') {
		return now;
	}
	// now we prepare the quit event
	t = now;
	quit = true;
	return t;
}
	
/***
 * This function delete an object
 */
void parser_Delete(const setting& set, system_c& sys) {
		
	string name;	//the name of the object
	object *obj;	//the pointer to the object
		
	// ask the user for the name
	OPS(set, "DELETE\n\nWhich object do you want do delete?\n\n&t1Press 'n' to Quit", nullptr);
	in_s(name);
	if (!name.compare("n"))
		return;
		
	// search the object
	obj = sys.SearchObj(name);
	if (obj == nullptr) {	//if there isn't any object whit that name
		OPS_Error(set, "There isn't any object whit that name!\nPress something to continue", nullptr);
		in_s();
		return;
	}
		
	// delete the object
	sys.RemoveObj(*obj);
}
	
/***
 * parser_Settings about the system and the objects
 */
void parser_Information(const setting& set, system_c& sys) {
		
	object *obj;	// The object to describe
	void *var[13];	// The variables to give to OPS
	unsigned int obs = sys.o.size();
	string input;

	var[0] = &sys.name;
	var[1] = &obs;
	// Generic informations about the system
	OPS(set, "Informations\n\nSystem %s whit %i objects\n\nOf which object do you want informations? press 'n' to not display any object informations", var);
	in_s(input);
	if(!input.compare("n"))
		return;
	// information about a precise object
	obj = sys.SearchObj(input);
	if(obj == nullptr){
		OPS_Error(set, "No object whit this name is been found. press a button to continue", nullptr);
		in_s();
		return;
	}	
	var[0] = &obj->name;
	var[1] = &obj->typ->name;
	var[2] = &obj->colour.red;
	var[3] = &obj->colour.green;
	var[4] = &obj->colour.blue;
	var[5] = &obj->mass;
	var[6] = &obj->radius;
	var[7] = &obj->pos.x;
	var[8] = &obj->pos.y;
	var[9] = &obj->pos.z;
	var[10] = &obj->vel.x;
	var[11] = &obj->vel.y; 
	var[12] = &obj->vel.z;
	OPS(set, "Informations about %s\n%f-type: %s\n%f-color: &td \nred: %i\ngreen: %i\nblue: %i &t0 \n%f-mass: %l\n%f-radius: %l\n%f-x: %l\n\ny: %l\n\nz: %l\n%f-velocity in x: %l\n\nvelocity in y: %l\n\nvelocity in z: %l\n%f-\n\nPress somthing to continue...", var);
	in_s();
}
	
	
/***
 * The parser_Wait function make the simulation parser_Wait for a while. The user say how much 
 */
time_sim parser_Wait(const setting& set, time_sim& now, long double precision) {
		
	OPS(set, "Wait\n\nInsert the amount of simulation-time you want to wait\n<year> <day> <hour> <minute> <second>\nThe operation will be made whit an error of max %l seconds", (void **)&precision);
	//scanf the time
	int y, d, h, m;
	float s;
	// year
	cin >> y;
	// day
	cin >> d;
	// hour
	cin >> h;
	// minute
	cin >> m;
	// second
	cin >> s;
	
	time_sim t (y, d, h, m, s);
	
	// check the time is future
	if (now.Compare(t) == comparison::major){
		OPS_Error(set, "You can't go in the past!\n\nPress something to continue...", nullptr);
		in_s();
		return now;
	}
	
	return t;
}
	
/***
 * The parser_Jump function make the simulation Jump to a determined time 
 */
time_sim parser_Jump(const setting& set, time_sim& now, long double precision) {

	time_sim t;
	void const *var[7];
	// set the var to give to OPS
	int y, d, h, m;
	float s;
	y = now.Year();
	d = now.Day();
	h = now.Hour();
	m = now.Minute();
	s = now.Second();
	var[0] = &y;
	var[1] = &d;
	var[2] = &h;
	var[3] = &m;
	var[4] = &s;
	var[6] = &precision;
	
	OPS(set, "Jump\n\nInsert the information about the moment you want to jump\n<year> <day> <hour> <minute> <second>\nThe actual time is: YEAR %i DAY %i TIME %i:%i:%f\nThe jump will be made whit an error of max %l seconds" , var);
	while(1) {
		int y, d, h, m;
		float s;
		// year
		cin >> y;
		// day
		cin >> d;
		// hour
		cin >> h;
		// minute
		cin >> m;
		// second
		cin >> s;
		
		time_sim t(y, d, h, m, s);
		
		if(t.Compare(now) == comparison::major)	{
			// Error message if the time given isn't valid
			t = now;
			OPS_Error(set, "The time given is out of range! Please put a time that is future to the actual time, that is:\nYEAR %i DAY %i TIME %i:%i:%f\nThe jump will be made whit an error of max %l seconds", var);
		}
		else
			break;
	}
	return t;
}
