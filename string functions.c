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
 * Here we have function that help whit using the strings and whit input-output
 * 
 */

/***
 * This function scan a string WHIT space
 */
	void ScanString(char *dest) {
		
		char string[1024];
		char c;
		unsigned int pos;
		
		fflush(stdin);
		
		// as long as I read characters that aren't \n I read characters
		scanf(" %c", string);
		for(pos = 1;; pos++) {
			c = getchar();
			if(c == '\n')
				break;
			string[pos] = c;
		}
		string[pos] = 0;
		
		// move the string in the new location
		strcpy(dest, string);
		
		return;
	}

/***
 * This function scan a string WHIT space, to use when scanning a name, a type... but from a file
 * 
 * */
	void ScanFString(char *dest, FILE *stream) {
		fscanf(stream, "%999999[^\n]%*1[\n]", dest);
		return;
	}

/*** PrintLine is a function that printf a line of characters
 * 	can be setted a number num of characters that must not printed
 *	*/
	void PrintLine (tinf *inf, char *character, int num) {
		int p;	//(p)rinted
		for ( p=inf->width-num; p!=0; p--) {
			printf("%c", *character);
		}

		return;
	}

/***
 * SafeIScanf scan an int value more "safely" that the normal scanf() function
 * 
 * */
	void SafeIScan(tinf *inf, int *dest) {
		DebugPrint(inf, "safeiscan");
		
		//this buffer remember all the input
		char input[BUFFERINPUTSIZE];
		//this is the int value saved in buffer
		long long int number;
		//int values that are given to OPS
		void *var[3];
		//temp variable
		long long int temp;
	
		//scanf the string
		ScanString(input);
		
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
			OPSE (inf, "The number %s that you gave is too big or too small!\n\nPlease, type another number between %i and -%i", var);
			scanf("%s", input);
			number = strtoll(input, NULL, 0);
		}
		while (1);

		//assign the value
		*dest = number;

		return;
	}






