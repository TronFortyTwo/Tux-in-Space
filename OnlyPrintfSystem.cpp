/*
#############################################################################
#    Tux in Space - space exploration game									#
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
 * OnlyPrintfSystem: print words in a simple way, with some nice feature
 * 
 * The advantages on use OnlyPrintfSystem is:
 * 		- A simply but nice automatic impagination that all function could use with a simple call 
 * 		- make the program nice
 * 		- Use only of the Standard C library for now
 *
 * 	NOTE:
 * 	OnlyPrintfSystem is aka OPS
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
void OPS(const setting& set, const std::string& phrase) {
	
	// counter for lines
	unsigned int linedone;
	// counter for columns
	unsigned int columndone;
	// the number of character of phrase elaborated
	unsigned int phrase_pos = 0;
	// the number of space to leave blank at the start of every line (max one digit)
	unsigned int indentation = 0;
	// the buf is finished?
	bool bufend = false;
	// the buffer to print, and his position
	stringstream buf;

	// PART ONE: writing the buffer. Elaborate the input and write it in buf
	while(1) {
	
		// dinamic printing! (character that mean other character, here translated)
		if(phrase[phrase_pos] == '%') {
			// advance to the next character
			phrase_pos++;
			// a line to print , r means 'row' | example: %r. => a row of '.' NOTE: whitout '\n'
			if(phrase[phrase_pos] == 'r') {
				phrase_pos++;
				for(unsigned int i=0; i!=set.width-TWOFRAMELEN; i++) {
					buf << phrase[phrase_pos];
				}
			}
			// the '%' character (%%)
			else if(phrase[phrase_pos] == '%' ){
				buf << '%';
			}
			// advance to the next character
			phrase_pos++;
		}
		// the bip character
		else if(phrase[phrase_pos] == '\a') {
			printf("\a");	//bip the bip but don't transfer it to the second part
			phrase_pos++;
		}
		// a normal character
		else if(phrase[phrase_pos] != 0) {
			buf << phrase[phrase_pos];
			phrase_pos++;
		}
		// end of string
		else {
			// put in the buffer the END directive (&e) and exit
			buf << "&e";
			break;
		}
	}

	// PART TWO: print the buf
	int p=0;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	//the first two line of the frame
	OPS_Line(set.width, FRAMESTART, 0);
	cout << "\n" << FRAME;
	OPS_Line(set.width, FRAMEEND, TWOFRAMELEN);
	cout << FRAMER << "\n";
	//printf the buf
	for(linedone=0; linedone < set.height-5; linedone++) {
		//the frame
		cout << FRAME;
		//print the buf
		for(columndone=0; columndone < set.width-TWOFRAMELEN; columndone++) {
			
			// PART ONE: check for directives. a directive started whit '&'
			if (buf.str()[p] == '&') {
				p++;
				//if is the '&' character
				if(buf.str()[p] == '&') {
					cout << "&";
					p++;
				}
				//if is the (e)nd directive
				else if(buf.str()[p] == 'e') {
					bufend = 1;
				} 
				//if is a (t)heet directive
				else if(buf.str()[p] == 't') {
					p++;
					// scan the new number
					switch(buf.str()[p]) {
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
							p++;
							switch(buf.str()[p]) {
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
				p++;
			}
		
			// PART TWO: print the buffer
			// if the buffer is finished print only spaces
			// print a space if we are behind the indentation
			if ((bufend == true)||(columndone < indentation))
				cout << " ";
			// a space in the first column is ignored
			else if ((columndone == indentation) && (buf.str()[p] == ' ')) {
				p++;
				columndone--;
			}
			// a not '\n' character
			else if (buf.str()[p] != '\n') {
				cout << buf.str()[p];
				p++;
			}
			// a '\n' character
			else {
				// print the remaining space whit spaces
				OPS_Line(set.width, " ", columndone+TWOFRAMELEN);
				p++;
				// if there is space for more line print the new line
				if(linedone < set.height-5) {
					cout << FRAMER << "\n" << FRAME;
					linedone++;
					columndone = -1;
				}
			}
		}
		// the frame
		cout << FRAMER << "\n";
	}
	// last lines
	cout << FRAME;
	OPS_Line(set.width, FRAMEEND, TWOFRAMELEN);
	cout << FRAMER << "\n";
	OPS_Line(set.width, FRAMESTART, 0);
	cout << endl << FRAME;

}
	
	
/***
 * OPS_Error printf an error intestation before print
 */
void OPS_Error(const setting& set, const string& message){
		
	// the message
	string buffer;
	// set the buffer
	buffer = "ERROR!\n\n";
	buffer += message;
	// printf the buffer
	OPS(set, buffer);
}

/***
 * OPS_MemLack (OnlyPrintfSystem_MEMoryLACK) is called when the memory lack to signal the problem
 */	
void OPS_MemLack(const string& data) {
		
	cout << "\n\n\n\n\n\n\n\n\n\n\aThe program has a problem whit memory allocation while:" << data << "Probably the RAM is overload. Press something to retry\n\t";
	debug_Printf("OPS_MemLack: the program has problem with memory allocation while:");
	debug_Printf(data);
	in_s();
}

	
/*** PrintLine is a function that printf a line of characters
 * 	can be setted a number num of characters that must not printed
 *	*/
void OPS_Line (int width, const string& c, int num) {
	int p;	//(p)rinted
	for ( p=width-num; p!=0; p--)
		cout << c;
}
