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
	tcolor Color_black();
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
	tcolor ScanColor(tinf *);
	tcolor ScanColor(tinf *inf) {
		
		tcolor color;	//our color
		//scan them and chek if the value given are true
		scanf("%d", &color.red);
		do {
			if((color.red < 256) && (color.red > -1))
				break;
			OPSE(inf, "The value %i that you have put is wrong. Correct values are between 0 and 255. Type another value for the red component of the color", &color.red, NULL);
			scanf("%d", &color.red);
		}
		while(1);
		OPS(inf, "Put the value of the green:", NULL, NULL);
		scanf("%d", &color.green);
		do {
			if((color.green < 256) && (color.green > -1))
				break;
			OPSE(inf, "The value %i that you have put is wrong. Correct values are between 0 and 255. Type another value for the green component of the color", &color.green, NULL);
			scanf("%d", &color.green);
		}
		while(1);
		OPS(inf, "Put the value of the blue:", NULL, NULL);
		scanf("%d", &color.blue);
		do {
			if((color.blue < 256) && (color.blue > -1))
				break;
			OPSE(inf, "The value %i that you have put is wrong. Correct values are between 0 and 255. Type another value for the blue component of the color", &color.blue, NULL);
			scanf("%d", &color.blue);
		}
		while(1);
		
		return color;
	}
