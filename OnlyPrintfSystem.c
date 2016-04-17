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

 * The function OnlyPrintfSystem: print word in a simple behavior and adapts on the value of column and line
 * 
 * The advantages on use OnlyPrintfSystem is:
 * 		- A simply but nice automatic impagination that all function could use whit a simple call 
 * 		- make the program nice and smart
 * 		- A very more simple algoritm (faster and lighter) respect more graphically mode of Rmotor not writted yet, but equally can adapts the column and line numbers
 *
 */
 
	//prototype for the OPS's functions
	int OnlyPrintfSystem(tinf *inf, char *phrase, int *ivar, long double *lvar, char *cvar);
	void PrintInt (tinf *inf, int n, short *columndone, short *linedone);
	void PrintLongDouble (tinf *inf, long double *n, short *columndone, short *linedone);
	
 
	int OnlyPrintfSystem(tinf *inf, char *phrase, int *ivar, long double *lvar, char *cvar) {
	
	// the number of lines alredy printfed
	short linedone = 0;
	// the number of character in a line alredy printfed
	short columndone = 0;
	// the number of character of phrase printed
	short chardone = 0;
	// the position in the arrays
	short ipos=0;
	short lpos=0;
	
	// make some space
	printf("\n\n\n\n\n\n\n\n");
	
	// printf the first character of the frame like first line
	PrintLine(inf, FRAMESTART, 0);
	printf("\n");
	
	// printf the second line continuing whit the frame
	printf(FRAME);
	PrintLine(inf, FRAMEEND, 4);
	printf("%s\n", FRAMER);
	
	//a loop that printf every line
	for( linedone=2; linedone!=inf->line-3; linedone++) {
		
		//printf the frame
		printf(FRAME);
		
		//a loop that fill the line
		for (columndone=FRAMELUN; columndone < inf->column-FRAMELUN; ) {
			
			// If the character is a new line
			if(phrase[chardone]=='\n') {
				// printf spaces to complete the line
				PrintLine(inf, " ", columndone + FRAMELUN);
				// update the counter
				chardone++;
				// exit the loop because the line has been printed
				break;
			}
			
			// if the character is a space on the start of the line don't printf it
			else if ((phrase[chardone] == ' ') && (columndone == FRAMELUN) ) {
				// update positon on phrase[] but don't printf it
				chardone++;
				continue;
			}
			
			// if the character is a % start var printing
			else if (phrase[chardone] == '%') {
				chardone++;
				// if is an int call PrintInt
				if (phrase[chardone] == 'i') {
					PrintInt(inf, ivar[ipos], &columndone, &linedone);
					ipos++;
					chardone++;
				}
				else if (phrase[chardone] == 'l') {
					PrintLongDouble(inf, &lvar[lpos], &columndone, &linedone);
					lpos++;
					chardone++;
					}
				
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
			
			// else the character is the '\0', so print blank line
			else {
				// write it, update counter variables and go to the next character
				PrintLine(inf, " ", FRAMELUN+columndone);
				break;
			}
		}
		
		//printf the frame and new line
		printf("%s\n", FRAMER);
		
	}
	
	// printf the last two line of the frame
	printf(FRAME);
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
		
		//if the number is too big for the line
		if(*columndone+2*FRAMELUN+size >= inf->column){
			//if there isn't another clear line
			if(*linedone+3 == inf->line){
				//complete the line
				PrintLine(inf, " ", 2*FRAMELUN+*columndone);
				printf("%s\n", FRAMER);
				//update teh counters
				*columndone=inf->column;
				//exit the function
				return;
			}
			//complete the line and update counter
			PrintLine(inf, " ", 2*FRAMELUN+*columndone);
			printf("%s\n%s", FRAMER, FRAME);
			*columndone = FRAMELUN;
			*linedone = *linedone+1;
			//printf the int
			printf("%i", n);
			//update the counter
			*columndone=*columndone+size;
		}
		//if the number isn't to big for the line
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
 * 
 */
	void PrintLongDouble (tinf *inf, long double *n, short *columndone, short *linedone) {
		
		// if a long double occupies more than a line (whit the frame), it will not be printfed
		char *buffer = (char *) malloc ((inf->column-2*FRAMELUN)*sizeof(char));
		// the size of the number
		short size;
		// caluculate size
		size = snprintf(buffer, inf->column-2*FRAMELUN, "%Lf", *n);
		// if the number don't overflow the line
		if(*columndone+2*FRAMELUN+size <= inf->column) {
			//printf it
			printf("%s", buffer);
			//update the counters
			*columndone=*columndone+size;
			}
		// else, if the number is more big than the space remaining in the line
		else{
			//complete the line whit spaces
			PrintLine(inf, " ", 2*FRAMELUN);
			//do the frame and new line
			printf("%s\n%s", FRAME, FRAMER);
			//printf the number
			printf("%s", buffer);
			//update the counters
			*columndone=FRAMELUN+size;
			*linedone=*linedone+1;
		}
		return;
	}
