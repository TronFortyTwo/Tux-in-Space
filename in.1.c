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
 * 
 * Here we have function that help whit input
 * 
 */

#include "generic.h"
#include "OnlyPrintfSystem.h"
#include "in.h"
#include "debug.h"

/***
 * This function scan a string WHIT spaces
 * NOT. this feature will came, maybe
 * 
 */
void in_s (char *d) {
	
	if(set.vmode == V_OPS) {
		scanf("%s", d);
	}
	
	if(set.vmode == V_SDL) {
		// Here should be something corrispondent to scanf but whit SDL
	}
}

/***
 * This function scan a string WHIT space, to use when scanning a name, a type... but from a file
 * 
 * */
void in_fs (char *dest, FILE *stream) {
	#if DEBUG
	debug_Printf("in_fs:");
	#endif
	
	fscanf(stream, "%9999[^\n]%*1[\n]", dest);
	
	#if DEBUG
	debug_Printf(dest);
	#endif
}


/***
 * SafeIScanf scan an int value more "safely" that the normal scanf() function
 * 
 * */
void in_i (int *dest) {
		
	//this buffer remember all the input
	char input[64];
	//this is the int value saved in buffer
	long long int number;
	//int values that are given to OPS
	void *var[3];
	//temp variable
	long long int temp;
	
	//scanf the string
	in_s(input);
		
	//call the function
	number = strtoll(input, NULL, 0);
		
	// reask the number until the number can fit the int number
	while(1) {
		if (number <=  INT_MAX)
			if (number >= INT_MIN)
				break;
		temp = INT_MAX;
		var[0] = input;
		var[1] = &temp;
		var[2] = &temp;
		OPS_Error ("The number %s that you gave is too big or too small!\n\nPlease, type another number between %i and -%i", var);
		scanf("%s", input);
		number = strtoll(input, NULL, 0);
	}

	//assign the value
	*dest = number;

	return;
}


/***
 * SafeUScanf scan an unsigned int value more "safely" that the normal scanf() function
 * 
 * */
void in_u (unsigned int *dest) {
		
	//this buffer remember all the input
	char input[64];
	//this is the int value saved in buffer
	long long int number;
	//int values that are given to OPS
	void *var[3];
	//temp variable
	unsigned long long int temp;
	
	//scanf the string
	in_s(input);
		
	//call the function
	number = strtoll(input, NULL, 0);
		
	// reask the number until the number can fit the int number
	do {
		if (number <=  INT_MAX)
			if (number >= INT_MIN)
				break;
		temp = INT_MAX;
		var[0] = input;
		var[1] = &temp;
		var[2] = &temp;
		OPS_Error ("The number %s that you gave is too big or too small!\n\nPlease, type another number between %i and -%i", var);
		scanf("%s", input);
		number = strtoll(input, NULL, 0);
	}
	while (1);

	//assign the value
	*dest = number;

	return;
}
