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
#    Foundation, Inc.																	#
#############################################################################################

 *
 * HERE we have function that help whit using the strings and whit input-output
 * 
 */


/*** PrintLine is a function that printf a line of characters
 * 		can be setted a number num of character that don't be printed
 *	*/
	void PrintLine (tinf *inf, char character[], int num);
	
	void PrintLine (tinf *inf, char character[], int num) {
		
		short p;	//(p)rinted

		for ( p=0; p!=inf->column-num; p++) {
			printf("%s", character);
			}

		return;
	}
		
/*** GetLine is a function that return a line of characters
 * 		can be setted a number num of character that don't be returned
 * 		similar(in the behavior but not in the structure) to PrintLine but this return the string and doesn't print it
 * 	NOTE:
 * 	this function don't end the string whit '\0'
 * 
 *	*/
	char * GetLine (tinf *inf, char character[1], short num);
	
	char * GetLine (tinf *inf, char character[1], short num) {
		
		short p;	// p for polpetta
		
		char *string = (char *) malloc (sizeof(char)*inf->column);
		
		for (p=0; p!=inf->column-num+1; p++) {
			string[p] = character[0];
		}
		
		free(string);
		
		return string;
	}


