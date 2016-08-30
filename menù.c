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
	int Menu(tStype *Stype) {
		DebugPrint("menu");
		
		// input variable
		int i;
		
		// The main menù is built in an infinite loop
		while (1) {
		
			//Principal menù, first screen	
			OPS("&t5CSPACE: The space simulator\n\n\n&t01) New system\n2) Load system\n\n3) Settings\n4) Information\n\n5) Quit", NULL);
			SafeIScan(&i);
			
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
				OPS ("Code hosted on GitHub: TronFourtyTwo/CSpace\n\nLICENSE: GNU GPL V3\n\n CSpace - space simulator\nCopyright (C) 2016  emanuele.sorce@hotmail.com\n\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or compatibles. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License version 3 for more details.\n\nYou should have received a copy of the GNU General Public License version 3 along with this program; if not, write to the Free Software Foundation, Inc.\n\nPress something to continue...", NULL);
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
	void OPSsettings() {
		int i;		 // input variable
		void *var[1];
		while(1) {
			OPS("SETTINGS/OPS\n\n1) Change number of columns\n2) Change number of lines\n3) Change number precision\n4) Back", NULL);
			SafeIScan(&i);
			// WIDTH
			if(i == 1) {
				var[0] = &inf.ops.width;
				OPS("SETTINGS/OPS\n\nInsert the new number of columns:\n&tdnow %i", var);
				SafeUScan(&inf.ops.width);
			}
			// HEIGHT
			else if(i == 2){
				var[0] = &inf.ops.height;
				OPS("SETTINGS/OPS\n\nInsert the new number of lines:\n&tdnow %i", var);
				SafeUScan(&inf.ops.height);
			}
			// NUMBER PRECISION
			else if(i == 3){
				var[0] = &inf.ops.numprecision;
				OPS("SETTINGS/OPS\n\nInsert the new number of deciaml digits printed:\n&tdnow %i", var);
				SafeIScan(&i);
				inf.ops.numprecision = i;
			}
			else if(i == 4)
				return;
		}
	}
	void GLsettings() {
		int i;		 // input variable
		void *var[1];
		while(1) {
			OPS("SETTINGS/VIDEO\n\n1) Change window width\n2) Change window height\n3) Change window position\n4) Back", NULL);
			SafeIScan(&i);
			// WIDTH
			if(i == 1) {
				var[0] = &inf.gl.winw;
				OPS("SETTINGS/VIDEO\n\nInsert the new width: of the window\n&tdnow %i pixels", var);
				SafeUScan(&inf.gl.winw);
			}
			// HEIGHT
			else if(i == 2){
				var[0] = &inf.gl.winh;
				OPS("SETTINGS/VIDEO\n\nInsert the new height of the window:\n&tdnow %i pixels", var);
				SafeUScan(&inf.gl.winh);
			}
			// POSITION
			else if(i == 3){
				var[0] = &inf.gl.winx;
				OPS("SETTINGS/VIDEO\n\nInsert the new x of the window:\n&tdnow %i pixels", var);
				SafeUScan(&inf.gl.winx);
				OPS("SETTINGS/VIDEO\n\nInsert the new y of the window:\n&tdnow %i pixels", var);
				SafeUScan(&inf.gl.winy);
			}
			else if(i == 4)
				return;
		}
		
		return;
	}
	 
	void Setting() {
		
		int i;
		void *var[3];
		
		while(1) {
			OPS ("SETTINGS\n\n1) Turn on/off debug\n2) Select video mode\n3) OPS settings\n4) Video settings\n\n5) Done\n6) Restore defaults", NULL);
			SafeIScan(&i);
			
			// TURN ON / OFF DEBUG
			if(i == 1) {
				char debug[2][4];						// Can contein "ON" or "OFF". the first contein the thruth, the second not
				char debugfile[DEBUG_FILE_LENGHT];		// Contein the debug file name
				strcpy(debugfile, DEBUG_FILE);
				if(inf.debug == ON){
					strcpy(debug[0], "ON");
					strcpy(debug[1], "OFF");
				}
				else if(inf.debug == OFF){
					strcpy(debug[0], "OFF");
					strcpy(debug[1], "ON");
				}
				var[0] = &debug[0];
				var[1] = &debug[1];
				var[2] = &debugfile;
				OPS("SETTINGS\n\nNow the debug is %s. Do you want to turn %s the debug? [Y/N]\n&tdthe debug will print in the file '%s' debug information", var);
				scanf("%s", debug[0]);
				if((debug[0][0] == 'y') || (debug[0][0] == 'Y')) {
					if(inf.debug == OFF)
						inf.debug = ON;
					else if(inf.debug == ON)
						inf.debug = OFF;
				}
			}
			// V_MODE
			else if(i == 2){
				char mode[6];
				if (inf.vmode == V_OPS)
					strcpy(mode, "OPS");
				else
					strcpy(mode, "GLUT");
				var[0] = &mode;
				OPS("SETTINGS\n\nNow the video mode is %s. Select the video mode:\n1) OPS\n2) GLUT --EXPERIMENTAL--", var);
				SafeIScan(&inf.vmode);
				if(inf.vmode == 2)
					inf.vmode = V_FREEGLUT;
				else
					inf.vmode = V_OPS;
			}
			// OPS settings
			else if(i == 3)
				OPSsettings();
			// GL settings
			else if(i == 4)
				GLsettings();
			// DONE
			else if(i == 5)
				break;
			// RESTORE DEFAULTS
			else if(i == 6){
				char input[2];
				OPS("SETTINGS\n\nAre you sure you want to restore the settings to the default ones? [y/N]", NULL);
				scanf("%s", input);
				if ((input[0] == 'n') || (input[0] == 'N'))
					continue;
				SetDefaultConfig();
			}
		}
		// Save and exit
		SaveConfig();
		return;
	}
	
	
