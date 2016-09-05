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
	 * This function clear the window
	 */
	void ClearWindow() {
		 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glutSwapBuffers();
	}
	
	/*
	 * This function reshape the window
	 */
	void ChangeSize(int w, int h) {
		
		// Prevent a divide by zero, when window is too short
		if(h == 0)
			h = 1;
		float ratio = 1.0 * w / h;

		// Use the Projection Matrix
		glMatrixMode(GL_PROJECTION);
        // Reset Matrix
		glLoadIdentity();
		// Set the viewport to be the entire window
		glViewport(0, 0, w, h);
		// Set the correct perspective.
		gluPerspective(45,ratio,1,1000);
		// Get Back to the Modelview
		glMatrixMode(GL_MODELVIEW);
	}
	 
	/*
	 * This function initialize freeGLUT and the window
	 */
	void InitGL(int argc, char *argv[]){
		
		// initializing
		glutInit(&argc, argv);
		glutInitWindowPosition(inf.gl.winx, inf.gl.winy);
		glutInitWindowSize(inf.gl.winw, inf.gl.winh);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
		// create the window
		inf.gl.wincode = glutCreateWindow("CSpace, the space simulator");
		inf.gl.winopen = YES;
		// clean the window and start the loop
		glutDisplayFunc(ClearWindow);
		glutReshapeFunc(ChangeSize);
		glutMainLoopEvent();
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
	void DisplayMenu() {
		
		
	}
	
	int GLMenu (tStype *Stype){
		
		glutDisplayFunc(DisplayMenu);
		glutMainLoop();
		
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




