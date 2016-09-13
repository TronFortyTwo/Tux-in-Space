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
 * HERE we have low-level functions that help whit the core system of the program
 * 
 */

/***
 * 	This function delete an object freeing the memory
 */
	void CleanObject(tobj *obj) {
		// free the name
		free(obj->name);
	}

/***
 * This function Delete an object from the system object buffer in an automatic way, ehitout the need of more free() or sys->nactive--, and resize the buffer. all the code is packed here
 * So, call it whitout worry
 * p is the position of the object
 */
	void AutoRemoveObject (tsys *sys, int p) {
		// Move the last object in the p position, update counters and free memory
		CleanObject(&sys->o[p]);
		sys->o[p] = sys->o[--sys->nactive];
		// if necessary resize the object buffer
		if(sys->nalloc - sys->nactive >= OBJBUFSIZE)
			ReduceObjBuf(sys);
	}
 
 
 
/***
 * The load object function load from a file the information about a object
 */
	int LoadObject(tobj *obj, tStype *Stype, char *name) {
		DebugPrint("loadobject");
		
		FILE *ofile;				// (the) o(bject) file
		char path [NAMELUN + 15];	// the path of the object
		
		strcpy(path, OBJECT_PATH);
		strcat(path, name);
		strcat(path, ".object");
		
		ofile = fopen(path, "r");
		while(ofile == NULL)
			return FILE_ERR_SIG;
		
		// Read type, color, radius and mass
		ReadObject(ofile, obj, Stype);
		
		//close the file and exit
		fclose(ofile);
		
		return GOODSIGNAL;
	}
 
/***
 * The SaveObject function save a object in a file
 */
	void SaveObject(tobj *obj) {
		DebugPrint("SaveObject");
	
		//the path where the object must be saved, an input variable and the destination file pointer
		char path[NAMELUN+16];
		char input[2];
		FILE *dest;
		
		//Write the path
		strcpy(path, OBJECT_PATH);
		strcat(path, obj->name);
		strcat(path, ".object");
		
		//control that the file isn't alredy existent
		dest = fopen(path, "r");
		if(dest != NULL) {
			fclose(dest);
			OPS("While saving: The object you want to save alredy exist.\nDo you want to delete the previous object and save this? [n = no | something else = y]", NULL);
			scanf("%s", input);
			if(strcmp(input, "n") == 0)
				return;
		}
	
		// Write the object
		dest = fopen(path, "w");
		WriteObject(dest, obj);
		fclose(dest);
	
		return;	
	}

/***
 * This function return a "random" int in a range given, but the gap can't be greater than 100
 */
	int RandomInt (int min, int max) {
		srand(time(NULL));
		return (rand() % (max - min)) + min;
	}

	
/***
 * This function reduce the object buffer size
 */
	 
	void ReduceObjBuf(tsys *sys) {
		DebugPrint("reduceobjbuf");
		
		tobj *newo;		//(new o)bject buffer
		int c;			//(c)ounter
		// create a new buffer whit less objects
		newo = (tobj *) malloc (sizeof(tobj) * (sys->nalloc-OBJBUFSIZE));
		while (newo == NULL) {
			OPSML("ReduceObjBuf");
			newo = (tobj *) malloc (sizeof(tobj[sys->nalloc-OBJBUFSIZE]));
		}
		// update counter
		sys->nalloc -= OBJBUFSIZE;
		// copy what is stored in the old buffer in the new buffer
		for(c=0; c!= sys->nalloc; c++)
			newo[c] = sys->o[c];
		// delete the old buffer
		free(sys->o);
		// point sys->o at the new buffer
		sys->o = newo;
		// if can be reduced more, recall itself
		if(sys->nalloc - sys->nactive >= OBJBUFSIZE)
			ReduceObjBuf(sys);
		// if the buffer is empty, set the pointer to NULL
		if(sys->nalloc == 0)
			sys->o = NULL;
		//exit
		free(newo);
	}
	
/***
 * This function make the object buffer size bigger
 */
	void ExtendObjBuf(tsys *sys){
		DebugPrint("extendobjbuf");
		
		tobj *newo;		//(new o)bject buffer
		int c;			//(c)ounter
		
		// create a new buffer whit more objects
		newo = (tobj *) malloc (sizeof(tobj[sys->nalloc+OBJBUFSIZE]));
		while (newo == NULL) {
			OPSML("ExtendObjBuf");
			newo = (tobj *) malloc (sizeof(tobj[sys->nalloc+OBJBUFSIZE]));
		}
		// copy what is stored in the old buffer in the new buffer
		for (c=0; c != sys->nalloc; c++)
			newo[c] = sys->o[c];
		// update counter
		sys->nalloc += OBJBUFSIZE;
		// if the old buffer isn't empty, delete the old buffer
		if(sys->o != NULL)
			free(sys->o);
		// point sys->o at the new buffer
		sys->o = newo;
	}
	
	
/***
 * Save a system in the directory Systems/
 */
	void SaveSys(tsys *sys){
		DebugPrint("savesys");
		
		// the path where the system must be saved, an input variable and the destination file pointer
		char path[NAMELUN+13];
		char input[2];
		FILE *dest;
		// counter
		int i;
		
		// Write the path
		strcpy(path, SYSTEM_PATH);
		strcat(path, sys->name);
		strcat(path, ".sys");
		
		// control that the file isn't alredy existent
		dest = fopen(path, "r");
		if(dest != NULL) {
			fclose(dest);
			OPS("While saving: The system you want to save alredy exist.\nDo you want to delete the previous system and save this? [n = no | something else = y]", NULL);
			scanf("%s", input);
			if(strcmp(input, "n") == 0)
				return;
		}
	
		// Write the object
		dest = fopen (path, "w");
		// Write information about the system
		fprintf (dest, "%.128Lf\n%ld\n%.128Lf\n",  sys->precision, sys->nactive, sys->G);
		fprintf (dest, "%ld\n%d\n%d\n%d\n%d\n%d\n", sys->stime.year, sys->stime.day, sys->stime.hour, sys->stime.min, sys->stime.sec, sys->stime.millisec);	//the time
		// write the system's object's datas
		for(i=0; i!=sys->nactive; i++)
			WriteObjectComplete(dest, &sys->o[i]);
		fclose(dest);
	
		OPS("SYSTEM SAVED WHIT SUCCESS!\n\nPress something to continue", NULL);
		scanf("%s", input);		
	}
	
/***
 * OBJECT I/O       (READ/WRITE)
 * WriteObject write in the stream given the object.
 * WriteObjectComplete write in the stream given the object whit coordinates and velocity
 * ReadObject read in the stream given the object.
 * Read ObjectComplete read in the stream given the object whit coordinates and velocity
 */
	void WriteObject (FILE *stream, tobj *obj) {
		fprintf(stream, "%s\n%s\n%d\n%d\n%d\n%.128Lf\n%.128Lf", obj->name, obj->type->name, obj->color.red, obj->color.green, obj->color.blue, obj->radius, obj->mass);
	}
	void WriteObjectComplete (FILE *stream, tobj *obj) {
		fprintf(stream, "%s\n%s\n%d\n%d\n%d\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n%.128Lf\n", obj->name, obj->type->name, obj->color.red, obj->color.green,obj->color.blue, obj->radius, obj->mass, obj->x, obj->y, obj->z, obj->velx, obj->vely, obj->velz);
	}
	int ReadObject (FILE *stream, tobj *obj, tStype *Stype) {
		TNAME buffer;	// temporany buffer that store the name of the object and the name of the name of the type of the object
		// scan the name
		ScanFString(buffer, stream);
		obj->name = (char *) malloc (sizeof(char[strlen(buffer)]));
		while (obj->name == NULL) {
			OPSML("ReadObject");
			obj->name = (char *) malloc (sizeof(char[strlen(buffer)]));
		}
		strcpy(obj->name, buffer);
		// scan the type
		ScanFString(buffer, stream);
		obj->type = typeSearchName(Stype, buffer);
		// scan all the other things
		fscanf(stream, "%d\n%d\n%d\n%Lf\n%Lf", &obj->color.red, &obj->color.green, &obj->color.blue, &obj->radius, &obj->mass);
		if (obj->type == NULL)
			return CORRUPTED_SIG;
		return GOODSIGNAL;
	}
	int ReadObjectComplete (FILE *stream, tobj *obj, tStype *Stype) {
		TNAME buffer;
		// scan the name
		ScanFString(buffer, stream);
		obj->name = (char *) malloc (sizeof(char[strlen(buffer)]));
		while (obj->name == NULL) {
			OPSML("ReadObjectComplete");
			obj->name = (char *) malloc (sizeof(char[strlen(buffer)]));
		}
		strcpy(obj->name, buffer);
		// scan the type
		ScanFString(buffer, stream);
		obj->type = typeSearchName(Stype, buffer);
		// scan the other stuff
		fscanf(stream, "%d\n%d\n%d\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n", &obj->color.red, &obj->color.green, &obj->color.blue, &obj->radius, &obj->mass, &obj->x, &obj->y, &obj->z, &obj->velx, &obj->vely, &obj->velz);
		if (obj->type == NULL)
			return CORRUPTED_SIG;
		return GOODSIGNAL;
	}
	
/***
 * SaveConfig save in a file the config of tinf inf
 */
	void SaveConfig(){
		
		FILE *cf = fopen(CONFIGURATION_FILE, "w");
		
		// scan the vmode and debug
		fprintf(cf, "%d\n", inf.vmode);
		fprintf(cf, "%d\n", inf.debug);
		// scan OPS settings
		fprintf(cf, "%d\n", inf.ops.height);
		fprintf(cf, "%d\n", inf.ops.width);
		fprintf(cf, "%d\n", inf.ops.numprecision);
		// scan Window setting
		fprintf(cf, "%d\n", inf.gl.winh);
		fprintf(cf, "%d\n", inf.gl.winw);
		fprintf(cf, "%d\n", inf.gl.winx);
		fprintf(cf, "%d\n", inf.gl.winy);
		
		fclose(cf);
	}
	
/***
 * InitConfig is a function that load from the config file 
 */
	void InitConfig() {
		
		FILE *cf = fopen(CONFIGURATION_FILE, "r");
		// If there is a file
		if(cf != NULL) {
			// scan the vmode and debug
			fscanf(cf, "%d", &inf.vmode);
			fscanf(cf, "%d", &inf.debug);
			// scan OPS settings
			fscanf(cf, "%d", &inf.ops.height);
			fscanf(cf, "%d", &inf.ops.width);
			fscanf(cf, "%d", &inf.ops.numprecision);
			// scan Window setting
			fscanf(cf, "%d", &inf.gl.winh);
			fscanf(cf, "%d", &inf.gl.winw);
			fscanf(cf, "%d", &inf.gl.winx);
			fscanf(cf, "%d", &inf.gl.winy);
			fclose(cf);
		}
		// if not, load defaults
		else 
			SetDefaultConfig(inf);
	}
	
/***
 * This function reset the settings to the default values
 */
	void SetDefaultConfig(){
		
		inf.ops.height = DEFAULT_OPS_HEIGHT;
		inf.ops.width = DEFAULT_OPS_WIDTH;
		inf.debug = DEFAULT_DEBUG;
		inf.ops.numprecision = DEFAULT_OPS_NUMPRECISION;
		inf.vmode = DEFAULT_V_MODE;
		inf.gl.winh = DEFAULT_GL_WINH;
		inf.gl.winw = DEFAULT_GL_WINW;
		inf.gl.winx = DEFAULT_GL_WINX;
		inf.gl.winy = DEFAULT_GL_WINY;

		return;
	}
 
	
/***
 * This function create the directories Where objects and systems are saved
 * 
 * NOTE:
 * This function isn't portable! This implementation is for linux
 */
	BYTE InitDir() {
		// The state of the directories
		struct stat st = {0};
		// Check for the object directory and create it if not present
		if (stat(OBJECT_PATH, &st) == -1)
			mkdir(OBJECT_PATH, 0700);
		
		// Check for the system directory and create it if not present
		if (stat(SYSTEM_PATH, &st) == -1) 
			mkdir(SYSTEM_PATH, 0700);
		
		// Check that the directories has been created succefully
		if (stat(SYSTEM_PATH, &st) == -1)
			return FILE_ERR_SIG;
			
		if (stat(OBJECT_PATH, &st) == -1)
			return FILE_ERR_SIG;
		
		return GOODSIGNAL;
	}
	
	/***
	 * the function search object search a object in a system whit a name and return his pointer or NULL if there isn't any object whit that name
	 */
	tobj *SearchObject(tsys *sys, char *name) {
		int i;
		for (i=0; i != sys->nactive; i++)
			if(strcmp(sys->o[i].name, name) == 0)
				return &sys->o[i];
		return NULL;
	}