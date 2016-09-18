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
 * This is the file that contein the core of the SDL interface,
 * Initialization, closing and low-level stuff
 * 
 * 
 * WARNING:
 * 
 * <-!-> HEAVY WORK IN PROGRESS <-!->
 * I'm not jokking. HEAVY wip.
 * 
 */

#include "CS_header.h"
#include <SDL2/SDL.h>

	/*
	 * This function initialize SDL and the window
	 */
	BYTE InitGL(){
		
		inf.gl.win = NULL;	// Our window
		
		// initialize SDL
		if(SDL_Init(SDL_INIT_VIDEO) < 0) {
			char *error = (char *) malloc (sizeof(char[strlen(SDL_GetError())]));
			while(error == NULL){
				OPSML("InitGL");
				error = (char *) malloc (sizeof(char[strlen(SDL_GetError())]));
			}
			void *var = error;
			strcpy(error, SDL_GetError());
			OPSE("Cannot initialize SDL library! Error: %s", &var);
			free(error);
			inf.gl.SDLinit = NO;
			sgetchar();
			SDL_Quit();
			return BADSIGNAL;
		}
		// if the program get here SDL is intialized
		inf.gl.SDLinit = YES;
		// create the window
		inf.gl.win = SDL_CreateWindow("CSpace: The space simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		// Quit if failed to load the window
		if(inf.gl.win == NULL) {
			char *error = (char *) malloc (sizeof(char[strlen(SDL_GetError())]));
			while(error == NULL){
				OPSML("InitGL");
				error = (char *) malloc (sizeof(char[strlen(SDL_GetError())]));
			}
			void *var = error;
			strcpy(error, SDL_GetError());
			OPSE("Cannot create window! SDL Error: %s", &var);
			free(error);
			inf.gl.winopen = NO;
			sgetchar();
			SDL_Quit();
			return BADSIGNAL;
		}
		// If nothing happened, the window is created succefully
		inf.gl.winopen = YES;
		
		return GOODSIGNAL;
		
	}
	
	/*
	 * This function finish the work whit the window and close it
	 */
	void CloseGL() {
		// destroy the window if is created
		if(inf.gl.winopen == YES)
			SDL_DestroyWindow (inf.gl.win);
		// quit SDL if SDL is initialized
		if(inf.gl.SDLinit == YES)
			SDL_Quit ();
	}
