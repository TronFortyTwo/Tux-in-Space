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
 * This function is the mean menù of the program
 * The returning value is a number that shell needs for know what do
 * 
 */
 
#include "generic.h"
#include "menù.h"
#include "OnlyPrintfSystem.h"
#include "in.h"
#include "setting.h"

// Internal functions
void menu_Settings_G();
void menu_Settings_OPS();


int menu_main(tStype *Stype) {
		
	// input variable
	int i;
		
	// The main menù is built in an infinite loop
	while (1) {
		
		//Principal menù, first screen	
		OPS("&t5CSPACE: The space simulator\n\n\n&t01) New system\n2) Load system\n\n3) Settings\n4) informations\n\n5) Quit", NULL);
		in_i(&i);
			
		// If "new simulation" tell the Shell 0; (uninitialized obj)
		if (i == 1)
			return NEW_SIG;
				
		// if "Load system" tell the Shell 1;
		else if (i == 2)
			return LOAD_SIG;
			
		// If is menu_Settings can be changed value set
		else if (i == 3)
			menu_Settings(set);
		// if settingrmation printf the license
		else if(i == 4){
			OPS ("Code hosted on GitHub: TronFourtyTwo/CSpace\n\nLICENSE: GNU GPL V3\n\n CSpace - space simulator\nCopyright (C) 2016  emanuele.sorce@hotmail.com\n\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or compatibles. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License version 3 for more details.\n\nYou should have received a copy of the GNU General Public License version 3 along with this program; if not, write to the Free Software Foundation, Inc.\n\nPress something to continue...", NULL);
			sgetchar();
		}
		else if(i == 5)
			return QUITSIGNAL;
	}
	return BADSIGNAL;
}

/***
 * menu_Settings. here can be changed some value of tset set
 */
void menu_Settings_OPS() {
	int i;		 // input variable
	void *var[1];
	while(1) {
		OPS("SETTINGS/OPS\n\n1) Change number of columns\n2) Change number of lines\n3) Change number precision\n4) Back", NULL);
		in_i(&i);
		// WIDTH
		if(i == 1) {
			var[0] = &set.ops.width;
			OPS("SETTINGS/OPS\n\nInsert the new number of columns:\n&tdnow %i", var);
			in_u(&set.ops.width);
		}
		// HEIGHT
		else if(i == 2){
			var[0] = &set.ops.height;
			OPS("SETTINGS/OPS\n\nInsert the new number of lines:\n&tdnow %i", var);
			in_u(&set.ops.height);
		}
		// NUMBER PRECISION
		else if(i == 3){
			var[0] = &set.ops.numprecision;
			OPS("SETTINGS/OPS\n\nInsert the new number of deciaml digits printed:\n&tdnow %i", var);
			in_i(&i);
			set.ops.numprecision = i;
		}
		else if(i == 4)
			return;
	}
}
void menu_Settings_G() {
	int i;		 // input variable
	while(1) {
		OPS("SETTINGS/VIDEO\n\n1) Back", NULL);
		in_i(&i);
		if(i == 1)
			return;
	}
	
	return;
}
	 
void menu_Settings() {
	
	int i;
	void *var[3];
		
	while(1) {
		OPS ("SETTINGS\n\n1) Select video mode\n2) OPS settings\n3) Video settings\n\n4) Done\n5) Restore defaults", NULL);
		in_i(&i);

		// V_MODE
		if(i == 1){
			char mode[4];
			if (set.vmode == V_OPS)
				strcpy(mode, "OPS");
			else
				strcpy(mode, "SDL");
			var[0] = &mode;
			OPS("SETTINGS\n\nNow the video mode is %s. Select the video mode:\n1) OPS\n2) SDL --EXPERIMENTAL--", var);
			in_i(&set.vmode);
			if(set.vmode == 2)
				set.vmode = V_SDL;
			else
				set.vmode = V_OPS;
		}
		// OPS settings
		else if(i == 2)
			menu_Settings_OPS();
		// Graphic settings
		else if(i == 3)
			menu_Settings_G();
		// DONE
		else if(i == 4)
			break;
		// RESTORE DEFAULTS
		else if(i == 5) {
			char input[2];
			OPS("SETTINGS\n\nAre you sure you want to restore the settings to the default ones? [y/N]", NULL);
			scanf("%s", input);
			if ((input[0] == 'n') || (input[0] == 'N'))
				continue;
			set_SetDefault();
		}
	}
	// Save and exit
	set_Save();
	return;
}
