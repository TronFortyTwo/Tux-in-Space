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
		
		// A variable that save the scanf of an input
		int i;
		void *var;
		
		// The main menù is built in an infinite loop
		for(;;) {
		
			//Principal menù, first screen	
			OPS(inf, "&t5CSPACE: The space's simulator\n\n\n&t01) New system\n2) Load system\n\n3) Settings\n4) Information\n\n5) Quit", NULL);
			SafeIScan(inf, &i);
			
			// If "new simulation" tell the Shell 0; (uninitialized obj)
			if (i == 1)
				return 0;
				
			// if "Load system" tell the Shell 1;
			else if (i == 2)
				return 1;
				
			// If is setting can be changed value of some variabiles
			else if (i == 3) {
				var = &inf->width;
				OPS (inf,"New number of columns (now %i):", &var);
				SafeIScan(inf, &inf->width);
				var = &inf->height;
				OPS (inf, "New number of lines (now %i):", &var);
				SafeIScan(inf, &inf->height);
				var = &inf->numprecision;
				OPS (inf, "New number of number's decimal printed (now %i):", &var);
				SafeIScan(inf, &inf->numprecision);
				OPS (inf, "Output mode:\n1)Only OnlyPrintfSystem based\n&tdThis option allow only textual output whitout any image but is fast and nice\n&t02)ASCII AIB renderizer (WORK IN PROGRESS)\n&tdThe Abstract Image Builder option allow images and a GUI but using a terminal interface. For now is unusable", NULL);
				SafeIScan(inf, &inf->vmode);
				inf->vmode--;
			}
			// if information printf the license
			else if(i == 4){
				OPS (inf, "Code hosted on GitHub: TronFourtyTwo/CSpace\n\nLICENSE: GNU GPL V3\n\n CSpace - space simulator\nCopyright (C) 2016  emanuele.sorce@hotmail.com\n\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or compatibles. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License version 3 for more details.\n\nYou should have received a copy of the GNU General Public License version 3 along with this program; if not, write to the Free Software Foundation, Inc.\n\nPress a number to conitinue", NULL);
				SafeIScan(inf, &i);
			}
			else if(i == 5)
				return QUITSIGNAL;
		}
		
		return 0;
	}
