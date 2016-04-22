/*
#############################################################################
#    CSpace - space simulator												#
#    Copyright (C) 2016  emanuele.sorce@hotmail.com							#
#																			#
#    This program is free software; you can redistribute it and/or modify	#
#    it under the terms of the GNU General Public License as published by	#
#    the Free Software Foundation, version 3 or compatibles.				#
#																			#
#    This program is distributed in the hope that it will be useful,		#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of			#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the			#
#    GNU General Public License for more details.							#
#																			#
#    You should have received a copy of the GNU General Public License		#
#    along with this program; if not, write to the Free Software			#
#    Foundation, Inc.														#
#############################################################################

 * The function OnlyPrintfSystem: print word in a simple behavior and adapts on the value of width and height
 * 
 * The advantages on use OnlyPrintfSystem is:
 * 		- A simply but nice automatic impagination that all function could use whit a simple call 
 * 		- make the program nice and smart
 * 		- A very more simple algoritm (faster and lighter) respect more complex mode of Rmotor not writted yet, but equally can adapts the width and height numbers
 *
 */
 
	//prototype for the OPS's functions
	int OnlyPrintfSystem(tinf *inf, char *phrase, int *ivar, long double *lvar, char *cvar);
	void PrintInt (tinf *inf, int n, short *columndone, short *linedone);
	void PrintLongDouble (tinf *inf, long double *n, short *columndone, short *linedone);
	void PrintString(tinf *inf, char *buffer, short numstring, short *columndone, short *linedone);
	
 /**Only Printf System */
	int OnlyPrintfSystem(tinf *inf, char *phrase, int *ivar, long double *lvar, char *cvar) {
	
	// the number of lines alredy printfed
	short linedone = 0;
	// the number of character in a height alredy printfed
	short columndone = 0;
	// the number of character of phrase printed
	short chardone = 0;
	// the position in the arrays
	short ipos=0;
	short lpos=0;
	short cpos=0;
	
	// make some space
	printf("\n\n\n\n\n\n\n\n");
	
	// printf the first character of the frame like first height
	PrintLine(inf, FRAMESTART, 0);
	printf("\n");
	
	// printf the second height continuing whit the frame
	printf(FRAME);
	PrintLine(inf, FRAMEEND, 4);
	printf("%s\n", FRAMER);
	
	//a loop that printf every height
	for( linedone=2; linedone!=inf->height-3; linedone++) {
		
		//printf the frame
		printf("%s", FRAME);
		
		//a loop that fill the height
		for (columndone=FRAMELUN; columndone < inf->width-FRAMELUN; ) {
			
			// If the character is a new height
			if(phrase[chardone]=='\n') {
				// printf spaces to complete the height
				PrintLine(inf, " ", columndone + FRAMELUN);
				// update the counter
				chardone++;
				// exit the loop because the height has been printed
				break;
			}
			
			// if the character is a space on the start of the height don't printf it
			else if ((phrase[chardone] == ' ') && (columndone == FRAMELUN) ) {
				// update positon on phrase[] but don't printf it
				chardone++;
				continue;
			}
			
			// if the character is a % start dinamic printing
			else if (phrase[chardone] == '%') {
				chardone++;
				// if is an i call PrintInt
				if (phrase[chardone] == 'i') {
					PrintInt(inf, ivar[ipos], &columndone, &linedone);
					ipos++;
				}
				// if is an l call PrintLongDouble
				else if (phrase[chardone] == 'l') {
					PrintLongDouble(inf, &lvar[lpos], &columndone, &linedone);
					lpos++;
				}
				// if is a c call PrintString
				else if (phrase[chardone] == 'c') {
					PrintString(inf, cvar, cpos, &columndone, &linedone);
					cpos++;
				}
				// if is a L finish the height whit phrase[chardone+1]
				else if (phrase[chardone] == 'f') {
					PrintLine(inf, &phrase[chardone+1], 2*FRAMELUN+columndone);
					chardone++;
					columndone = inf->width-FRAMELUN;
				}
				chardone++;
				continue;
			}
			
			// else if the character is not the end string character (a normal character) print it
			else if (phrase [chardone] != '\0') {
				// write it, update counter variables and go to the next character
				printf("%c", phrase[chardone]);
				chardone++;
				columndone++;
				continue;
			}
			
			// else the character is the '\0', so print blank height
			else {
				// write it, update counter variables and go to the next character
				PrintLine(inf, " ", FRAMELUN+columndone);
				break;
			}
		}
		
		//printf the frame and new height
		printf("%s\n", FRAMER);
		
	}
	
	// printf the last two height of the frame
	printf("%s", FRAME);
	PrintLine(inf, FRAMEEND, 4);
	printf("%s\n", FRAMER);
	PrintLine(inf, FRAMESTART, 0);
	printf("\n");
	
	// ask user for input
	printf("%s:", FRAME);
	
	// return 0
	return 0;
	}








/***
 * 	The function PrintInt print an int whit the OPS's style
 * 	n is the number
 * 	columndone is the pointer to columndone
 * 	linedone is the pointer to linedone
 * 	inf is the pointer to inf
 * 	return the new value of columndone or -1 if error
 * 
 */

	void PrintInt (tinf *inf, int n, short *columndone, short *linedone) {
		
		// the size in character of the number
		short size;
		
		//take size
		size = GetSize(n, 0);
		
		//if the number is too big for the height
		if(*columndone+2*FRAMELUN+size >= inf->width){
			//if there isn't another clear height
			if(*linedone+3 == inf->height){
				//complete the height
				PrintLine(inf, " ", 2*FRAMELUN+*columndone);
				printf("%s\n", FRAMER);
				//update teh counters
				*columndone=inf->width;
				//exit the function
				return;
			}
			//complete the height and update counter
			PrintLine(inf, " ", 2*FRAMELUN+*columndone);
			printf("%s\n%s", FRAMER, FRAME);
			*columndone = FRAMELUN;
			*linedone = *linedone+1;
			//printf the int
			printf("%i", n);
			//update the counter
			*columndone=*columndone+size;
		}
		//if the number isn't to big for the height
		else {
			//printf the number
			printf("%i", n);
			//update columndone
			*columndone=*columndone+size;
		}
		
		return;
	}

/***
 * The function PrintLongDouble printf a long double whit the OPS's nice style
 * 
 */
	void PrintLongDouble (tinf *inf, long double *n, short *columndone, short *linedone) {
		
		// if a long double occupies more than a height (whit the frame), it will not be printfed
		char *buffer = (char *) malloc ((inf->width-2*FRAMELUN)*sizeof(char));
		// the size of the number
		short size;
		// caluculate size
		size = snprintf(buffer, inf->width-2*FRAMELUN, "%+'.*Lf",inf->numprecision, *n);
		// if the number don't overflow the height
		if(*columndone+2*FRAMELUN+size <= inf->width) {
			//printf it
			printf("%s", buffer);
			//update the counters
			*columndone=*columndone+size;
			}
		// else, if the number is more big than the space remaining in the height
		else{
			//if there isn't any new height to print
			if(*linedone+3 == inf->height){
				//complete the height
				PrintLine(inf, " ", 2*FRAMELUN+*columndone);
				printf("%s\n", FRAMER);
				//update teh counters
				*columndone=inf->width;
				//exit the function
				return;
			}
			//complete the height whit spaces
			PrintLine(inf, " ", *columndone+2*FRAMELUN);
			//do the frame and new height
			printf("%s\n%s", FRAME, FRAMER);
			//printf the number
			printf("%s", buffer);
			//update the counters
			*columndone=FRAMELUN+size;
			*linedone=*linedone+1;
		}
		return;
	}

/***
 * The function PrintString printf a string from a buffer of char. 
 * For easily transport of the buffer in the functions, in a buffer there is many strings, shared whit '\0'.
 * This is the reason of why must be given a number that represent what string must be printed
 */
	void PrintString(tinf *inf, char *buffer, short numstring, short *columndone, short *linedone) {
		
		//contein the position of the first character of the string to printf
		short position;
		
		//counter
		short i;
		
		//look for the first character of the string to print
		for (position=0, i=0; i != numstring; position++) {
			if(buffer[position]=='\0')
				i++;
		}
	
		//take the size of the string
		i = strlen(&buffer[position]);
	
		//now printf the string if not overflow the height
		if(*columndone+2*FRAMELUN+i <= inf->width) {
			printf("%s", &buffer[position]);
			*columndone = *columndone+i;
		}
		//else, if there is another height, printf the string in a new height
		else {
			if(*linedone+3 == inf->height){
				//complete the height
				PrintLine(inf, " ", FRAMELUN+*columndone);
				printf("%s\n", FRAMER);
				//update teh counters
				*columndone=inf->width;
				//exit the function
				return;
			}
			PrintLine(inf, " ", 2*FRAMELUN+*columndone);
			printf("%s\n%s%s", FRAMER, FRAME, &buffer[position]);
			*columndone = FRAMELUN+i;
			*linedone=*linedone+1;
		}
		
		return;
	}



