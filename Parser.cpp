/*
#############################################################################################
#    Tux in Space - space simulator																#
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
bool parser_Quit (const setting& set, system_c&);
void parser_Distance(const setting&, system_c&);
time_sim parser_Jump(const setting& set, time_sim&, const time_raw&);
time_sim parser_Wait(const setting& set, time_sim&, const time_raw&);
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
	in_inline_s(input);
	// continue
	if ((!input.compare("step")) || (!input.compare("s"))) {
		t.Add(sys.precision.time());
	}
	// help
	else if ((!input.compare("help")) || (!input.compare("h"))) {
		OPS(set, "HELP\n\nYou have to press commands to manage the system. Some commands are:\n-step (s)\n-create (c)\n-jump (j)\n-wait (w)\n-information (i)\n-settings\n-save\n-distance\n-quit\n-delete\n\nPress something to continue...");
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
		quit = parser_Quit(set, sys);
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
	else
		parser_Reask(set, input);
	
	in_clear();
	
	return t;
}
	
/**
 * The parser_Reask function. parser_Reask the input
 */
void parser_Reask(const setting& set, const string& command){
	OPS_Error(set, "Sorry. But the command " + command + " that you wrote is unknown. Press something to continue:");
	in_s();
}
	
/***
 * This command calculate and show the distance between two objects
 */
void parser_Distance(const setting& set, system_c& sys){
	
	string name;
	object *o;
	object *u;
	long double distance;
	
	// ask which two object
	OPS(set, "DISTANCE\n\nCalculate the distance between two objects.\n\n&t2Insert the name of the first object:\n\n'n' to exit");
	in_s(name);
	if(!name.compare("n"))
		return;
	o = sys.SearchObj(name);
	if(o == nullptr) {
		OPS_Error(set, "There isn't any object whit that name!\n\nInsert a new command");
		return;
	}
	OPS(set, "DISTANCE\n\nCalculate the distance between two objects.\n\n&t2Insert the name of the second object:\n\n'n' to exit");
	in_s(name);
	if(!name.compare("n"))
		return;
	u = sys.SearchObj(name);
	if(u == nullptr) {
		OPS_Error(set, "There isn't any object whit that name!\n\nInsert a new command");
		in_s();
		return;
	}
	distance = o->Distance(*u).module();
	stringstream ss;
	ss << "DISTANCE\n\nThe distance between the two object is:\n&td" << distance << " m/s\n\n&t0Press something to continue...";
	OPS(set, ss.str());
	in_s();
}
	
/***
 * This function prepare the parser to parser_Quit
 */
bool parser_Quit (const setting& set, system_c& sys){
		
	string input;		
	// ask for confirm to quit
	OPS(set, "QUIT\n%r-Are you sure you want to quit? [y/n]\nOr you want to save before go? [s]");
	in_s(input);
	
	if (input[0] == 's') {
		sys.Save(set);
	}
	else if (input[0] != 'y')
		return false;
	
	return true;
}
	
/***
 * This function delete an object
 */
void parser_Delete(const setting& set, system_c& sys) {
		
	string name;	//the name of the object
	object *obj;	//the pointer to the object
		
	// ask the user for the name
	OPS(set, "DELETE\n%r-Which object do you want do delete?\n\n&t1Press 'n' to go back");
	in_s(name);
	if (!name.compare("n"))
		return;
		
	// search the object
	obj = sys.SearchObj(name);
	if (obj == nullptr) {	//if there isn't any object whit that name
		OPS_Error(set, "There isn't any object whit that name!\nPress something to continue");
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
	string input;
	stringstream ss;
	
	// Generic informations about the system
	ss << "INFORMATIONS\n%r-System " << sys.name << " with " << sys.o.size() 
		<< " objects\n";
	if(sys.o.size() > 0)
		ss << "Of which object do you want informations?\n\npress 'n' to exit";
	else {
		ss << "&t2Press something to continue...";
		OPS(set, ss.str());
		in_s();
		return;
	}
	
	OPS(set, ss.str());
	in_s(input);
	if(!input.compare("n"))
		return;
	// information about a precise object
	obj = sys.SearchObj(input);
	if(obj == nullptr){
		OPS_Error(set, "No object with this name has been found.\n\n&t2Press something to continue...");
		in_s();
		return;
	}
	
	ss.clear();
	ss.str("");
	ss << "Informations about " << obj->name << "%s\n\n%r-type: " << obj->typ->name 
		<< "\n%r-color: &td \nred: " << obj->colour.red << "\ngreen: " << obj->colour.green
		<< "\nblue: " << obj->colour.blue << " &t0 \n%r-mass: " << obj->Mass().value()
		<< "\n%r-radius: " << obj->Radius().value() << "\n%r-x: " << obj->Pos().x() << "\ny: "
		<< obj->Pos().y() << "\nz: " << obj->Pos().z() << "\n%r-velocity in x: "
		<< obj->Vel().x() << "\nvelocity in y: " << obj->Vel().y() << "\nvelocity in z: "
		<< obj->Vel().z() << "\n%r-\nPress somthing to continue...";
	
	OPS(set, ss.str());
	in_s();
}
	
	
/***
 * Make the simulation wait for a while
 */
time_sim parser_Wait(const setting& set, time_sim& now, const time_raw& precision) {
		
	OPS(set, "WAIT\n%r-Insert the amount of simulation-time you want to wait\n<year> <day> <hour> <minute> <second>\nThe operation will be made whit an error of max " + to_string(precision.time()) + " seconds");
	//scanf the time
	int y, d, h, m;
	float s;
	// year
	y = in_inline_i();
	// day
	d = in_inline_i();
	// hour
	h = in_inline_i();
	// minute
	m = in_inline_i();
	// second
	s = in_f();
	
	time_sim t (y, d, h, m, s);
	
	
	return now + t;
}
	
/***
 * Make the simulation Jump to a determined time 
 */
time_sim parser_Jump(const setting& set, time_sim& now, const time_raw& precision) {

	time_sim t;
	
	stringstream ss;
	ss << "JUMP\n%r-Insert the information about the moment you want to jump\n<year> <day> <hour> <minute> <second>\nThe actual time is: YEAR "
		<< now.Year() << " DAY " << now.Day() << " TIME " << now.Hour() << ":"
		<< now.Minute() << ":" << now.Second() << "\nThe jump will be made whit an error of max "
		<< precision.time() << " seconds";
	
	OPS(set, ss.str());
	while(1) {
		int y, d, h, m;
		float s;
		// year
		y = in_inline_i();
		// day
		d = in_inline_i();
		// hour
		h = in_inline_i();
		// minute
		m = in_inline_i();
		// second
		s = in_f();
		
		time_sim t(y, d, h, m, s);
		
		if(t.Compare(now) == comparison::major)	{
			// Error message if the time given isn't valid
			t = now;
			OPS_Error(set, "The time given is out of range! Please put a time that is future to the actual time, that is:\nYEAR " + to_string(t.Year()) + " DAY " + to_string(t.Day()) + " TIME " + to_string(t.Hour()) + ":" + to_string(t.Minute()) + ":" + to_string(t.Second()) + "\nThe jump will be made whit an error of max " + to_string(precision.time()) + " seconds");
		}
		else
			break;
	}
	return t;
}
