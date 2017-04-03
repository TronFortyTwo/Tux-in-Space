/*
#############################################################################
#    CSpace - space simulator												#
#    Copyright (C) 2016-2017  emanuele.sorce@hotmail.com					#
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
 *
 * The function OnlyPrintfSystem: print words in a simple behavior that adapts on the value of width and height
 * 
 * The advantages on use OnlyPrintfSystem is:
 * 		- A simply but nice automatic impagination that all function could use whit a simple call 
 * 		- make the program nice
 * 		- A very more simple algoritm (faster and lighter) respect more complex mode (like the AIB), but equally can adapts the width and height numbers
 * 		- Use only of the Standard C library for now
 *
 * 	NOTE:
 * 	OnlyPrintfSystem is often called OPS
 * 
 */

#include "OnlyPrintfSystem.h"

using namespace std;

// internal constant
#define FRAME "# "
#define FRAMER " #"		// FRAME R(ight)
#define FRAMELEN 2		// FRAME LENGHT
#define TWOFRAMELEN 4	// 2 * FRAME LENGHT
#define FRAMESTART "#"
#define FRAMEEND " "
#define THEETDESCR 5	// The number of space when '&td'

// internal functions
void OPS_Line(int, const string&, int);


/**Only Printf System */
void OPS(const setting& set, const std::string& phrase, const void *const* const var) {
	
	// counter for lines
	UWORD linedone;
	// counter for columns
	UWORD columndone;
	// the number of character of phrase elaborated
	QWORD chardone = 0;
	// the number of space to leave blank at the start of every line (max one digit)
	BYTE indentation = 0;
	// one if the buf is finished
	BYTE bufend = 0;
	// the position in the var array
	QWORD pos = 0;
	// the buffer to print, and his position
	string buf;


	// OPS PART ONE: writing the buffer. Elaborate the input and write it in buf
	while(1) {
	
		// dinamic printing! (character that mean other character, here translated)
		if(phrase[chardone] == '%') {
			// advance to the next character
			chardone++;
			// an int value to print
			if(phrase[chardone] == 'i') {
				buf +=  *((int *) var[pos]);
			}
			// an unsigned int value to print
			if(phrase[chardone] == 'u') {
				buf += *((unsigned int *)var[pos]);
				pos++;
			}
			// a long double value to print
			else if(phrase[chardone] == 'l') {
				buf += *((long double *)var[pos]);
				pos++;
			}
			// a string to print
			else if(phrase[chardone] == 's') {
				buf += (char *) var[pos];
				pos++;
			}
			// a line to print , f mean '(f)inish line' | example: %f. => a line of '.' NOTE: whitout '\n'
			else if(phrase[chardone] == 'f') {
				chardone++;
				for(unsigned int i=0; i!=set.width-TWOFRAMELEN; i++) {
					buf += phrase[chardone];
				}
			}
			// the '%' character (%%)
			else if(phrase[chardone] == '%' ){
				buf += '%';
			}
			// advance to the next character
			chardone++;
		}
		// the bip character
		else if(phrase[chardone] == '\a') {
			printf("\a");	//bip the bip but don't transfer it to the second part
			chardone++;
		}
		// a normal character
		else if(phrase[chardone] != 0) {
			buf += phrase[chardone];
			chardone++;
		}
		// end of string
		else {
			// put in the buffer the END directive (&e) and exit
			buf += '&';
			buf += 'e';
			break;
		}
	}

	//OPS PART TWO: print the buf
	int i=0;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	//the first two line of the frame
	OPS_Line(set.width, FRAMESTART, 0);
	cout << endl << FRAME;
	OPS_Line(set.width, FRAMEEND, TWOFRAMELEN);
	cout << FRAMER << endl;
	//printf the buf
	for(linedone=0; linedone < set.height-5; linedone++) {
		//the frame
		cout << FRAME;
		//print the buf
		for(columndone=0; columndone < set.width-TWOFRAMELEN; columndone++) {
			
			// PART ONE: check for directives. a directive started whit '&'
			if (buf[i] == '&') {
				i++;
				//if is the '&' character
				if(buf[i] == '&') {
					cout << "&";
					i++;
				}
				//if is the (e)nd directive
				else if(buf[i] == 'e') {
					bufend = 1;
				} 
				//if is a (t)heet directive
				else if(buf[i] == 't') {
					i++;
					// scan the new number
					switch(buf[i]) {
						case '0': indentation=0; break;
						case '1': indentation=1; break;
						case '2': indentation=2; break;
						case '3': indentation=3; break;
						case '4': indentation=4; break;
						case '5': indentation=5; break;
						case '6': indentation=6; break;
						case '7': indentation=7; break;
						case '8': indentation=8; break;
						case '9': indentation=9; break;
						// or scan a letter whit a meaning
						case 'd': indentation=THEETDESCR; break;		// for a description
						case 'i': {								// for a indentation in the 10-19 range
							i++;
							switch(buf[i]) {
								case '0': indentation=10; break;
								case '1': indentation=11; break;
								case '2': indentation=12; break;
								case '3': indentation=13; break;
								case '4': indentation=14; break;
								case '5': indentation=15; break;
								case '6': indentation=16; break;
								case '7': indentation=17; break;
								case '8': indentation=18; break;
								case '9': indentation=19;
							}
						}
					}
				}
				i++;
			}
		
			// PART TWO: print the buffer
			// if the buffer is finished print only spaces
			if (bufend == 1)
				cout << " ";
			// print a space if we are behind the indentation
			else if (columndone < indentation)
				cout << " ";
			// a space in the first column is ignored
			else if ((columndone == indentation) && (buf[i] == ' ')) {
				i++;
				columndone--;
			}
			// a not '\n' character
			else if (buf[i] != '\n') {
				cout << buf[i];
				i++;
			}
			// a '\n' character
			else {
				// print the remaining space whit spaces
				OPS_Line(set.width, " ", columndone+TWOFRAMELEN);
				i++;
				// if there is space for more line print the new line
				if(linedone < set.height-(+5)) {
					cout << FRAMER << endl << FRAME;
					linedone++;
					columndone = -1;
				}
			}
		}
		//the frame
		cout << FRAMER << endl;
	}
	//last lines
	cout << FRAME;
	OPS_Line(set.width, FRAMEEND, TWOFRAMELEN);
	cout << FRAMER << endl;
	OPS_Line(set.width, FRAMESTART, 0);
	cout << endl << FRAME;

}
	
	
/***
 * OPS_Error printf an error intestation before print
 */
void OPS_Error(const setting& set, const string& message, const void *const* const var){
		
	// the message
	string buffer;
	// set the buffer
	buffer = "ERROR!\n\n";
	buffer += message;
	// printf the buffer
	OPS(set, buffer, var);
}

/***
 * OPS_MemLack (OnlyPrintfSystem_MEMoryLACK) is called when the memory lack to signal the problem
 */	
void OPS_MemLack(const string& data) {
		
	cout << "\n\n\n\n\n\n\n\n\n\n\aThe program has a problem whit memory allocation while:" << data << "Probably the RAM is overload. Press something to retry\n\t";
	#if DEBUG
	debug_Printf("OPS_MemLack: the program has problem with memory allocation while:");
	debug_Printf(data);
	#endif
	sgetchar();
}

	
/*** PrintLine is a function that printf a line of characters
 * 	can be setted a number num of characters that must not printed
 *	*/
void OPS_Line (int width, const string& c, int num) {
	int p;	//(p)rinted
	for ( p=width-num; p!=0; p--)
		cout << c;
}
