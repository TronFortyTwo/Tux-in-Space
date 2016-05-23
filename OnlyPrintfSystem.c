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

 * The function OnlyPrintfSystem: print words in a simple behavior that adapts on the value of width and height
 * 
 * The advantages on use OnlyPrintfSystem is:
 * 		- A simply but nice automatic impagination that all function could use whit a simple call 
 * 		- make the program nice
 * 		- A very more simple algoritm (faster and lighter) respect more complex mode of Rmotor not writted yet, but equally can adapts the width and height numbers
 *
 * 	NOTE:
 * 	OnlyPrintfSystem is often called OPS
 * 
 */

 /**Only Printf System */
	void OPS(tinf *inf, char *phrase, int *ivar, long double *lvar) {
	
	//loop counter
	int i;
	// the number of lines alredy printfed
	int linedone;
	// the number of character in a line alredy printfed
	int columndone;
	// the number of character of phrase printed
	int chardone;
	// the position in the arrays
	int ipos=0;
	int lpos=0;
	// the buffer to print, his size and position
	int size = (inf->width-TWOFRAMELUN) * (inf->height-5) +1;
	char *buf = (char *) malloc (sizeof(char)*size);
	int bufpos = 0;
	
	//signal if there is a memory leack
	while (buf == NULL) {
		OPSML(inf);
		buf = (char *) malloc (sizeof(char)*((inf->width-TWOFRAMELUN)*(inf->height-5)+1));
	};
	
	//OPS PART ONE: writing the buffer. Elaborate the input and write it in buf
	for(chardone=0; bufpos!=size-1;) {
		
		//dinamic printing!
		if(phrase[chardone] == '%') {
			chardone++;
			//an int value to print
			if(phrase[chardone] == 'i') {
				bufpos = bufpos + sprintf(&buf[bufpos], "%d", ivar[ipos]);
				ipos++;
				chardone++;
			}
			//a long double value to print
			else if(phrase[chardone] == 'l') {
				bufpos = bufpos + sprintf(&buf[bufpos], "%Lf", lvar[lpos]);
				lpos++;
				chardone++;
			}
			//a line to print
			else if(phrase[chardone] == 'f') {
				chardone++;
				for(i=0; i!=inf->width; i++) {
					strncat(&buf[bufpos], &phrase[chardone], 1);
					bufpos++;
				}
				chardone++;
			}
		}
		// a normal character
		else if(phrase[chardone] != '\0') {
			buf[bufpos] = phrase[chardone];
			chardone++;
			bufpos++;
		}
		//end of string
		else {
			buf[bufpos] = ' ';
			bufpos++;
		}
	}
	
	//OPS PART TWO: print the buf
	bufpos=0;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	//the first two line of the frame
	PrintLine(inf, FRAMESTART, 0);
	printf("\n%s", FRAME);
	PrintLine(inf, FRAMEEND, TWOFRAMELUN);
	printf("%s\n", FRAMER);
	//printf the buf
	for(linedone=0; linedone!=inf->height-5; linedone++) {
		//the frame
		printf("%s", FRAME);
		for(columndone=0; columndone!=inf->width-TWOFRAMELUN; columndone++) {
			if (buf[bufpos] != '\n') {
				printf("%c", buf[bufpos]);
				bufpos++;
			}
			else {
				PrintLine(inf, " ", columndone+TWOFRAMELUN);
				bufpos++;
				if(linedone < inf->height-5) {
					linedone++;
					printf("%s\n%s", FRAMER, FRAME);
					columndone = -1;
				}
			}
		}
		//the frame
		printf("%s\n", FRAMER);
	}
	//last lines
	printf("%s", FRAME);
	PrintLine(inf, FRAMEEND, TWOFRAMELUN);
	printf("%s\n", FRAMER);
	PrintLine(inf, FRAMESTART, 0);
	printf("\n%s:", FRAME);
	
	// finish the function
	free(buf);
	return;
	}
	
/***
 * OPSE (OnlyPrintfSystemError) printf an error message whit the OPS
 */
	void OPSE(tinf *inf, char *message, int *ivar, long double *lvar){
		//size of message
		int size;
		size = strlen(message);
		//the message to print
		char *buffer = (char *) malloc ((32+size)*sizeof(char));
		//a nice bip
		printf("\a");
		//set the buffer
		strcpy(buffer, "ERROR!\n\n");
		strcat(buffer, message);
		strcat(buffer, "\n\nwaiting...");
		//printf the buffer
		OPS(inf, buffer, ivar, lvar);
		//exit the function
		free(buffer);
		return;
	}

/***
 * OPSML (OnlyPrintfSystemMemoryLeack) is called when the memory leack and manage the situation
 */	
	void OPSML(tinf *inf) {
		
		int i;	//(i)nput
		
		OPSE(inf, "The program has a problem whit memory allocation. Probably the RAM is overload. Retry? [y=0 n!=0]", 0, 0);
		scanf("%d", &i);
		if(i == 0)
			return;
		else {
			OPS(inf, "The program crash if you continue whitout this memory allocation. It's more elegant stop it here", 0, 0);
			scanf("I'm a stupid string whitout any sense");
		}
		return;
	}




