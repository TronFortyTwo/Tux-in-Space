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
 * This is the file that contein the core of the SDL interface
 * 
 * WARNING:
 * 
 * <-!-> HEAVY WORK IN PROGRESS <-!->
 * 
 */


#include "generic.h"
#include "SDL_interface.h"
#include <SDL2/SDL.h>
#include "OnlyPrintfSystem.h"


//
// This is the menù that use SDL
//
int Video_Menu (tStype *Stype) {
	// the (ren)derer
	SDL_Renderer *ren;
	// the (sur)face
	SDL_Surface *sur;
	// the (tex)ture
	SDL_Texture *tex;
	
	// initialize the renderer
	ren = SDL_CreateRenderer(set.gl.win, -1, SDL_RENDERER_ACCELERATED);
	while (ren == NULL) {
		OPS_Error("Can't Create a renderer! Press something to retry", NULL);
		sgetchar();
		ren = SDL_CreateRenderer(set.gl.win, -1, SDL_RENDERER_ACCELERATED);
	}
	// initialize the background
	sur = SDL_LoadBMP("images/menu_background");
	while (sur == NULL) {
		OPS_Error("Can't load menù background! Press something to retry", NULL);
		sgetchar();
		sur = SDL_LoadBMP("images/menu_background");
	}
	// Renderer the background
	tex = SDL_CreateTextureFromSurface(ren, sur);
	if (tex == NULL){
		OPS_Error("Can't render the texture! press something to retry", NULL);
		sgetchar();
		tex = SDL_CreateTextureFromSurface(ren, sur);
	}
	SDL_FreeSurface(sur);
	// a loop that wait for a user interaction to exit whit a result
	while(1) {
		// clear the renderer
		SDL_RenderClear(ren);
		// draw the texture
		SDL_RenderCopy(ren, tex, NULL, NULL);
		// update the screen
		SDL_RenderPresent(ren);
		// pause to the next frame
		SDL_Delay( (uint32_t) set.gl.framerate);
	}
	
	SDL_DestroyRenderer(ren);
	SDL_DestroyTexture(tex);
	
	return BADSIGNAL;
}

//
// 	This is the simulation(S) graphical(GL) interface(GUI). Corrispond to the ascii OPSo
//
void Video_SimGUI (tsys *sys) {

	return;
}
	
//
// 	This is the parser using SDL
//
ttime Video_parser (tsys *sys) {
	
	return sys->stime;
}


//
// Initialize the system
//
tsys *InitSystemGl(tStype *Stype) {
		
	tsys *sys = (tsys *) malloc (sizeof(tsys));
	while (sys == NULL) {
		OPS_MemLack("sys");
		sys = (tsys *) malloc (sizeof(tsys));
	}
	sys->o = NULL;
		
	return sys;
}

//
// Load a system
//
tsys *LoadSystemGl(tStype *Stype) {
		
	tsys *sys = (tsys *) malloc (sizeof(tsys));
	while (sys == NULL) {
		OPS_MemLack("sys");
		sys = (tsys *) malloc (sizeof(tsys));
	}
	sys->o = NULL;
	
	return sys;
}
