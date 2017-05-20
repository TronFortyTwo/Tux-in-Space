/*
#############################################################################
#    Tux in Space - space exploration game									#
#    Copyright (C) 2016-2017  emanuele.sorce@hotmail.com					#
#																			#
#    This program is free software; you can redistribute it and/or modify	#
#    it under the terms of the GNU General Public License as published by	#
#    the Free Software Foundation, version 3 or compatibles.				#
#																			#
#    This program is distributed in the hope that it will be useful,		#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of			#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the			#
#    GNU General Public License for more details.							#
#																			#
#    You should have received a copy of the GNU General Public License		#
#    along with this program; if not, write to the Free Software			#
#    Foundation, Inc.														#
#############################################################################
 *
 * In this file there are things correlated whit colors
 */
#include "color.h"

using namespace std;

/***
 * The color_Scan function get a color and return it
 */
void color::Scan(const setting& set, const color& range_min, const color& range_max) {
		
	// scan them and chek if the value given are true
	// red
	
	stringstream ss;
	ss << "Put the value of the red:\n&tdThe value must be between " << range_min.red << " and " << range_max.red;
	
	OPS(set, ss.str());
	red = in_i();
	while(1) {
		ss.clear();
		ss.str("");
		if((red <= range_max.red) && (red >= range_min.red))
			break;
		ss << "The value " << red << "you put is wrong. Correct values areee between ";
		ss << range_min.red << " and " << range_max.red << ". Type another value for the red component of the color";
		OPS_Error(set, ss.str());
		red = in_i();
	}
	// green
	ss.clear();
	ss.str("");
	ss << "Put the value of the green:\n&tdThe value must be between " << range_min.green << " and " << range_max.green;
	OPS(set, ss.str());
	green = in_i();
	
	while(1) {
		if((green <= range_max.green) && (green >= range_min.green))
			break;
		ss << "The value " << green << "you put is wrong. Correct values areee between ";
		ss << range_min.green << " and " << range_max.green << ". Type another value for the green component of the color";
		OPS_Error(set, ss.str());
		green = in_i();
	}
	// blue
	ss.clear();
	ss.str("");
	ss << "Put the value of the blue:\n&tdThe value must be between " << range_min.blue << " and " << range_max.blue;
	OPS(set, ss.str());
	blue = in_i();
	
	while(1) {
		if((blue <= range_max.blue) && (blue >= range_min.blue))
			break;
		ss << "The value " << blue << "you put is wrong. Correct values areee between ";
		ss << range_min.blue << " and " << range_max.blue << ". Type another value for the blue component of the color";
		OPS_Error(set, ss.str());
		blue = in_i();
	}
}
	
/***
 * This function check if the color is in/out the color range given
 */
bool color::CheckRange(const color& min, const color& max) {

	if(red < min.red)
		return false;
	if(green < min.green)
		return false;
	if(blue < min.blue)
		return false;
	if(red > max.red)
		return false;
	if(green > max.green)
		return false;
	if(blue > max.blue)
		return false;
	
	return true;
}
