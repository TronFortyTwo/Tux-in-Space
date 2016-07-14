/*
#############################################################################
#    CSpace - space simulator												#
#    Copyright (C) 2016  emanuele.sorce@hotmail.com							#
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
 * In this file there are some debug functions
 * 
 */
 
///Prototypes
	void PrintStype(tStype *);

/***
 * This function print the Stype structure
 */
	void PrintStype(tStype *Stype) {
	
		int i; //counter
		
		printf("\nSTYPE PRINTING-------------------------\n");
		
		for (i=0; i!=Stype->number; i++) {
			printf("\nNAME: %s\nDESCRIPTION: %s\nPARENT: %s\nMASS_MIN: %lf\nMASS_MAX: %lf\n", Stype->type[i].name, Stype->type[i].description, Stype->type[i].parent, Stype->type[i].mass_min, Stype->type[i].mass_max);
			printf("BLUE_RANGE: %i - %i\n", Stype->type[i].color_min.blue, Stype->type[i].color_max.blue);
			printf("RED_RANGE: %i - %i\n", Stype->type[i].color_min.red, Stype->type[i].color_max.red);
			printf("GREEN_RANGE: %i - %i\n", Stype->type[i].color_min.green, Stype->type[i].color_max.green);
		}
		return;
	}
