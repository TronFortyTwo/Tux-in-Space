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
	// counter for lines
	int linedone;
	// counter for columns
	int columndone;
	// the number of character of phrase elaborated
	int chardone;
	// the number of space to leave blank at the start of every line (max one digit)
	int theet = 0;
	// one if the buf is finished
	int bufend = 0;
	// the position in the int and long double arrays
	int ipos=0;
	int lpos=0;
	// the buffer to print, his size and position
	int size = (inf->width-TWOFRAMELUN) * (inf->height-5) +1;
	char *buf = (char *) malloc (sizeof(char)*size);
	int bufpos = 0;
	
	//signal if there is a memory leack
	while (buf == NULL) {
		OPSML(inf, "OPS");
		buf = (char *) malloc (sizeof(char)*((inf->width-TWOFRAMELUN)*(inf->height-5)+1));
	};
	
	//OPS PART ONE: writing the buffer. Elaborate the input and write it in buf
	for(chardone=0; bufpos!=size-1;) {
		
		//dinamic printing! (character that mean other character, here translated)
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
			//a line to print , f mean '(f)inish line' | example: %f. => a line of '.', but whitout '\n'
			else if(phrase[chardone] == 'f') {
				chardone++;
				for(i=0; i!=inf->width-TWOFRAMELUN; i++) {
					buf[bufpos] = phrase[chardone];
					bufpos++;
				}
				chardone++;
			}
			// the % character (%%)
			else if(phrase[chardone] == '%' ){
				chardone++;
				buf[bufpos] = '%';
				bufpos++;
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
			//put in the buffer the END directive (&e) and exit
			buf[bufpos] = '&';
			bufpos++;
			buf[bufpos] = 'e';
			break;
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
		//print the buf
		for(columndone=0; columndone!=inf->width-TWOFRAMELUN; columndone++) {
			
			// PART ONE: check for directives. a directive started whit '&'
			if (buf[bufpos] == '&') {
				bufpos++;
				//if is the '&' character
				if(buf[bufpos] == '&') {
					printf("&");
					bufpos++;
				}
				//if is the (e)nd directive
				else if(buf[bufpos] == 'e') {
					bufend++;
				} 
				//if is a (t)heet directive
				else if(buf[bufpos] == 't') {
					bufpos++;
					//scan the new number (max one digit)
					if (buf[bufpos] == '0') theet=0;
					else if (buf[bufpos] == '1') theet=1;
					else if (buf[bufpos] == '2') theet=2;
					else if (buf[bufpos] == '3') theet=3;
					else if (buf[bufpos] == '4') theet=4;
					else if (buf[bufpos] == '5') theet=5;
					else if (buf[bufpos] == '6') theet=6;
					else if (buf[bufpos] == '7') theet=7;
					else if (buf[bufpos] == '8') theet=8;
					else if (buf[bufpos] == '9') theet=9;
				}
				bufpos++;
			}
			
			// PART TWO: print the buffer
			// if the buffer is finished print only spaces
			if (bufend == 1)
				printf(" ");
			// print the number of spaces conteined in theet if at the start of the line
			else if (columndone < theet)
				printf(" ");
			// a space in the first column is ignored (calculating that the first column can have )
			else if ((columndone == theet) && (buf[bufpos] == ' ')) {
				bufpos++;
				columndone--;
			}
			// a normal character
			else if (buf[bufpos] != '\n') {
				printf("%c", buf[bufpos]);
				bufpos++;
			}
			// a '\n' character
			else {
				PrintLine(inf, " ", columndone+TWOFRAMELUN);
				bufpos++;
				// if there isn't space for more line
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
	printf("\n%s: ", FRAME);
	
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
		//printf the buffer
		OPS(inf, buffer, ivar, lvar);
		//exit the function
		free(buffer);
		return;
	}

/***
 * OPSML (OnlyPrintfSystemMemoryLeack) is called when the memory leack and manage the situation
 */	
	void OPSML(tinf *inf, char *data) {
		
		char i[2];	//(i)nput
		
		printf ("\n\n\n\n\n\n\n\n\n\n\n\n\aThe program has a problem whit memory allocation while: '%s'. Probably the RAM is overload. Press something to retry\n\t", data);
		scanf("%s", i);
		
		return;
	}




