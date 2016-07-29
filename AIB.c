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
		double y;				// coordinates
		double z;
		double deep;			// the deep of the sprite; deepest sprites are covered by nearest.
		ttemplate template;
	};
	typedef struct Sprite tsprite;
	
	// The structure that contein an image
	struct Image {
		tcolor background;	// background color
		tsprite *sprite;	// pointer to the sprites
		int nsprite;		// the number of sprites
	};
	typedef struct Image timage;

	/** 
	 * the function AIB that draw in an image structure what happen in the system structure given
	 * (Abstract Image Builder)
	 */
	timage AIB (tsys *sys, tinf *inf) {
		DebugPrint(inf, "AIB");
		timage image;	// the image
		int i, c;		// counters for loops
		int *l;			// the state of the frames
		tsprite *news;	// a temp array of sprite
		int nums;		// temp number of sprite
		
		// set the background black (we are in the space)
		image.background = Color_black();
		// set the number of frames
		image.nsprite = sys->nactive;
		// alloc spaces for the sprites and check for correct allocation
		image.sprite = (tsprite *) malloc (sizeof(tsprite) * image.nsprite);
		do{	if (image.sprite != NULL)	break;
			OPSML(inf, "AIB");
			image.sprite = (tsprite *) malloc (sizeof(tsprite) * image.nsprite);
		} while(1);
	
		// NOTE: the view point is in the axis defined in inf.view_axis at a distance from the center defined in inf.view_distance

		// THE OBJECTS
		// take every object and create his sprite
		for (i=0; i!=sys->nactive-1; i++) {
			//for now all the objects are spheres
			image.sprite[i].template.which = TEMPLATE_CIRCLE;
			//set the coordinate and the deepest
			if (inf->view_axis == X_AXIS) {
				image.sprite[i].x = sys->o[i].y;
				image.sprite[i].y = sys->o[i].z;
				image.sprite[i].deep = inf->view_distance - sys->o[i].x;
			}
			else if (inf->view_axis == Y_AXIS) {
				image.sprite[i].x = sys->o[i].x;
				image.sprite[i].y = sys->o[i].z;
				image.sprite[i].deep = inf->view_distance - sys->o[i].y;
			}
			else if (inf->view_axis == Z_AXIS) {
				image.sprite[i].x = sys->o[i].x;
				image.sprite[i].y = sys->o[i].y;
				image.sprite[i].deep = inf->view_distance - sys->o[i].z;
			}
			//set the template information
			if (image.sprite[i].template.which == TEMPLATE_CIRCLE)
				image.sprite[i].template.circle.radius = sys->o[i].radius / image.sprite[i].deep;
		}
		
		// DELETE FRAMES COVERED OR OUT OF RANGE
		l = (int *) malloc (sizeof(int) * image.nsprite);
		if(l == NULL)
			do {
				OPSML(inf, "Abstract image builder");
				l = (int *) malloc (sizeof(int) * image.nsprite);
				if(l != NULL)
					break;
			}
			while(1);
		// Set all the sprite to 'ok'
		for (i=0; i!=image.nsprite; i++) {
			l[i] = 0;
		}
		// If a sprite is behind the point of view sign it
		for (i=0; i!=image.nsprite; i++) {
			if(image.sprite[i].deep <= 0)
				l[i]++;
		}
		// sign the sprites covered by other sprites NOW ONLY WORK FOR CIRCLE
		for (i=0; i!=image.nsprite; i++) {
			for (c=0; c < image.nsprite; c++) {
				// if are the same sprite continue
				if (i == c)
					continue;
				// if the sprite i is smaller than c continue (because can't cover c)
				if (image.sprite[i].template.circle.radius < image.sprite[c].template.circle.radius)
					continue;
				// if the sprite i is deeper than c continue (bacause can't cover c)
				if (image.sprite[i].deep >= image.sprite[c].deep)
					continue;
				// if the sprite i cover c, sign c (distance + c's radius must be < than i's radius if i cover c)
				if (Pitagora2D(image.sprite[i].x-image.sprite[c].x, image.sprite[i].y-image.sprite[c].y)+image.sprite[c].template.circle.radius <= image.sprite[i].template.circle.radius)
					l[c]++;
			}
		}
		//count how many frames aren't signed
		for (i=0, nums=0; i!=image.nsprite; i++) {
			if(l[i] == 0)
				nums++;
		}
		// create a new array of sprites whitout the sprites signed
		news = (tsprite *) malloc (sizeof(tsprite) * nums);
		for (i=0, c=0; i!=image.nsprite; i++){
			if(l[i] == 0) {
				news[c] = image.sprite[i];
				c++;
			}
		}
		image.nsprite = nums;
		
		//free the memory and exit
		free(l);
		
		return image;
	}

/***
 * The AIB ASCII renderizer renderizes the image created by the AIB and print it
 */
	void AIB_ASCII_renderizer (tsys *sys, tinf *inf) {
		DebugPrint(inf, "aib_ascii_renderizer");
		//counter for loop
		int i;
		
		// the image to renderize
		timage image;		
		image = AIB(sys, inf);
		
		//the video buffer to print
		char *buffer;
		do {
			buffer = (char *) malloc (sizeof(char[(inf->height-5) * (inf->width-TWOFRAMELUN)]));
			if(sys != NULL)
				break;
			OPSML(inf, "AIB ASCII renderizer");
		}
		while(1);
		
		buffer[0] = '2';
		
		//start to renderize
		for (i=0; i>image.nsprite; i++) {
			
		}
		
		//free the memory and exit
		free(image.sprite);
		return;
	}
