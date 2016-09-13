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
	// Other libraries for linux
	#include <sys/stat.h>
	// SDL library
	#include <SDL2/SDL.h>

	// Pi
	#define PI M_PI
	
	// values
	// NOTE:
	// Is important the YES = ON and OFF = NO
	#define ON 1
	#define OFF 0
	#define NO OFF
	#define YES ON
		
	// Window size
	#define SCREEN_WIDTH 256
	#define SCREEN_HEIGHT 256
		
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
	
	// the size of a buffer of character
	#define BUFFERSIZE 1024
	
	// max lenght of the buffer used by SafeScan function
	#define BUFFERINPUTSIZE 32
	
	// the max lenght of a command word
	#define COMMANDLENGHT 12
	
	// When you alloc the object buffer, this is how many object you delete or create when you resize
	#define OBJBUFSIZE 4
	
	// The frame that Rengine uses and his size
	#define FRAME "# "
	#define FRAMER " #"		// FRAME R(ight)
	#define FRAMELUN 2		// FRAME LENGHT
	#define TWOFRAMELUN 4	// 2 * FRAME LENGHT
	#define FRAMESTART "#"
	#define FRAMEEND " "

	// constant used by the Impacts function (Pmotor)
	#define BIGGER_TOLERANCE 1.3
	#define COLOR_PREDOMINANCE 1.35
	
	// this are the code that refer to a template (AIB)(see template.which)
	#define TEMPLATE_IRREGULAR 0
	#define TEMPLATE_POINT 1
	#define TEMPLATE_CIRCLE 2
	
	// The acceleration of a hunter (Km/s)
	#define HUNTER_ACCELERATION 0.002

	// The video mode
	#define V_OPS 0
	#define V_SDL 1
	
	// The files
	#define DEBUG_FILE "debug.dbg"				// Where are printed debug information
	#define DEBUG_FILE_LENGHT 10				// The size of DEBUG_FILE
	#define TYPE_DATABASE_FILE "type.typ"		// Where read type information
	#define CONFIGURATION_FILE "cspace.conf"	// Where read configuration information
	#define OBJECT_PATH "Objects/"				// Where save/load systems
	#define SYSTEM_PATH "Systems/"				// Where save/load objects
	
	// Default values for the inf structure
	#define DEFAULT_OPS_HEIGHT 			42
	#define DEFAULT_OPS_WIDTH 			88
	#define DEFAULT_DEBUG 				OFF
	#define DEFAULT_OPS_NUMPRECISION 	6
	#define DEFAULT_V_MODE 				V_OPS
	
	// A two-in-one function call whitout argurment (safe getchar)
	#define sgetchar() (scanf(" "), getchar())
	
	// BYTE is a value that occupies one byte max
	typedef 	int8_t		BYTE;	// max +/- 128
	typedef 	int16_t 	WORD;	// max +/- 32768
	typedef		int32_t		DWORD;
	typedef		int64_t		QWORD;
	
	// the array that contein a name of a type/system/object
	typedef char TNAME[NAMELUN];

	// the type that we use as color
	typedef struct scolor{
		unsigned int red;
		unsigned int green;
		unsigned int blue;
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

	/*
	 * The structure info is a structure that contein information about the options and other tecnical things 
	 */
	typedef struct infoOps {
		unsigned int width;				// The number of columns that the program use
		unsigned int height;			// The number of lines that the program use
		unsigned int numprecision;		// Number of character used for printing the deciamal of a long double
	} tinfops;
	
	typedef struct infoGl {
		SDL_Window *win;			// the window
		SDL_Surface *sur;
		BYTE winopen;				// YES if the window is opened, NO if NOT
	} tinfgl;
	
	typedef struct info {
		int vmode;		// Visual mode
		int debug;		// could be ON or OFF
		tinfops ops;	// OPS settings
		tinfgl gl;		// Window and OpenGL settings
	} tinf;

	// definition of the type of the object's structures
	// structure of one object
	typedef struct object {
		char *name;				// the name of the object (es.: Earth, My_Planet, Moon)
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
		void *data;				// type specific information about the object
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
	
	
	//
	// THE INF STRUCTURE, THE ONLY GLOBAL VARIABLE
	//
	tinf inf;

	
	// System functions
	BYTE InitDir();
	void InitConfig();
	void SetDefaultConfig();
	void SaveConfig();
	void Setting();
	int	LoadObject(tobj *, tStype *, char *);
	long double Pitagora(long double, long double, long double);
	long double Pitagora2D(long double, long double);
	tobj *SearchObject(tsys *, char *);
	void ComputeBigger(tobj *, tobj *, tobj **);
	int GetBiggerStime(ttime *, ttime *);
	void UpdateTime(ttime *);
	int Menu(tStype *);
	ttype *TypeBrowser(tStype *, char *);
	int Shell (tStype *);
	void SafeIScan(int *);
	void SafeUScan (unsigned int *);
	void PrintLine (char *, int);
	void ScanFString(char *, FILE *);
	void SaveObject(tobj *);
	void InitObject (tobj *, tStype *);
	tsys *InitSystem (tStype *);
	tsys *InitSystemOPS (tStype *);
	tsys *InitSystemGl (tStype *);
	tsys *LoadSystemOPS (tStype *);
	tsys *LoadSystemGl (tStype *);
	void ReduceObjBuf(tsys *);
	void ExtendObjBuf(tsys *);
	tStype *Inittype (FILE *);
	char *typeDescriptionFromName (tStype *, char *);
	ttype *typeSearchName (tStype *, char *);
	char *typeParentFromName (tStype *, char *);
	long double RadiusestoVolume (long double, long double);
	void ScanString(char *);
	void AutoRemoveObject(tsys *, int);
	void CleanObject(tobj *);
	int RandomInt (int, int);
	// OPS and derivates
	void OPS(char *, void *[]);
	void OPSE(char *, void *[]);
	void OPSML(char *);
	int OPSo (tsys *);
	// Parser
	ttime Parser(tsys *);
	void Reask(char *);
	void SaveSys(tsys *);
	void Create(tsys *);
	ttime Jump(ttime *, long double *);
	ttime Wait(ttime *, long double *);
	void DeleteObject(tsys *);
	ttime Quit (tsys *, ttime *);
	void DistanceCommand(tsys *);
	void Info(tsys *);
	// I/O object
	void WriteObject (FILE *, tobj *);
	void WriteObjectComplete (FILE *, tobj *);
	int ReadObject (FILE *, tobj *, tStype *);
	int ReadObjectComplete (FILE *, tobj *, tStype *);
	// Pmotor
	void Pmotor (tsys *, ttime dest);
	void Gravity(tsys *);
	void Inertia(tsys *);
	void Impacts(tsys *);
	void HunterIA(tsys *);
	void HunterIA_single(tsys *, tobj *);
	tobj MergeObject_Impact (tobj *, tobj *);
	void Hunting_Impact(tStype *, tobj *, tobj *);
	void ElasticImpact(tobj *, tobj *);
	long double Distance(tobj *i, tobj *l);
	// color
	tcolor ScanColor(tcolor, tcolor);
	int ColorRangeCheck(tcolor, tcolor, tcolor);
	// debug
	void PrintStype(tStype *);
	void DebugPrint(char *);
	void InitDebug();
	void DebugObject(tobj *);
	void DebugInt(int);
	// SDL
	BYTE InitGL();
	int GlMenu(tStype *);
	tsys *LoadSystem(tStype *);
	void SGLGUI (tsys *);
	ttime GLparser (tsys *);
