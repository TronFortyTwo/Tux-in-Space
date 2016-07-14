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
*/

/***
 * This is CSpace's header file
 * 
 */

	#define PI (245850922/78256779)
	
	// The three axis must have different codes
	#define X_AXIS 0
	#define Y_AXIS 1
	#define Z_AXIS 2
	
	// The number of space when a description
	#define THEETDESCR 5
	
	// The value that the variable ttime.year assumes if the user want to quit
	#define QUITSIGNAL -1
	
	// The lenght of a name of an object, a system or a type
	#define NAMELUN 32
	
	// The size of a type's description. It must is bigger than NAMELUN
	#define DESCRIPTIONSIZE 512
	
	//the size of a buffer of character
	#define BUFFERSIZE 1024
	
	//max lenght of the buffer used by SafeScan function
	#define BUFFERINPUTSIZE 25
	
	// the max lenght of a command word
	#define COMMANDLENGHT 12
	
	//When you alloc the object buffer, this is how many object you delete or create when you resize
	#define OBJBUFSIZE 8
	
	// The frame that Rmotor uses and his size
	#define FRAME "# "
	#define FRAMER " #"		// FRAME R(ight)
	#define FRAMELUN 2		// FRAME LENGHT
	#define TWOFRAMELUN 4	// 2 * FRAME LENGHT
	#define FRAMESTART "#"
	#define FRAMEEND " "

	//the type that we use as color
	struct scolor{
		int red;
		int green;
		int blue;
	};
	typedef struct scolor tcolor;
	
	// The structure that represent a type of a object
	struct sStype {
		char name [NAMELUN];
		char description [DESCRIPTIONSIZE];
		char parent [NAMELUN];
		double mass_min;		// Mass range
		double mass_max;
		tcolor color_max;		// Color range
		tcolor color_min;		
	};
	typedef struct sStype ttype;
	
	// The structure whit all the types
	struct TypesStruct {
		int number;
		ttype *type;			// This is a pointer to the first member of the arrays that conteins all the types
	};
	typedef struct TypesStruct tStype;

	// The structure infostruct is a structure that contein information about the options and other tecnical things 
	struct info {
		int vmode;					// Visual mode (0 = Only OPS)
		int width;					// The number of columns that the program use
		int height;					// The number of lines that the program use
		int numprecision;			// Number of character used for printing the deciamal of a long double
		int view_axis;				// Information about the point of view (for AIB)
		long double view_distance;
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
		tcolor color;			// the color
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

// External standard library
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <math.h>
	#include <time.h>
	
// Prototypes
	void DistanceCommand(tsys *, tinf *);
	void AIB_ASCII_renderizer (tsys *, tinf *);
	long double Pitagora(long double, long double, long double);
	long double Pitagora2D(long double a, long double b);
	void DeleteObject(tinf *, tsys *);
	ttime Quit (tsys *, tinf *, ttime *);
	tobj *SearchObject(tsys *, char *);
	void Info(tsys *sys, tinf *);
	int GetBiggerStime(ttime *, ttime *);
	void UpdateTime(ttime *);
	void OPS(tinf *, char *, int *, long double *);
	void OPSE(tinf *, char *, int *, long double *);
	void OPSML(tinf *, char *);
	ttime Jump(ttime *, tinf *, long double *);
	ttime Wait(ttime *, tinf *, long double *);
	int Menu(tinf *, tStype *);
	int OPSo (tsys *, tinf *);
	ttime Parser(tsys *, tinf *);
	void Reask(tinf *, char *);
	void SaveSys(tsys *sys, tinf *);
	void Create(tsys *, tinf *);
	ttype *TypeBrowser(tinf *, tStype *, char *);
	void Pmotor (tsys *, tinf *);
	int Shell (tinf *, tStype *);
	void SafeIScan(tinf *, int *);
	void PrintLine (tinf *, char *, int);
	void ScanFString(char *, FILE *);	
	void SaveObject(tinf *, tobj *);
	void InitObject (tinf *, tobj *, tStype *, int);
	tsys *InitSystem (tinf *, tStype *);
	void ReduceObjBuf(tsys *sys, tinf *);
	tStype *Inittype (FILE *, tinf *);
	char *typeDescriptionFromName (tStype *, char *);
	ttype *typeSearchName (tStype *, char *);
	char *typeParentFromName (tStype *, char *);
 
// CSpace's functions sorted by dependance (so DON'T MODIFY the order if you don't want to fight dozen of gcc's error)
	#include "debug.c"
	#include "color.c"
	#include "AIB.c"
	#include "string functions.c"
	#include "type.c"
	#include "system functions.c"
	#include "OnlyPrintfSystem.c"
	#include "OPSo.c"
	#include "menù.c"
	#include "pmotor.c"
	#include "Parser.c"
	#include "shell.c"
