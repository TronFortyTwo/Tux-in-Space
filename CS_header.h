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
	
// Prototype of some function called from everywhere
	int GetBiggerStime(ttime *, ttime *);
	void ResProp(long double *,long double *,long double *,long double *, int x);
	void OPS(tinf *inf, char *, int *, long double *);
	void OPSE(tinf *inf, char *message, int *ivar, long double *lvar);
	void OPSML(tinf *inf);
	ttime Jump(ttime *now, tinf *inf, long double *precision);
	int Menu(tinf *inf);
	void PrintInt (tinf *, int, int *, int *);
	void PrintLongDouble (tinf *, long double *, int *, int *);
	void PrintString(tinf *, char *, int, int *, int *);
	int OPSo (tsys *sys, tinf *inf);
	ttime Parser(tStype *Stype, tsys *, tinf *, char);
	int Reask(tinf *, char *);
	void Create(tStype *Stype, tsys *, tinf *);
	ttype *TypeBrowser(tinf *, tStype *, char *);
	void Pmotor (tsys *);
	void Shell (tinf *, tStype *);
	void ChangeChar(char *, char, char);
	void SafeIScan(tinf *inf, int *dest);
	void PrintLine (tinf *inf, char character[], int);
	void ScanFString(char *dest, FILE *stream);	
	void SaveObject(tinf *, tobj *);
	void InitObject (tinf *, tobj *, tStype *, int);
	tsys *InitSystem (tinf *, tStype *);
	void ResizeObject(tStype *, tinf *, tobj **, int, int);
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

