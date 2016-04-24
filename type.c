/*
 * In this file there are functions that manage type
 * 
 */
 //Prototipes
 void ExtractType (int , char *);
 

/***
 * This function gave a number write in a variable the name
 * 
 */
	void ExtractType (int type, char *dest) {
	
		if (type <= 0)
			strcpy(dest, "Error Type");
		else if (type == 0)
			strcpy(dest, "Void");
		else if (type == 1)
			strcpy(dest, "Spaceship");
		else if (type == 2)
			strcpy(dest, "Sun");
		else if (type == 3)
			strcpy(dest, "Generic Planet");
		else if (type == 4)
			strcpy(dest, "Rock Planet");
		else if (type == 5)
			strcpy(dest, "Giant Gas Planet");
		else if (type == 6)
			strcpy(dest, "Natural Satellite");
		else if (type == 7)
			strcpy(dest, "Asteroid");
		else if (type == 8)
			strcpy(dest, "Comet");
		else if (type == 9)
			strcpy(dest, "Black Hole");
		else if (type == 10)
			strcpy(dest, "Space Station");
		else if (type == 11)
			strcpy(dest, "Unknow type");
		else if (type >= 11)
			strcpy(dest, "Error Type");
	
		return;
	}
