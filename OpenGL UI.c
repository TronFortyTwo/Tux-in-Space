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
 * HERE we are starting to build an OpenGL interface using FreeGLUT
 * 
 * WARNING:
 * 
 * <-!-> HEAVY WORK IN PROGRESS <-!->
 * 
 */


	/*
	 * This function initialize freeGLUT and the window
	 */
	void InitGL(int argc, char *argv[]){
		
		// initialize lut and window
		glutInit(&argc, argv);
		glutInitWindowPosition (inf.gl.winx, inf.gl.winy);
		glutInitWindowSize (inf.gl.winw, inf.gl.winh);
		glutInitDisplayMode (GLUT_RGBA);
		// create the window
		inf.gl.wincode = glutCreateWindow("CSpace, the space simulator");
		inf.gl.winopen = YES;
		
		return;
	}
	
	/*
	 * This function finish the work whit the window and close it
	 */
	void CloseGL(){
		
		glutDestroyWindow(inf.gl.wincode);
		
	}


	/*
	 * This is the menù that use FreeGLUT
	 */
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
	 * 	This is the parser using FreeGLUT
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




