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
/**
 * In this file there are all the constant (#define)
 * 
 */


	// Max number of object that the program can work on
	#define NUMOGG 2048
	
	// The lenght of a name of an object or a system
	#define NAMELUN 64
	
	// The number of character printed when printing a LONG DOUBLE (possible 3 to 12)
	#define LDLUN 8
	
	// The max lenght of a variable cvar (see NUMCVAR)
	#define LENGHTCVAR 16

	// The frame that Rmotor uses and his size
	#define FRAME "# "
	#define FRAMER " #"		//FRAME R(ight)
	#define FRAMELUN 2
	#define FRAMESTART "#"
	#define FRAMEEND " "

	// this are numbers needed from the variable database that use it for make a variable proprety of a function.
	// No one function use the number directly, but use the name, so what number chose is indifferent
	// all the number must be different
	#define NUMFUNCTIONS 2
	#define VOnlyPrintfSystem 1
	#define VOPSo 2
	//...
	//if a function use the Database manager just add it here whit a new number(and a V first) and add one at the NUMFUNCTION
