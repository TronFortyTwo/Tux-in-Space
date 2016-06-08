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

	// The lenght of a name of an object, a system or a type
	#define NAMELUN 64
	
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
	#define FRAMER " #"		//FRAME R(ight)
	#define FRAMELUN 2
	#define TWOFRAMELUN 4
	#define FRAMESTART "#"
	#define FRAMEEND " "

