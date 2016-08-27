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
	int Menu(tinf *inf, tStype *Stype) {
		DebugPrint(inf, "menu");
		
		// input variable
		int i;
		
		// The main menù is built in an infinite loop
		while (1) {
		
			//Principal menù, first screen	
			OPS(inf, "&t5CSPACE: The space simulator\n\n\n&t01) New system\n2) Load system\n\n3) Settings\n4) Information\n\n5) Quit", NULL);
			SafeIScan(inf, &i);
			
			// If "new simulation" tell the Shell 0; (uninitialized obj)
			if (i == 1)
				return NEW_SIG;
				
			// if "Load system" tell the Shell 1;
			else if (i == 2)
				return LOAD_SIG;
				
			// If is setting can be changed value inf
			else if (i == 3)
				Setting(inf);
			// if information printf the license
			else if(i == 4){
				OPS (inf, "Code hosted on GitHub: TronFourtyTwo/CSpace\n\nLICENSE: GNU GPL V3\n\n CSpace - space simulator\nCopyright (C) 2016  emanuele.sorce@hotmail.com\n\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or compatibles. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License version 3 for more details.\n\nYou should have received a copy of the GNU General Public License version 3 along with this program; if not, write to the Free Software Foundation, Inc.\n\nPress something to continue...", NULL);
				getchar();
			}
			else if(i == 5)
				return QUITSIGNAL;
		}
		return BADSIGNAL;
	}
	
	/***
	 * Setting. here can be changed some value of tinf inf
	 */
	void Setting(tinf *inf) {
		
		int i;
		BYTE quit = OFF;
		void *var[3];
		
		while(quit == OFF) {
			OPS (inf, "SETTING\n\n1) Change number of columns\n2) Change number of lines\n3) Change number precision\n4) Turn on/off debug\n\n5) Done\n6) Restore defaults", NULL);
			SafeIScan(inf, &i);
			// WIDTH
			if(i == 1) {
				var[0] = &inf->width;
				OPS(inf, "SETTING\n\nInsert the new number of columns:\n&tdnow %i", var);
				SafeIScan(inf, &inf->width);
			}
			// HEIGHT
			else if(i == 2){
				var[0] = &inf->height;
				OPS(inf, "SETTING\n\nInsert the new number of lines:\n&tdnow %i", var);
				SafeIScan(inf, &inf->height);
			}
			// NUMBER PRECISION
			else if(i == 3){
				var[0] = &inf->numprecision;
				OPS(inf, "SETTING\n\nInsert the new number decimal printed:\n&tdnow %i", var);
				SafeIScan(inf, &i);
				inf->numprecision = i;
			}
			// TURN ON / OFF DEBUG
			else if(i == 4) {
				char debug[2][4];						// Can contein "ON" or "OFF". the first contein the thruth, the second not
				char debugfile[DEBUG_FILE_LENGHT];		// Contein the debug file name
				strcpy(debugfile, DEBUG_FILE);
				if(inf->debug == ON){
					strcpy(debug[0], "ON");
					strcpy(debug[1], "OFF");
				}
				else if(inf->debug == OFF){
					strcpy(debug[0], "OFF");
					strcpy(debug[1], "ON");
				}
				var[0] = &debug[0];
				var[1] = &debug[1];
				var[2] = &debugfile;
				OPS(inf, "SETTING\n\nNow the debug is %s. Do you want to turn %s the debug? [Y/N]\n&tdthe debug will print in the file '%s' debug information", var);
				scanf("%s", debug[0]);
				if((debug[0][0] == 'y') || (debug[0][0] == 'Y')) {
					if(inf->debug == OFF)
						inf->debug = ON;
					else if(inf->debug == ON)
						inf->debug = OFF;
				}
			}
			// DONE
			else if(i == 5)
				quit = ON;
			// RESTORE DEFAULTS
			else if(i == 6){
				char input[2];
				OPS(inf, "SETTING\n\nAre you sure you want to restore the settings to the default ones? [y/N]", NULL);
				scanf("%s", input);
				if ((input[0] == 'n') || (input[0] == 'N'))
					continue;
				SetDefaultConfig(inf);
			}
		}
		// Save and exit
		SaveConfig(inf);
		return;
	}
	
	
