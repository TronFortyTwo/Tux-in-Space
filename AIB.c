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
	//this are the code that refer to a template (see template.which)
	#define TEMPLATE_IRREGULAR 0
	#define TEMPLATE_POINT 1
	#define TEMPLATE_CIRCLE 2
	
	//this structure contein a circle
	struct Circle {
		double radius;	//the radius of the circle
	};
	typedef struct Circle tcircle;
	
	//this structure contein the template of a irregular sprite
	struct Irregular {
		// Not supported for now
	};
	typedef struct Irregular tirregular;
	
	//this union contein data about the tamplate of a sprite. there are the templates of mean template (like a circle) and a irregular template
	union Template {
		tcircle circle;
		tirregular iregg;
		int which;		//define which template is used
						//if is TEMPLATE_POINT, there's no need to a structure because point haven't any data to store
	};
	typedef union Template ttemplate;
	
	//this struct contein data about a sprite
	struct Sprite {
		double x;
		double y;		// coordinates
		double z;
		double deep;	// the deep of the sprite; deepest sprites are covered by nearest.
		ttemplate template;
	};
	typedef struct Sprite tsprite;
	
	// The structure that contein an image
	struct Image {
		tcolor background;	// background color (256 colors max for now)
		tsprite *sprite;	// pointer to the sprites
		int nsprite;		// the number of sprites
	};
	typedef struct Image timage;

	/** 
	 * the function AIB that draw in an image structure what happen in the system structure given
	 * (Abstract Image Builder)
	 */
	timage AIB (tsys *sys, tinf *inf) {
		
		timage image;	//the image
		int i;			//counter for loops
		
		// set the background black (we are in the space)
		image.background = Color_black();
		// set the number of frame
		image.nsprite = sys->nactive;
		// alloc spaces for the sprites and check for correct allocation
		image.sprite = (tsprite *) malloc (sizeof(tsprite) * image.nsprite);
		do{	if (image.sprite != NULL)	break;
			OPSML(inf, "AIB");
			image.sprite = (tsprite *) malloc (sizeof(tsprite) * image.nsprite);
		} while(1);
	
		//the view point is in an axis. Can be

		for (i=0; i!=sys->nactive; i++) {
			
		}

		return image;
	}
