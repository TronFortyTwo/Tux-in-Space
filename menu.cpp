/*
#############################################################################################
#    CSpace - space simulator																#
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
		OPS(set, "&t5CSPACE: The space simulator\n\n\n&t01) New system\n2) Load system\n\n3) Settings\n4) informations\n\n5) Quit");
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
		OPS(set, "SETTINGS/OPS\n\n1) Change number of columns\n2) Change number of lines\n3) Change number precision\n4) Back");
		i = in_i();
		// WIDTH
		if(i == 1) {
			OPS(set, "SETTINGS/OPS\n\nInsert the new number of columns:\n&tdnow " + to_string(set.width) + ", recommended minimum 68");
			set.width = in_i();
		}
		// HEIGHT
		else if(i == 2){
			OPS(set, "SETTINGS/OPS\n\nInsert the new number of lines:\n&tdnow " + to_string(set.height) + ", recommended minimum 48");
			set.height = in_i();
		}
		// NUMBER PRECISION
		else if(i == 3){
			OPS(set, "SETTINGS/OPS\n\nInsert the new number of deciaml digits printed:\n&tdnow " + to_string(set.numprecision));
			i = in_i();
			set.numprecision = i;
		}
		else if(i == 4)
			return;
	}
}
void menu_Settings_G(setting& set) {
	int i;		 // input variable
	while(1) {
		OPS(set, "SETTINGS/VIDEO\n\n1) Back");
		i = in_i();
		if(i == 1)
			return;
	}
}
	 
void menu_Settings(setting& set) {
	
	int i;
	string input;
		
	while(1) {
		OPS (set, "SETTINGS\n\n1) Select video mode\n2) OPS settings\n3) Video settings\n\n4) Done\n5) Restore defaults");
		i = in_i();

		// V_MODE
		if(i == 1){
			std::string mode;
			if (set.vmode == videomode::OPS)
				mode = "OPS";
			else
				mode = "Graphic";
			OPS(set, "SETTINGS\n\nNow the video mode is " + mode + ". Select the video mode:\n1) OPS\n2) GRAPHIC --EXPERIMENTAL--");
			input = in_i();
			if (input[0] == 2)
				set.vmode = videomode::GL;
			else
				set.vmode = videomode::OPS;
		}
		// OPS settings
		else if(i == 2)
			menu_Settings_OPS(set);
		// Graphic settings
		else if(i == 3)
			menu_Settings_G(set);
		// DONE
		else if(i == 4)
			break;
		// RESTORE DEFAULTS
		else if(i == 5) {
			char input[2];
			OPS(set, "SETTINGS\n\nAre you sure you want to restore the settings to the default ones? [y/N]");
			scanf("%s", input);
			if ((input[0] == 'n') || (input[0] == 'N'))
				continue;
			set.Defaults();
		}
	}
	// Save and exit
	set.Save();
}
