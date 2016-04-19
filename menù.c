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
 * The returning value is a number that shell need for know how to initialize obj
 * 
 * NOTE:
 * In this function we call Rmotor, but the only the OPS. Then we don't need to know the *objstruct, so we tell to Rmotor that it is 0. 
 * 
 * 
 */
 
 
	int Menu(tinf *inf);

	int Menu (tinf *inf) {
		
		// A variable that save the scanf of an input. And do other too...
		int inputandothers;
		
		// The main menù is built in an infinite loop
		for(;;) {
		
			//Principal menù, first screen	
			Rmotor(0, inf, 0, ".   CSPACE: The space's simulator\n\n-New system: 1\n-Settings: 2\n-Information: 3\n", 0, 0, 0);
			scanf("%d", &inputandothers);
			fflush(stdin);
			
			// If "new simulation" tell the Shell 0; (uninitialized obj)
			if (inputandothers == 1) {
				return 0;
			}
		
			// If is setting can be changed value of some variabiles
			else if (inputandothers == 2)	{
				inputandothers = inf->column;
				Rmotor(0, inf, 0, "New number of columns (now %i):", &inputandothers, 0, 0);
				scanf("%d", &inf->column);
				fflush(stdin);
				Setmaxoutput(inf);
				inputandothers = inf->line;
				Rmotor(0, inf, 0, "New number of lines (now %i):", &inputandothers, 0, 0);
				Setmaxoutput(inf);
				scanf("%d", &inf->line);
				fflush(stdin);
				inputandothers=inf->numprecision;
				Rmotor(0, inf, 0, "New number of number's decimal printed (now %i):", &inputandothers, 0, 0);
				scanf("%d", &inf->numprecision);
				fflush(stdin);
			}
			// if information printf the license
			else if(inputandothers == 3){
				Rmotor(0, inf, 0, "LICENSE: GNU GPL V3\n\n CSpace - space simulator\nCopyright (C) 2016  emanuele.sorce@hotmail.com\n\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or compatibles. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License version 3 for more details.\n\nYou should have received a copy of the GNU General Public License version 3 along with this program; if not, write to the Free Software Foundation, Inc.\n\nPress a number to conitinue", 0, 0, 0);
				scanf("%d", &inputandothers);
			}
		}
		return 0;
	}
