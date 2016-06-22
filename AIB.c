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
 * This is the AIB. (Abstract Image Builder)
 * This function create an image struct, but whitout print or transform it in a real image renderizing it, because then can be renderized in ASCII, whit a graphic, or in a file
 * The aim for now is to create a function parallel to OPSo but whit a GUI
 * 
 */
 
	//this structure contein a circle
	struct circle {
		double radius;	//the radius of the circle
	};
	typedef struct circle tcircle;
	
	//this structure contein the template of a irregular sprite
	struct irregular {
		// Not supported for now
	};
	typedef struct irregular tirregular;
	
	//this union contein data about the tamplate of a sprite. there are the templates of mean template (like a circle) and a irregular template
	union template {
		tcircle circle;
		tirregular iregg;
		int template;		//define which template is used
	};
	typedef union template ttemplate;
	
	//this struct contein data about a sprite
	struct sprite {
		double x;
		double y;		// coordinates
		double z;
		double deep;	// the deep of the sprite; deepest sprites are covered by nearest.
		ttemplate tamplate;
	};
	typedef struct sprite tsprite;
	
	// The structure that contein an image
	struct image {
		int background;		// background color
		tsprite *sprite;	// pointer to the sprites
		int nsprite;		// the number of sprites
	};
	typedef struct image timage;
