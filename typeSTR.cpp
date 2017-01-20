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
 * the big type class 
 */
 
#include "typeSTR.h"

using namespace std;

/***
 * Build the type structure reading it from a file
 */
typeSTR::typeSTR () {
	
	// buffer (always helpful)
	string buf;
	
	// count how many types there are in the file in a loop
	{	
		// the stream to use
		ifstream stream(TYPE_DATABASE_FILE);
		// reset the number
		number = 0;
		// loop
		while(1) {
			// read the line (jumping blank ones)
			in_hfs (buf, stream);
			if(!buf.length())
				continue;
			// if is a new object memorize that there is a new object
			if (!buf.compare(0, 6, "NAME: "))
				number++;
			// if the file is finished exit
			else if (!buf.compare(0, 3, "EOF"))
				break;
		}
	}	
	// alloc enought spaces for all the ttype structures
	t.resize(number);
	
	// NAME. scan all the names
	{
		// the stream
		ifstream stream(TYPE_DATABASE_FILE);
		
		for(int i=0; i!=number; i++) {
			do
				in_hfs(buf, stream);
			while
				(!buf.compare(0, 6, "NAME: "));
			t[i].name = buf.substr(6, buf.length());
		}
	}
	// PARENT. Set all the parent
	{
		// the stream
		ifstream stream(TYPE_DATABASE_FILE);
		
		for(int i=0; i!=number; i++) {
			do
				in_hfs(buf, stream);
			while
				(!buf.compare(0, 8, "PARENT:"));
			string parent = buf.substr(8, buf.length());
		t[i].parent = &Search(parent);
		}
	}
	// OTHER STUFF
	{
		// the stream
		ifstream stream(TYPE_DATABASE_FILE);
	
		// loop to scan all the types
		for(int i=0; i!=number; i++) {
			// start assigning some values
			t[i].color_max = t[i].parent->color_max;
			t[i].color_min = t[i].parent->color_min;
			t[i].hunted = t[i].parent->hunted;
			t[i].hunter = t[i].parent->hunter;
			t[i].mass_max = t[i].parent->mass_max;
			t[i].mass_min = t[i].parent->mass_min;
			t[i].product = t[i].parent->product;
			t[i].description.clear();

			// then scan own values over his parent ones
			// name, jump it
			in_hfs(buf, stream);
			// description
			in_hfs(buf, stream);
			if(!buf.compare(0, 13, "DESCRIPTION: ")) {
				t[i].description = buf.substr(13,buf.length());
				in_hfs(buf, stream);
			}
			// mass max:
			if(!buf.compare(0, 9, "MASS_MAX: ")) {
				string temp = buf.substr(9,buf.length());
				t[i].mass_max = atof(temp.c_str());
				in_hfs(buf, stream);
			}
			// mass min:
			if(!buf.compare(0, 9, "MASS_MIN: ")) {
				string temp = buf.substr(9,buf.length());
				t[i].mass_min = atof(temp.c_str());
				in_hfs(buf, stream);
			}
			// blue max:
			if(!buf.compare(0, 9, "BLUE MAX: ")) {
				string temp = buf.substr(9,buf.length());
				t[i].color_max.blue = atoi(temp.c_str());
				in_hfs(buf, stream);
			}
			// blue min:
			if(!buf.compare(0, 9, "BLUE MIN: ")) {
				string temp = buf.substr(9,buf.length());
				t[i].color_min.blue = atoi(temp.c_str());
				in_hfs(buf, stream);
			}
			// red max:
			if(!buf.compare(0, 8, "RED MAX: ")) {
				string temp = buf.substr(8, buf.length());
				t[i].color_max.red = atoi(temp.c_str());
				in_hfs(buf, stream);
			}
			// red min:
			if(!buf.compare(0, 8, "RED MIN: ")) {
				string temp = buf.substr(8, buf.length());
				t[i].color_min.red = atoi(temp.c_str());
				in_hfs(buf, stream);
			}
			// green max:
			if(!buf.compare(0, 10, "GREEN MAX: ")) {
				string temp = buf.substr(10, buf.length());
				t[i].color_max.green = atoi(temp.c_str());
				in_hfs(buf, stream);
			}
			// green min:
			if(!buf.compare(0, 10, "GREEN MIN: ")) {
				string temp = buf.substr(10,buf.length());
				t[i].color_min.green = atoi(temp.c_str());
				in_hfs(buf, stream);
			}
			// HUNTED:
			if(!buf.compare(0, 8,"HUNTED: ")) {
				if(buf[8] == 'N')
					t[i].hunted = NO;
				else
					t[i].hunted = YES;
				in_hfs(buf, stream);
			}
			// HUNTER:
			if(!buf.compare(0, 8,"HUNTED: ")) {
				if(buf[8] == 'N')
					t[i].hunter = NO;
				else
					t[i].hunter = YES;
				in_hfs(buf, stream);
			}
			// product:
			if(!buf.compare(0, 7, "PRODUCT: ")) {
				string temp = buf.substr(0, 9);
				t[i].product = &Search(temp);
				in_hfs(buf, stream);
			}
			// assign the description if none has been set
			if(!t[i].description.length())
				t[i].description =  "No description is available yet for this type";
		}
	}
}



/***
 * Given a name, this function return the pointer to that type. If there isn't any type whit that name return NULL
 */
type& typeSTR::Search (const string& tofind) {
	
	// the loop that search the type whit the right name
	for(int i=0; i!=number; ++i)
		if (!t[i].name.compare(tofind))
			 return t[i];
	
	#if DEBUG
	debug_Printf("type_Search (!) No type whit the name (read below) has been found! This is a bug!");
	debug_Printf(tofind);
	#endif
	
	return Search("Object");
}



/***
 * In the kind browser you can browse types read from type.typ file and stored in Stype, see descriptions and choose one type to return to the calling function
 * 
 * file is the source struct
 * title is an intestation to write as title
 */ 
type& typeSTR::Browse(const setting& set, const string& title) {
		
	// in the gerarchic tree of types, is the common parent that the types listed have
	type *commonparent = &Search("Object");
	type& genobj = Search("Object");
	// the output buffer
	std::string buf;
	// the last object number
	int maxn;
	// the number of the back and description buttons
	int backn, descrn, genericn;
	// The pointers to the types listed
	vector<type *> types_listed;
	// input
	int input;
	// stuff to give to OPS and its counter
	vector<int> ivar;
	ivar.reserve(number);
	vector<void *> var;
	var.reserve(number);

	// the main loop
	while(1) {
		// restart elaborate the output
		maxn = 0;
		// the title
		buf = title;
		buf += "\n";
		// write in the dbuf the parent
		buf += commonparent->name;
		buf += ":\n";
		// search for types that have as parent commonparent
		for (int i=0; i!=number; i++) {
			// if the type has commonparent as parent
			if(t[i].parent == commonparent) {
				// if the type and his parent are the same, go ahead, because
				// it will be printed in the generic
				if(&t[i] == t[i].parent)
					continue;
				// write its number
				buf += "\n%i) %s";	// Write the object in the buffer
				types_listed.push_back(&t[i]);
				maxn++;
				ivar.push_back(maxn);
				var.push_back(&ivar.back());
				var.push_back(&t[i].name);
			}
		}
		// add the generic button
		genericn = maxn+1;
		var.push_back(&genericn);
		buf += "\n%i) Generic ";
		buf += commonparent->name;
		// add the description button
		descrn = maxn+2;
		var.push_back(&descrn);
		buf += "\n\n%i) description of an object";
		// add the back button
		backn = maxn+3;
		var.push_back(&backn);
		buf += "\n%i) back to the top";
		types_listed.push_back(&genobj);
		// print and reset some vectors
		OPS(set, buf, &var[0]);
		ivar.resize(0);		// capacity is still = number!
		var.resize(0);
		
		// make indexes start from 0
		maxn--;
		genericn--;
		descrn--;
		backn--;
		
		// scan the input as long as a valid number is given
		do {
			cin >> input;
			input--;
		}
		while ((input < 0) || (input > descrn));
		
		// if the value point to a type, set this type as pointer and continue if the type is parent of some type, else exit the loop
		if (input <= maxn) {
			BYTE flag = NO;		// NO if the type haven't any child  
			commonparent = types_listed[input];
			for(int i=0; i!=number; i++) {
				if(commonparent == t[i].parent)
					flag = YES;
			}
			if(flag == NO) 
				return *types_listed[input];
		}
		// if is the generic xxx button
		else if (input == genericn)
			return *commonparent;
		// if is the description button
		else if (input == descrn) {
			int n;
			type *type_descr;	// the type described
			// output
			buf = "Of which type of object do you want an explaination?\n";
			for(int i=0; i <= maxn; i++){
				buf += "\n%i) %s";
				ivar.push_back(i+1);
				var.push_back(&ivar[i]);
				var.push_back(&types_listed[i]->name);
			}
			// generic
			buf += "\n%i) %s";
			ivar.push_back(descrn);				// descrn = genericn+1
			var.push_back(&ivar.back());
			var.push_back(&commonparent->name);
			OPS(set, buf, &var[0]);
			var.resize(0);
			ivar.resize(0);
			// input
			cin >> n;
			n--;
			// check that is a valid value
			if ((n < 0) || (n > descrn)) {
				OPS(set, "There is no object whit that number out there! press something to continue...", nullptr);
				sgetchar();
				continue;
			}
			// set the type
			type_descr = types_listed[n];
			buf = "Info about:  ";
			buf += type_descr->name;
			buf += "\n\nDescription: &ti3";
			buf += type_descr->description;
			buf += "&t0";
			buf += "\nUnder the category:&t9 ";
			buf += type_descr->parent->name;
			buf += "&t0";
			// the mass range
			buf += "\nMinimum mass: %l";
			buf += "\nMaximum mass: ";
			var[0] = &type_descr->mass_min;
			buf += "%l";
			var.push_back(&type_descr->mass_max);
			// the color range
			buf += "\nColor range:\n&t9red: %i - %i\ngreen: %i - %i\nblue: %i - %i&t0";
			var.push_back(&type_descr->color_min.red);
			var.push_back(&type_descr->color_max.red);
			var.push_back(&type_descr->color_min.green);
			var.push_back(&type_descr->color_max.green);
			var.push_back(&type_descr->color_min.blue);
			var.push_back(&type_descr->color_max.blue);
			// finalizing the description page
			buf += "\n\nPress something to continue...";
			OPS(set, buf, &var[0]);
			var.resize(0);
			ivar.resize(0);
			sgetchar();
		}
		// if is the back button return to the start
		else if (input == backn)
			commonparent = &genobj;
	}
}
