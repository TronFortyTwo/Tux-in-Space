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
 * This is CSpace header file
 * 
 */
 
	// External standard library
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <math.h>
	#include <time.h>
	#include <limits.h>
	#include <stdint.h>


	#define PI (245850922/78256779)
	
	// BYTE values
	#define ON 1
	#define OFF 0
	#define NO OFF
	#define YES ON
		
	// The three axis must have different codes
	#define X_AXIS 0
	#define Y_AXIS 1
	#define Z_AXIS 2
	
	// The number of space in '&td'
	#define THEETDESCR 5
	
	// A three char string that represent a picture of ALLERT or ATTENCTION
	#define IRREGULARITY "(!)"
	
	// Values returned by functions (the two mean)
	#define GOODSIGNAL 1
	#define BADSIGNAL 2	
	// Advanced returned signals
	#define FILE_ERR_SIG 3
	#define CORRUPTED_SIG 4
	#define NEW_SIG 5
	#define LOAD_SIG 6
	#define QUITSIGNAL 7			// The value that the variable ttime.year assumes if the user want to quit
	
	// The lenght of a name of an object, a system or a type
	#define NAMELUN 64
	
	// The size of a type's description. It must is bigger than NAMELUN
	#define DESCRIPTIONSIZE 512
	
	//the size of a buffer of character
	#define BUFFERSIZE 1024
	
	//max lenght of the buffer used by SafeScan function
	#define BUFFERINPUTSIZE 32
	
	// the max lenght of a command word
	#define COMMANDLENGHT 12
	
	// When you alloc the object buffer, this is how many object you delete or create when you resize
	#define OBJBUFSIZE 4
	
	// The frame that Rmotor uses and his size
	#define FRAME "# "
	#define FRAMER " #"		// FRAME R(ight)
	#define FRAMELUN 2		// FRAME LENGHT
	#define TWOFRAMELUN 4	// 2 * FRAME LENGHT
	#define FRAMESTART "#"
	#define FRAMEEND " "

	//constant used by the Impacts function (Pmotor)
	#define BIGGER_TOLERANCE 1.3
	#define COLOR_PREDOMINANCE 1.35
	
	//this are the code that refer to a template (AIB)(see template.which)
	#define TEMPLATE_IRREGULAR 0
	#define TEMPLATE_POINT 1
	#define TEMPLATE_CIRCLE 2
	
	// The acceleration of a monster (Km/s)
	#define MONSTER_ACCELERATION 0.00403

	// The vmode BYTE values
	#define V_OPS 0
	
	// The files
	#define DEBUG_FILE "debug.dbg"				// Where are printed debug information
	#define TYPE_DATABASE_FILE "type.typ"		// Where read type information
	#define CONFIGURATION_FILE "cspace.conf"	// Where read configuration information

	// BYTE is a value that occupies one byte max
	typedef 	int8_t		BYTE;	// max +/- 128
	typedef 	int16_t 	WORD;	// max +/- 32768
	typedef		int32_t		DWORD;
	typedef		int64_t		QWORD;
	
	// the array that contein a name of a type-system-object
	typedef char TNAME[NAMELUN];

	// the type that we use as color
	typedef struct scolor{
		int red;
		int green;
		int blue;
	} tcolor;
	
	// The structure that represent a type of a object
	typedef struct sStype {
		char *name;
		char description[DESCRIPTIONSIZE];
		TNAME parent;
		double mass_min;			// Mass range
		double mass_max;
		tcolor color_max;			// Color range
		tcolor color_min;
		BYTE hunted;				// if are hunted by space monster (ON/OFF)
		BYTE hunter;				// if hunts (ON/OFF)
		char *product;				// if an object is destroyed, this is what can remains from it (type name)
	} ttype;
	
	// The structure whit all the types
	typedef struct TypesStruct {
		WORD number;
		ttype *type;			// This is a pointer to the first member of the arrays that conteins all the types
	} tStype;

	// The structure infostruct is a structure that contein information about the options and other tecnical things 
	typedef struct info {
		int vmode;					// Visual mode
		int width;					// The number of columns that the program use
		int height;					// The number of lines that the program use
		int numprecision;			// Number of character used for printing the deciamal of a long double
		int debug;
	} tinf;

	// definition of the type of the object's structures
	// structure of one object
	typedef struct object {
		TNAME name;				// the name of the object (es.: Earth, My_Planet, Moon)
		ttype *type;			// the type of object.
		long double	radius;		// the object for now are sphere
		long double mass;		// the mass
		long double x;   		// the coordinate x
		long double y;			// the coordinate y
		long double z;			// the coordinate z
		long double velx;		// the fast of the movement in x
		long double vely;		// the fast of the movement in y
		long double velz;		// the fast of the movement in z
		tcolor color;			// the color
	} tobj;
	
	//in this structure is conteined a moment
	typedef struct strtime {
		QWORD year;
		int day;
		int hour;
		int min;
		int sec;
		int millisec;
	} ttime;
	
	// one system's structure: include the objects, the name and the number, the active object's position, the time of the system and the G constant of universal gravitation
	typedef struct system {
		TNAME name;
		long double precision;	// Precision of the simulation (in second)
		ttime stime;			// the time of the simulation
		QWORD nactive;			// number of objects active
		QWORD nalloc;			// number of objects allocated
		tobj *o;				// the pointer to the dinamic allocated array of objects
		long double G;
		tStype *Stype;			// The pointer at the structure that coontein all the type
	} tsys;
	
	// System functions
	void Setting(tinf *inf);
	int	LoadObject(tinf *, tobj *, tStype *, char *);
	long double Pitagora(long double, long double, long double);
	long double Pitagora2D(long double, long double);
	tobj *SearchObject(tsys *, char *);
	void ComputeBigger(tobj *o, tobj *u, tobj **b);
	int GetBiggerStime(ttime *, ttime *);
	void UpdateTime(ttime *);
	int Menu(tinf *, tStype *);
	ttype *TypeBrowser(tinf *, tStype *, char *);
	int Shell (tinf *, tStype *);
	void SafeIScan(tinf *, int *);
	void PrintLine (tinf *, char *, int);
	void ScanFString(char *, FILE *);	
	void SaveObject(tinf *, tobj *);
	void InitObject (tinf *, tobj *, tStype *, int);
	tsys *InitSystem (tinf *, tStype *);
	void ReduceObjBuf(tsys *, tinf *);
	tStype *Inittype (FILE *, tinf *);
	char *typeDescriptionFromName (tinf *inf, tStype *, char *);
	ttype *typeSearchName (tinf *, tStype *, char *);
	char *typeParentFromName (tinf *inf, tStype *, char *);
	long double RadiusestoVolume (long double, long double);
	// OPS and derivates
	void OPS(tinf *, char *, void **);
	void OPSE(tinf *, char *, void **);
	void OPSML(tinf *, char *);
	int OPSo (tsys *, tinf *);
	// Parser
	void Reask(tinf *, char *);
	void SaveSys(tsys *, tinf *);
	void Create(tsys *, tinf *);
	ttime Jump(ttime *, tinf *, long double *);
	ttime Wait(ttime *, tinf *, long double *);
	void DeleteObject(tinf *, tsys *);
	ttime Quit (tsys *, tinf *, ttime *);
	void DistanceCommand(tsys *, tinf *);
	void Info(tsys *, tinf *);
	// I/O object
	void WriteObject (FILE *stream, tobj *obj);
	void WriteObjectComplete (FILE *stream, tobj *obj);
	int ReadObject (tinf *inf, FILE *stream, tobj *obj, tStype *Stype);
	int ReadObjectComplete (tinf *inf, FILE *stream, tobj *obj, tStype *Stype);
	// Pmotor
	void Pmotor (tsys *, tinf *, ttime dest);
	void Gravity(tsys *, tinf *);
	void Inertia(tsys *, tinf *);
	void Impacts(tsys *, tinf *);
	void HunterIA(tsys *, tinf *);
	void HunterIA_single(tsys *, tinf *, tobj *);
	tobj MergeObject_Impact (tinf *, tobj *, tobj *);
	void Hunting_Impact(tinf *, tsys *, int, int);
	long double Distance(tobj *i, tobj *l);
	// color
	tcolor ScanColor(tinf *, tcolor, tcolor);
	int ColorRangeCheck(tcolor, tcolor, tcolor);
 
// CSpace's functions sorted by dependance
	#include "debug.c"
	#include "color.c"
	#include "system functions.c"
	#include "string functions.c"
	#include "type.c"
	#include "OnlyPrintfSystem.c"
	#include "OPSo.c"
	#include "menù.c"
	#include "pmotor.c"
	#include "Parser.c"
	#include "shell.c"
