/*
#############################################################################
#    CSpace - space simulator												#
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
	
	const void *var[3];	// the vars to give to OPS
		
	// scan them and chek if the value given are true
	// red
	var[0] = &range_min.red;
	var[1] = &range_max.red;
	OPS(set, "Put the value of the red:\n&tdThe value must be between %i and %i", var);
	cin >> red;
	while(1) {
		if((red <= range_max.red) && (red >= range_min.red))
			break;
		var[0] = &red;
		var[1] = &range_min.red;
		var[2] = &range_max.red;
		OPS_Error(set, "The value %i that you have put is wrong. Correct values are between %i and %i. Type another value for the red component of the color", var);
		scanf("%d", &red);
	}
	// green
	var[0] = &range_min.green;
	var[1] = &range_max.green;
	OPS(set, "Put the value of the green:\n&tdThe value must be between %i and %i", var);
	cin >> green;
	while(1) {
		if((green <= range_max.green) && (green >= range_min.green))
			break;
		var[0] = &green;
		var[1] = &range_min.green;
		var[2] = &range_max.green;
		OPS_Error(set, "The value %i that you have put is wrong. Correct values are between %i and %i. Type another value for the green component of the color", var);
		scanf("%d", &green);
	}
	// blue
	var[0] = &range_min.blue;
	var[1] = &range_max.blue;
	OPS(set, "Put the value of the blue:\n&tdThe value must be between %i and %i", var);
	cin >> blue;
	while(1) {
		if((blue <= range_max.blue) && (blue >= range_min.blue))
			break;
		var[0] = &blue;
		var[1] = &range_min.blue;
		var[2] = &range_max.blue;
		OPS_Error(set, "The value %i that you have put is wrong. Correct values are between %i and %i. Type another value for the green component of the color", var);
		scanf("%d", &blue);
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
