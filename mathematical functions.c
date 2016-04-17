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
 * HERE we have functions that help whit mathematical problems 
 * 
 * 
 */

/*** GetSize is a function that get the size of an int.
 * 		for example the number one-hundred and fourty-seven has size 3.
 * 		because:
 * 			1	4	7
 * 			one	|	|
 * 				two	|
 * 					three
 * 	NOTE:
 * 	- Is a recursive function
 * 	- the int add is needed for the recursion
 *	*/
	int GetSize (int num, int add);	
	
	int GetSize (int num, int add) {
		// intialization
		int size = add;
		// default case
		if (num < 10)
			size ++;
		// else restart whit a semplification of the things
		else {
			size ++;
			num = num/10;
			size = GetSize (num, size);
			}
		// if the number is negative remember that must be printed the '-'
		if (num < 0) {
			num = -num;
			size++ ;
			}
		return size;
	}
