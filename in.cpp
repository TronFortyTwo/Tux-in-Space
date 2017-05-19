/*
#############################################################################################
#    Tux in Space - space simulator															#
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
 * 
 * Here we have function that help whit input
 * 
 */

#include "in.h"

using namespace std;

/***
 * This function scan a line
 * 
 */
void in_s (string& d) {
	char b[256];
	scanf(" %255[^\n]", b);
	d = b;
}

void in_s () {
	char b[256];
	scanf(" %255[^\n]", b);
}

void in_inline_s(std::string& s){
	cin >> s;
}

/***
 * Scan a string WHIT space, to use when scanning a name, a type... but from a file
 * 
 * */
void in_fs (string& dest, istream& stream) {
	
	getline(stream, dest);
}

/***
 * Scan a string like in_fs but whit support for comments, indentation
 */
void in_hfs (string& dest, istream& stream) {
	while(1) {
		getline(stream, dest);
		
		while(1) {
			if(!dest.length())
				break;
			if((dest[0] == ' ') || (dest[0] == '\t')) {
				dest.erase(dest.begin());
				continue;
			}
			if(dest[0] == '#')
				break;
			else
				return;
		}
	}
}


int in_i() {
	
	string s;
	
	in_s(s);
	
	return stoi(s);
}

int in_fi(istream& f) {
	
	string s;
	
	in_fs(s, f);
	
	return stof(s);
}

float in_f() {
	
	string s;
	
	in_s(s);
	
	return stof(s);
}

float in_ff(istream& f) {
	
	string s;
	
	in_fs(s, f);
	
	return stof(s);
}

double in_d() {
	
	string s;
	
	in_s(s);
	
	return stod(s);
}


long double in_ld() {
	
	string s;
	
	in_s(s);
	
	return stold(s);
}

long double in_fld(istream& f) {
	
	string s;
	
	in_fs(s, f);
	
	return stold(s);
}

int in_inline_i(){
	
	string s;
	
	if(!(cin >> s))
		return in_inline_i();
	
	return stoi(s);
}

void in_clear(){
	cin.ignore(999999, '\n');
}
