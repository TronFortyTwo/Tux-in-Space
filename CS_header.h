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
 * Contein even the definition of constants
 */

// External standard library
	#include <stdint.h>
	#include <inttypes.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <math.h>
	#include <time.h>
	
// Prototypes
	ttime Quit (tsys *, tinf *, ttime *);
	tobj *SearchObject(tsys *sys, char *name);
	tobj CreateObject (tStype *, char *, ttype *, long double, long double, long double, long double, long double, long double, long double, long double);
	void Info(tsys *sys, tinf *inf);
	int GetBiggerStime(ttime *, ttime *);
	void UpdateTime(ttime *stime);
	void OPS(tinf *, char *, int *, long double *);
	void OPSE(tinf *, char *, int *, long double *);
	void OPSML(tinf *, char *);
	ttime Jump(ttime *, tinf *, long double *);
	ttime Wait(ttime *, tinf *, long double *);
	int Menu(tinf *);
	int OPSo (tsys *, tinf *);
	ttime Parser(tsys *, tinf *);
	void Reask(tinf *, char *);
	void SaveSys(tsys *sys, tinf *inf);
	void Create(tsys *, tinf *);
	ttype *TypeBrowser(tinf *, tStype *, char *);
	void Pmotor (tsys *, tinf *inf);
	int Shell (tinf *, tStype *);
	void SafeIScan(tinf *inf, int *dest);
	void PrintLine (tinf *inf, char character[], int);
	void ScanFString(char *dest, FILE *stream);	
	void SaveObject(tinf *, tobj *);
	void InitObject (tinf *, tobj *, tStype *, int);
	tsys *InitSystem (tinf *, tStype *);
	void ReduceObjBuf(tsys *sys, tinf *inf);
	void ResetObject(tStype *, tobj *);	
	tStype *Inittype (FILE *, tinf *);
	char *typeDescriptionFromName (tStype *, char *);
	ttype *typeSearchName (tStype *, char *);
	char *typeParentFromName (tStype *, char *);
 
	
// CSpace's functions sorted by dependance (so DON'T MODIFY the order if you don't want to fight dozen of gcc's error)
	#include "string functions.c"
	#include "type.c"
	#include "system functions.c"
	#include "OnlyPrintfSystem.c"
	#include "OPSo.c"
	#include "menù.c"
	#include "pmotor.c"
	#include "Parser.c"
	#include "shell.c"

