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
	
// Prototype of some function called from everywhere
	void OPS(tinf *inf, char *, int *, long double *);
	void OPSE(tinf *inf, char *message, int *ivar, long double *lvar);
	void OPSML(tinf *inf);
	int Menu(tinf *inf);
	void PrintInt (tinf *, int, int *, int *);
	void PrintLongDouble (tinf *, long double *, int *, int *);
	void PrintString(tinf *, char *, int, int *, int *);
	int OPSo (tsys *sys, tinf *inf);
	void Parser(tsys *, tinf *, char);
	int Reask(tinf *, char *);
	void Create(tsys *, tinf *);
	void Pmotor (tsys *sys);
	void Shell (tsys *sys, tinf *inf);
	void ChangeChar(char *, char, char);
	void SafeIScan(tinf *inf, int *dest);
	void PrintLine (tinf *inf, char character[], int num);
	void ScanFString(char *dest, FILE *stream);	
	void SaveObject(tinf *, tobj *);
	void InitObject (tinf *, tobj *, tStype *, int);
	void InitSystem (tsys *, tinf *);
	void ResizeObject(tinf *, tobj **, int, int);
	void ResetObject(tobj *);	
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

