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


 * This is the rendering engine
 * Questo è il motore di rendering
 * 
 * RENDERING ENGINE STRUCTURE
 * 
 * The Shell call Rmotor whit one mode;
 * 
 * if the mode is 0		-->	Onlyprintfsystem (aka OPS)
 * if the mode is 1		--> OPS output (aka OPSo)
 * 
 * The structure is descripted below:
 * 
 * 			|Calling function|
 * 						|
 * 						|
 * 	--------------------|-------------------------
 *						V
 * 	R		  		|Rmotor|------.
 * 	E					|		   \
 * 	N E					V			|
 * 	D N				|OPS   |		|
 * 	E G		 		|output|		V
 * 	R I	 				 \ 		  |Only Printf|
 * 	I N	  				  '-----> |System     |
 * 	N E	   								|
 * 	G	   							    |
 * 			  						   /
 * 	----------------------------------/-----------
 * 									 /
 * 			|Calling Function| <----'
 * 						 
 * 
 * 
 * The function Rmotor amministrates the work and calls more specific function. A function don't calls a specific function of Pmotor, but calls Pmotor specifying what work Pmotor must do, then pmotor call other functions
 * 
*/


	int Rmotor (tsys *sys, tinf *inf, int mode, char *phrase, int *ivar, long double *lvar, char *cvar[]) {

		// The state received
		int staterec;
		
		// String that contein the name of a function
		char string[16];
		
		// Call the correct function
		if (mode==0)
			staterec = OnlyPrintfSystem(inf, phrase);
		if (mode==1)
			staterec = OPSo(sys, inf);
		
		// Control that the function did the work correctly. If not signal it
		if 		(staterec == 0 );
		else {
			if (mode==0)
				strcpy(string[0] , "OnlyPrintfSystem");
			if (mode==1)
				strcpy(string[0] , "OPSOutput");
			Rmotor (sys, inf, 0, "Rmotor's call to %c. It exit whit error: %i\n\nPress a button to continue...",&staterec ,);
			Gets();
		}
		return 0;
	}



