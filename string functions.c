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
		
/*** GetLine is a function that write a line of characters
 * 		can be setted a number num of character that don't be returned
 * 		similar(in the behavior but not in the structure) to PrintLine but this write a char and doesn't print
 * 
 *	*/
	void GetLine (tinf *inf, char character[1], short num, int cpos);
	
	void GetLine (tinf *inf, char character[1], short num, int cpos) {
		
		short p;	// p for polpetta
		
		for (p=0; p!=inf->column-num+1; p++) {
			if (p == LENGHTCVAR) {
				return;
			}
			inf->cvar[p][cpos] = character[0];
		}
		
		return;
		}


/*** Write on an Array of Chars	(Was)
 * 		this function write a string given in another string starting from a position
 * 
 * 		return the number of characters copyed, else -1
 *	*/
	short Was (char *string, char toadd[], int pos);

	short Was (char *string, char toadd[], int pos) {
		// loop's counter
		int i;
		// main loop
		for (i=0; toadd[i]!='\0'; i++) {
			// control that the string has space for another character
			if(string[i+pos] == '\0')
				return -1;
			// copy the character
			string[i+pos] = toadd[i];
		}
		return i;
	}
