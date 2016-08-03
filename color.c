/*
#############################################################################################
#    CSpace - space simulator																#
#    Copyright (C) 2016  emanuele.sorce@hotmail.com											#
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
 * In this file there are things correlated whit colors
 */
	
/***
 * The Color_black return the black color
 */
	tcolor Color_black(){
		tcolor black;
		black.red = 0;
		black.green = 0;
		black.blue = 0;
		return black;
	}
 
/***
 * The ScanColor function get a color and return it
 */
	tcolor ScanColor(tinf *inf, tcolor range_min, tcolor range_max) {
		
		DebugPrint(inf, "scancolor");
		
		tcolor color;	//our color
		void *var[3];	//the vars to give to OPS
		
		// scan them and chek if the value given are true
		// red
		var[0] = &range_min.red;
		var[1] = &range_max.red;
		OPS(inf, "Put the value of the red:\n&tdThe value must be between %i and %i", var);
		scanf("%d", &color.red);
		do {
			if((color.red <= range_max.red) && (color.red >= range_min.red))
				break;
			var[0] = &color.red;
			var[1] = &range_min.red;
			var[2] = &range_max.red;
			OPSE(inf, "The value %i that you have put is wrong. Correct values are between %i and %i. Type another value for the red component of the color", var);
			scanf("%d", &color.red);
		}
		while(1);
		// green
		var[0] = &range_min.green;
		var[1] = &range_max.green;
		OPS(inf, "Put the value of the green:\n&tdThe value must be between %i and %i", var);
		scanf("%d", &color.green);
		do {
			if((color.green <= range_max.green) && (color.green >= range_min.green))
				break;
			var[0] = &color.green;
			var[1] = &range_min.green;
			var[2] = &range_max.green;
			OPSE(inf, "The value %i that you have put is wrong. Correct values are between %i and %i. Type another value for the green component of the color", var);
			scanf("%d", &color.green);
		}
		while(1);
		// blue
		var[0] = &range_min.blue;
		var[1] = &range_max.blue;
		OPS(inf, "Put the value of the blue:\n&tdThe value must be between %i and %i", var);
		scanf("%d", &color.blue);
		do {
			if((color.blue <= range_max.blue) && (color.blue >= range_min.blue))
				break;
			var[0] = &color.blue;
			var[1] = &range_min.blue;
			var[2] = &range_max.blue;
			OPSE(inf, "The value %i that you have put is wrong. Correct values are between %i and %i. Type another value for the green component of the color", var);
			scanf("%d", &color.blue);
		}
		while(1);
		
		return color;
	}
	
	/***
	 * This function check if the color given is in or out the color range given
	 */
	int ColorRangeCheck(tcolor color, tcolor min, tcolor max) {
		
		if(color.red < min.red)
			return BADSIGNAL;
		if(color.green < min.green)
			return BADSIGNAL;
		if(color.blue < min.blue)
			return BADSIGNAL;
		if(color.red > max.red)
			return BADSIGNAL;
		if(color.green > max.green)
			return BADSIGNAL;
		if(color.blue > max.blue)
			return BADSIGNAL;
		
		return GOODSIGNAL;
	}
