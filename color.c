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
 ///prototypes
	tcolor Color_black();
	tcolor ScanColor(tinf *, tcolor, tcolor);
	
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
		
		tcolor color;	//our color
		int ivar[3];	//the var to give to OPS
		
		//scan them and chek if the value given are true
		//red
		scanf("%d", &color.red);
		do {
			if((color.red <= range_max.red) && (color.red >= range_min.red))
				break;
			ivar[0] = color.red;
			ivar[1] = range_min.red;
			ivar[2] = range_max.red;
			OPSE(inf, "The value %i that you have put is wrong. Correct values are between %i and %i. Type another value for the red component of the color", ivar, NULL);
			scanf("%d", &color.red);
		}
		while(1);
		//green
		ivar[0] = range_min.green;
		ivar[1] = range_max.green;
		OPS(inf, "Put the value of the green:\n&tdThe value must be between %i and %i", ivar, NULL);
		scanf("%d", &color.green);
		do {
			if((color.green <= range_max.green) && (color.green >= range_min.green))
				break;
			ivar[0] = color.green;
			ivar[1] = range_min.green;
			ivar[2] = range_max.green;
			OPSE(inf, "The value %i that you have put is wrong. Correct values are between %i and %i. Type another value for the green component of the color", ivar, NULL);
			scanf("%d", &color.green);
		}
		while(1);
		//blue
		ivar[0] = range_min.blue;
		ivar[1] = range_max.blue;
		OPS(inf, "Put the value of the blue:\n&tdThe value must be between %i and %i", ivar, NULL);
		scanf("%d", &color.blue);
		do {
			if((color.blue <= range_max.blue) && (color.blue >= range_min.blue))
				break;
			ivar[0] = color.blue;
			ivar[1] = range_min.blue;
			ivar[2] = range_max.blue;
			OPSE(inf, "The value %i that you have put is wrong. Correct values are between %i and %i. Type another value for the green component of the color", ivar, NULL);
			scanf("%d", &color.blue);
		}
		while(1);
		
		return color;
	}
