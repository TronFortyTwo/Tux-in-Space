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
 * HERE we have function that help whit using the strings and whit input-output
 * 
 */


/*** PrintLine is a function that printf a height of characters
 * 		can be setted a number num of character that don't be printed
 *	*/
	void PrintLine (tinf *inf, char character[], int num);
	
	void PrintLine (tinf *inf, char character[], int num) {
		
		short p;	//(p)rinted

		for ( p=0; p!=inf->width-num; p++) {
			printf("%s", character);
			}

		return;
	}

/***
 * SafeIScanf scan an int value more "safely" that the normal scanf() function
 * 
 * */

void SafeIScan(tinf *inf, int *dest);
void SafeIScan(tinf *inf, int *dest) {
	
	//this buffer remember all the input
	char buffer[BUFFERINPUTSIZE];
	//this is the int value saved in buffer
	long long int input;
	//int values that are given to Rmotor
	int ivar[2];
	
	//scanf the string
	scanf("%s", buffer);
	fflush(stdin);
		
	//call the function
	input = strtoll(buffer, NULL, 0);
	
	//set the max value of an int
	ivar[0]= (int) pow(2, 8*sizeof(int) -1);
	ivar[1]= -ivar[0];
		
	// reask the number until the number can fit the int number
	for( ; ; ) {
		if(input <= ivar[0])
			if(input >= ivar[1])
				break;
		Rmotor(0, inf, 0, "ATTENCTION:\nThe number %s that you gave us is too big or too small!\n\nPlease, type another number between %i and %i", ivar, 0, buffer);
		scanf("%s", buffer);
		fflush(stdin);
		input = strtoll(buffer, NULL, 0);
	}

	//assign the value
	*dest = input;

	return;
}






