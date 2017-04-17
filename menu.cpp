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

int menu_main(setting& set) {
		
	// input variable
	int i;
		
	// The main menù is built in an infinite loop
	while (1) {
		
		//Principal menù, first screen	
		OPS(set, "&t5CSPACE: The space simulator\n\n\n&t01) New system\n2) Load system\n\n3) Settings\n4) informations\n\n5) Quit", nullptr);
		cin >> i;
			
		// If "new simulation" tell the Shell 0; (uninitialized obj)
		switch (i) {
			case 1:
				return NEW_SIG;
			// if "Load system" tell the Shell 1;
			case 2:
				return LOAD_SIG;
			// If is menu_Settings can be changed value set
			case 3:
				menu_Settings(set);
				break;
			// if information printf the license banner
			case 4: 
				OPS (set, "Code hosted on GitHub: TronFourtyTwo/CSpace\n\nLICENSE: GNU GPL V3\n\n CSpace - space simulator\nCopyright (C) 2016-2017  emanuele.sorce@hotmail.com\n\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or compatibles. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License version 3 for more details.\n\nYou should have received a copy of the GNU General Public License version 3 along with this program; if not, write to the Free Software Foundation, Inc.\n\nPress something to continue...", nullptr);
				in_s();
				break;
			case 5:
				return ABORTED_SIG;
		}
	}
	return BAD_SIG;
}

/***
 * menu_Settings. here can be changed some value of tset set
 */
void menu_Settings_OPS(setting& set) {
	int i;		 // input variable
	void *var[1];
	while(1) {
		OPS(set, "SETTINGS/OPS\n\n1) Change number of columns\n2) Change number of lines\n3) Change number precision\n4) Back", nullptr);
		cin >> i;
		// WIDTH
		if(i == 1) {
			var[0] = &set.width;
			OPS(set, "SETTINGS/OPS\n\nInsert the new number of columns:\n&tdnow %i", var);
			cin >> set.width;
		}
		// HEIGHT
		else if(i == 2){
			var[0] = &set.height;
			OPS(set, "SETTINGS/OPS\n\nInsert the new number of lines:\n&tdnow %i", var);
			cin >> set.height;
		}
		// NUMBER PRECISION
		else if(i == 3){
			var[0] = &set.numprecision;
			OPS(set, "SETTINGS/OPS\n\nInsert the new number of deciaml digits printed:\n&tdnow %i", var);
			cin >> i;
			set.numprecision = i;
		}
		else if(i == 4)
			return;
	}
}
void menu_Settings_G(setting& set) {
	int i;		 // input variable
	while(1) {
		OPS(set, "SETTINGS/VIDEO\n\n1) Back", nullptr);
		cin >> i;
		if(i == 1)
			return;
	}
}
	 
void menu_Settings(setting& set) {
	
	int i;
	void *var[3];
		
	while(1) {
		OPS (set, "SETTINGS\n\n1) Select video mode\n2) OPS settings\n3) Video settings\n\n4) Done\n5) Restore defaults", nullptr);
		cin >> i;

		// V_MODE
		if(i == 1){
			std::string mode;
			if (set.vmode == V_OPS)
				mode = "OPS";
			else
				mode = "Graphic";
			var[0] = &mode;
			OPS(set, "SETTINGS\n\nNow the video mode is %s. Select the video mode:\n1) OPS\n2) GRAPHIC --EXPERIMENTAL--", var);
			cin >> set.vmode;
			if(set.vmode == 2)
				set.vmode = V_GL;
			else
				set.vmode = V_OPS;
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
			OPS(set, "SETTINGS\n\nAre you sure you want to restore the settings to the default ones? [y/N]", nullptr);
			scanf("%s", input);
			if ((input[0] == 'n') || (input[0] == 'N'))
				continue;
			set.Defaults();
		}
	}
	// Save and exit
	set.Save();
}
