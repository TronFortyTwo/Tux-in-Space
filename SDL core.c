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
 * WARNING:
 * 
 * <-!-> HEAVY WORK IN PROGRESS <-!->
 * 
 */
	/*
	 * This function initialize SDL and the window
	 */
	void InitGL(int argc, char *argv[]){
		
	
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




