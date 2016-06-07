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

/***
 * This function scan a string WHIT space, to use when scanning a name, a type... but from a file
 * 
 * */
	void ScanFString(char *dest, FILE *stream){
	
		fscanf(stream, "%9999[^\n]%*1[\n]", dest);
	
		return;
	}





/***
 * 	The function ChangeChar take a string and in it remove all a char and change it whit an other
 * */
	void ChangeChar(char *string, char first, char later) {
		// counter for loops
		int i;
		
		// a loop
		for(i=0; string[i]!='\0'; i++) {
			if(string[i] == first)
				string[i] = later;
		}
		return;
	}




/*** PrintLine is a function that printf a height of characters
 * 		can be setted a number num of character that don't be printed
 *	*/
	void PrintLine (tinf *inf, char *character, int num) {
		
		int p;	//(p)rinted

		for ( p=0; p!=inf->width-num; p++) {
			printf("%c", *character);
			}

		return;
	}

/***
 * SafeIScanf scan an int value more "safely" that the normal scanf() function
 * 
 * */
void SafeIScan(tinf *inf, int *dest) {
	
	//this buffer remember all the input
	char input[BUFFERINPUTSIZE];
	char buffer[BUFFERSIZE];
	//this is the int value saved in buffer
	long long int number;
	//int values that are given to Rmotor
	int ivar[2];
	
	//scanf the string
	scanf("%s", input);
	fflush(stdin);
		
	//call the function
	number = strtoll(input, NULL, 0);
	
	//set the max value of an int
	ivar[0]= (int) pow(2, 8*sizeof(int) -1);
	ivar[1]= -ivar[0];
		
	// reask the number until the number can fit the int number
	for( ; ; ) {
		if(number <= ivar[0])
			if(number >= ivar[1])
				break;
		strcpy(buffer, "The number ");
		strcat(buffer, input);
		strcat(buffer, " that you gave is too big or too small!\n\nPlease, type another number between %i and %i");
		OPSE(inf, buffer, ivar, 0);
		scanf("%s", input);
		fflush(stdin);
		number = strtoll(input, NULL, 0);
	}

	//assign the value
	*dest = number;

	return;
}






