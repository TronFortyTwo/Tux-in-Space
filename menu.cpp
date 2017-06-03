/*
#############################################################################################
#    Tux in Space - space exploration game													#
#    Copyright (C) 2016-2017  emanuele.sorce@hotmail.com									#
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
 * This function is the mean menù of the program
 * The returning value is a number that shell needs for know what do
 * 
 */


#include "menu.h"

using namespace std;

// Internal functions
void menu_Settings_G(setting&);
void menu_Settings_OPS(setting&);

signal menu_main(setting& set) {
		
	// input variable
	int i;
		
	// The main menù is built in an infinite loop
	while (1) {
		
		//Principal menù, first screen	
		OPS(set, "%r-&t3TUX IN SPACE&t0\n%r-\n&t01) New system\n2) Load system\n\n3) Settings\n4) informations\n\n5) Quit");
		i = in_i();
			
		// If "new simulation" tell the Shell 0; (uninitialized obj)
		switch (i) {
			case 1:
				return signal::create;
			case 2:
				return signal::load;
			case 3:
				menu_Settings(set);
				break;
			case 4: 
				OPS (set, BANNER "\n\nPress something to continue...");
				in_s();
				break;
			case 5:
				return signal::aborted;
		}
	}
}

/***
 * menu_Settings. here can be changed some value of tset set
 */
void menu_Settings_OPS(setting& set) {
	int i;		 // input variable
	while(1) {
		OPS(set, "SETTINGS/TEXT MODE\n\n1) Change number of columns\n2) Change number of lines\n3) Back");
		i = in_i();
		// WIDTH
		if(i == 1) {
			OPS(set, "SETTINGS/TEXT MODE\n\nInsert the new number of columns:\n&tdnow " + to_string(set.width) + ", recommended minimum 68");
			set.width = in_i();
		}
		// HEIGHT
		else if(i == 2){
			OPS(set, "SETTINGS/TEXT MODE\n\nInsert the new number of lines:\n&tdnow " + to_string(set.height) + ", recommended minimum 48");
			set.height = in_i();
		}
		else if(i == 3)
			return;
	}
}
	 
void menu_Settings(setting& set) {
	
	int i;
	string input;
		
	while(1) {
		OPS (set, "SETTINGS\n\n1) Text mode settings\n\n2) Done\n3) Restore defaults");
		i = in_i();

		// OPS settings
		if(i == 1)
			menu_Settings_OPS(set);
		// DONE
		else if(i == 2)
			break;
		// RESTORE DEFAULTS
		else if(i == 3) {
			char input[2];
			OPS(set, "SETTINGS\n\nAre you sure you want to restore the settings to the default ones? [y/N]");
			scanf("%s", input);
			if ((input[0] == 'n') || (input[0] == 'N'))
				continue;
			set.Defaults();
		}
		else
			continue;
	}
	// Save and exit
	set.Save();
}
