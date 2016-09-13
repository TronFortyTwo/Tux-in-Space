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
 * HERE we are starting to build an OpenGL interface using SDL
 * 
 * This is the file that contein the core of the interface, others will come soon
 * 
 * WARNING:
 * 
 * <-!-> HEAVY WORK IN PROGRESS <-!->
 * 
 */
 
#include "CS_header.h"
#include <SDL2/SDL.h>

	/*
	 * This function initialize SDL and the window
	 */
	BYTE InitGL(){
		/*
		inf.gl.win = NULL;	// Our window
		inf.gl.sur = NULL;
		
		// initialize SDL
		if(SDL_Init(SDL_INIT_VIDEO) < 0) {
			char error[128];	// the error
			void *var = error;
			strcpy(error, SDL_GetError());
			OPSE("Cannot initialize SDL library! Error: %s", &var);
			return BADSIGNAL;
		}
		// create the window
		inf.gl.win = SDL_CreateWindow("CSpace: The space simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		// Quit if failed to load the window
		if(inf.gl.win == NULL) {
			char error[128];
			void *var = error;
			strcpy(error, SDL_GetError());
			OPSE("Cannot create window! SDL Error: %s", &var);
			return BADSIGNAL;
		}
		
		return GOODSIGNAL;
		*/
	}
	
	/*
	 * This function finish the work whit the window and close it
	 */
	void CloseGL(){

	}


	/*
	 * This is the menù that use SDL
	 */
	void DisplayMenu() {
		
		
	}
	
	int GLMenu (tStype *Stype){
		
		return GOODSIGNAL;
	}

	/*
	 * 	This is the simulation(S) graphical(GL) interface(GUI)
	 */

	 void SGLGUI (tsys *sys) {
	
		return;
	}
	
	/*
	 * 	This is the parser using SDL
	 */
	
	ttime GLparser (tsys *sys) {
		
		return sys->stime;
	}
	
	
	/*
	 * 	This is the menu
	 */

	int GlMenu (tStype *Stype) {
		
		return QUITSIGNAL;
	}

	/*
	 * Initialize the system
	 */
	tsys *InitSystemGl(tStype *Stype) {
		
		tsys *sys;
		sys = (tsys *) malloc (sizeof(tsys));
		while (sys == NULL) {
			OPSML("sys");
			sys = (tsys *) malloc (sizeof(tsys));
		}
		
		return sys;
	}

	/*
	 * Load a system
	 */
	tsys *LoadSystemGl(tStype *Stype) {
		
		tsys *sys;
		sys = (tsys *) malloc (sizeof(tsys));
		while (sys == NULL) {
			OPSML("sys");
			sys = (tsys *) malloc (sizeof(tsys));
		}
		
		return sys;
	}




