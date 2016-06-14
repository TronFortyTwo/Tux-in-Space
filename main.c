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


#################################################################################################################################################################################################################
# This is the Main function of the program but doesn't do much, is a launchpad for compiling and esecution, is a collection of structures definitions for the other functions and contein file's initialization	#
#################################################################################################################################################################################################################
*/

	// include definition of constants
	#include "constants.h"
	
	
	// The structure that represent a type of a object
	struct zStype {
		char name [NAMELUN];
		char description [DESCRIPTIONSIZE];
		char parent [NAMELUN];
	};
	typedef struct zStype ttype;
	
	// The structure whit all the types
	struct TypesStruct {
		int number;
		ttype *type;			// This is a pointer to the first member of the arrays that conteins all the types
	};
	typedef struct TypesStruct tStype;

	// The structure infostruct is a structure that contein information about the options and other tecnical things 
	struct info {
		// Visual mode (0 = Only OPS)
		int vmode;
		// The number of columns and lines that Rmotor's function must use.
		int width;
		int height;
		// number of character used for printing the deciamal of a long double
		int numprecision;
	};
	typedef struct info tinf;

	// definition of the type of the object's structures
	// structure of one object
	struct object {
		char name [NAMELUN];	// the name of the object (es.: Earth, My_Planet, Moon)
		ttype *type;			// the type of object.
		long double	radius;		// the object for now are sphere, so this is the ray
		long double mass;		// the mass
		long double x;   		// the coordinate x
		long double y;			// the coordinate y
		long double z;			// the coordinate z
		long double velx;		// the fast of the movement in x
		long double vely;		// the fast of the movement in y
		long double velz;		// the fast of the movement in z
	};
	typedef struct object tobj;
	
	//in this structure is conteined a moment
	struct time {
		int year;
		int day;
		int hour;
		int min;
		int sec;
		int millisec;
	};
	typedef struct time ttime;
	
	// one system's structure: include the objects, the name and the number, the active object's position, the time of the system and the G constant of universal gravitation
	struct system {
		char name [NAMELUN];
		long double precision;	// Precision of the simulation (in second). [Pmotor needs it]
		ttime stime;			// the time of the simulation
		int nactive;			// number of objects active
		int nalloc;				// number of objects allocated
		tobj *o;				// the pointer to the dinamic allocated array of objects
		long double G;
		tStype *Stype;			// The pointer at the structure that coontein all the type
	};
	typedef struct system tsys;


	// Include the header file
	#include "CS_header.h"

	// Funzione principale

	int main (int argc, char *argv[]) {
		
		// INITIALIZATION
		
		// definition of the structures
		tinf inf;
		tStype *Stype;
		
		// The types file
		FILE *Ftype;
		
		//an input variable
		char input[2];
		
		// default things for struct inf are setted.
		// height and width are respectively the number of height and width that Rmotor can use for printing
		inf.height = 44;
		inf.width = 180;
		
		//print that is loading
		OPS(&inf, "LOADING CSPACE........\n\nCSpace - space simulator\n\nCopyright (C) 2016  emanuele.sorce@hotmail.com\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or compatibles", 0, 0);
		
		// the vmode is setted 0 (onlyOPS)
		inf.vmode = 0;
		
		// set num precision
		inf.numprecision = 4;
		
		// Read the types from a file
		Ftype = fopen("type.typ", "r");
		if(Ftype != NULL) {
			Stype = Inittype(Ftype, &inf);
			fclose(Ftype);
		}
		else {
			OPSE(&inf, "Can't open the file type.typ conteiner of the definitions of object's types\nPress a button to exit the program", 0, 0);
			scanf("%s", input);
			return 0;
		}

		// RUNNING THE PROGRAM
		do{
			// call the shell
			Shell (&inf, Stype);
		}
		while(1);
		
		// EXITING
		
		// free the memory
		free(Stype);
		
		return 0;
	}
