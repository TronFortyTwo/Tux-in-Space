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


#########################################################################################################################################################################################################
# This is the Main function of the program but doesn't do much, is a launchpad for compiling and esecution, is a collection of structures for the other functions and contein file's initialization		#
#########################################################################################################################################################################################################
*/

	// include definition of constants
	#include "constants.h"
	
	
	// The structure that represent a type of a object
	struct objtype {
		char name [NAMELUN];
		char description [DESCRIPTIONSIZE];
		char parent [NAMELUN];
	};
	typedef struct objtype ttype;
	
	// The structure whit all the types
	struct TypesStruct {
		int number;
		ttype *type;			// This is a pointer to an array
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
		char type [NAMELUN];	// the type of object.
		long double mass;		// the mass
		long double x;   		// the coordinate x
		long double y;			// the coordinate y
		long double z;			// the coordinate z
		long double velx;		// the fast of the movement in x
		long double vely;		// the fast of the movement in y
		long double velz;		// the fast of the movement in z
	};
	typedef struct object tobj;
	
	// one system's structure: include the objects, the name and the number, the active object's position, the time of the system and the G constant of universal gravitation
	struct system {
		char name [NAMELUN];
		float precision;	// Precision of the simulation (in second). [Pmotor needs it]
		int year;
		int day;
		int hour;
		int min;
		int sec;
		int millisec;
		int nactive;		//number of objects active
		int nalloc;			//number of objects allocated
		tobj *o;			//the pointer to the dinamic allocated array of objects
		long double G;
		tStype *Stype;		// The pointer at the structure that coontein all the type
	};
	typedef struct system tsys;


	// Include the header file
	#include "CS_header.h"

	// Funzione principale

	int main (int argc, char *argv[]) {
		
		// definition of the structures
		tinf inf;
		tsys sys;
		
		// The types file
		FILE *Ftype;
		
		//an input variable
		char input;
		
		
		// default things for struct inf are setted.
		// height and width are respectively the number of height and width that Rmotor can use for printing
		inf.height = 50;
		inf.width = 100;
		
		//print that is loading
		OPS(&inf, "LOADING CSPACE........\n\nCSpace - space simulator\n\nCopyright (C) 2016  emanuele.sorce@hotmail.com\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or compatibles", 0, 0);
		
		// the vmode is setted 0 (onlyOPS)
		inf.vmode = 0;
	
		// the precision is setted 1 calcolation every 2 second
		sys.precision = 2;
		
		// set num precision
		inf.numprecision = 4;
		
		// Read the a file and load the types
		Ftype = fopen("types.typ", "r");
		if(Ftype != NULL) {
			sys.Stype = Inittype(Ftype, &inf);
			fclose(Ftype);
		}
		else {
			OPSE(&inf, "Can't open type.typ file whit definition of object's type. Program can works whit problems and issues", 0, 0);
			scanf("%c", &input);
		}

		// call the shell
		Shell (&sys, &inf);
		
		//free the memory
		free(sys.Stype);
		
		return 0;
	}
