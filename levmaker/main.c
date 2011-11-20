#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ENEMIES 20
#define MAX_CONSTRUCTIONS 4
#define MIN_ENEMIES 10
#define MIN_CONSTRUCTIONS 5
#define NUM_INVASIONS     40

//Define number of images on each category
#define NUM_GROUNDS 4
#define NUM_ENEMIES 35
#define NUM_CONSTRUCTIONS 13
#define NUM_BONUS 5
#define NUM_GUNS 7
#define NUM_MUNITIONS 10
char *img_enemies[NUM_ENEMIES]= { "bugz", "dragon01",
		"dragon02", "dragon03", "gdragon1", "gdragon2",
		"gunship1", "gunship2", "gunship3", "gunship4",
		"gunship5", "heavy", "little", "lspace01", "lwing",
		"planer1", "planer2", "planer3", "planer4",
		"planer5", "planer6", "planer7", "redcar01",
		"rocket", "space001", "stone1", "stone2", "stone3",
		"stone4", "stone5", "stone6", "stone7", "threefly",
		"truck1", "wing" };
char *img_constructions[NUM_CONSTRUCTIONS]= { "arabe",
		"badhouse", "future01", "future02", "marte01",
		"outpost1", "outside", "relic", "stone01",
		"stone02", "stones01", "tank01", "tank02" };
		
char *img_bonus[NUM_BONUS]= { "energy", "energy2", "life",
		"money", "money2"

};
char *img_grounds[NUM_GROUNDS]= { "desert", "grass",
		"stone", "space"

};
char *img_guns[NUM_GUNS]= { "mod0", "mod1", "mod2", "mod3",
		"mod4", "mod5", "mod6" };
char *img_munitions[NUM_MUNITIONS]= { "laser", "laser",
		"cannon", "bird", "coke", "fireball", "fire",
		"knife", "missil", "plasma" };

int main(int argc, char *argv[]) {
	FILE *f;
	int num_enemies=MIN_ENEMIES;
	int num_constructions=MIN_CONSTRUCTIONS;
	int num_invasions=NUM_INVASIONS;
	
	int curEnemy=0, curConstruction=0, curBonus=0, curObj=0;
	
	int i, j, k, l;
	int side, position, accel, energy, dirx,
			diry, colide;
	char *type, *idtiro, *idtiromod;

	if (argc<2) {
		printf(
				"Usage: %s levelfile.fas [num_invasions] [seed] \n",
				argv[0]);
		return 1;
	}
	if (argc>=3) {
		num_invasions = atoi(argv[2]);
		printf("number of invasions: %d \n", num_invasions);
	}
	if (argc>=4) {
		printf("Seed used: %d \n", atoi(argv[3]));
		srand(atoi(argv[3]));
	}

	f=fopen(argv[1], "r");
	if (f) {
		printf("File ´%s´ alredy exists!\n", argv[1]);
		fclose(f);
		return 1;
	}
	f=fopen(argv[1], "w");
	if (!f) {
		printf("Can´t open file ´%s´!\n", argv[1]);
		return 1;
	}
	//Generate the level
	fprintf(
			f,
			"0.1\n640\ngrass\nfire\n#\n4 start0 Use SHIFT to fire... \n1 3000\n4 start1 Level begin\n1 1000\n");
	for (i=0; i<num_invasions; i++) {
		//Generate constructions
		for (j=0; j<num_constructions; j++) {
			side = 0;
			position = j*80/num_constructions + (rand())%10;
			type = img_constructions[(rand())%12];
			energy = 1+(rand())%9;
			dirx = 0;//-5+(rand())%5;
			diry = -1;//+(rand())%5;
			colide = ((rand())%12<10) ? 0 : 1;
			fprintf(f, "5 construction%d %s %d %d %d %d %d %d \n", curConstruction++, type,
					side, position, dirx, diry, energy,
					colide);
		}

		//Generate enemies
		for (j=0; j<num_enemies; j++) {
			side = (rand())%4;
			position = 20 + (rand())%60;
			accel = (rand())%11;
			type = img_enemies[(rand())%34];
			energy = (rand())%10;
			idtiro = img_munitions[(rand())%10];
			idtiromod = img_guns[(rand())%7];
			dirx = 1+(rand())%5;
			diry = 1+(rand())%5;
			switch (side) {
			case 0:
				if (position>50)
					dirx = -dirx;
				break;
			case 1:
				if (position>50)
					diry = -diry;
				break;
			case 2:
				diry = -diry;
				if (position>50)
					dirx = -dirx;
				break;
			case 3:
				dirx = -dirx;
				if (position>50)
					diry = -diry;
				break;
			}
			fprintf(f,
					"0 enemy%d %s %d %d %d %d %d %d %d %d %s %s\n",
					curEnemy++, type, side, position, dirx, diry, dirx,
					diry, accel, energy, idtiro, idtiromod);
		}
		if ((rand()%3)==0) { //Gun change bonus 
			side = (rand())%4;
			position = 20 + (rand())%60;
			accel = (rand())%11;
			energy = (rand())%10;
			idtiro = img_munitions[(rand())%10];
			dirx = 1+(rand())%5;
			diry = 1+(rand())%5;
			switch (side) {
			case 0:
				if (position>50)
					dirx = -dirx;
				break;
			case 1:
				if (position>50)
					diry = -diry;
				break;
			case 2:
				diry = -diry;
				if (position>50)
					dirx = -dirx;
				break;
			case 3:
				dirx = -dirx;
				if (position>50)
					diry = -diry;
				break;
			}

			fprintf(f,
					"6 bonus%d %s %s %d %d %d %d %d %d %d %d \n", curBonus++,
					idtiro, "mod0", side, position, dirx, diry,
					dirx, diry, accel, energy);
		}
		if ((rand()%3)==0) { //Bonus from bonus list
			side = (rand())%4;
			position = 20 + (rand())%60;
			accel = (rand())%11;
			energy = (rand())%10;
			idtiro = img_munitions[(rand())%10];
			dirx = 1+(rand())%5;
			diry = 1+(rand())%5;
			switch (side) {
			case 0:
				if (position>50)
					dirx = -dirx;
				break;
			case 1:
				if (position>50)
					diry = -diry;
				break;
			case 2:
				diry = -diry;
				if (position>50)
					dirx = -dirx;
				break;
			case 3:
				dirx = -dirx;
				if (position>50)
					diry = -diry;
				break;
			}

			fprintf(f, "7 bonus%d %s %d %d %d %d %d %d %d %d \n", curBonus++, 
					img_bonus[rand()%5], side, position, dirx,
					diry, dirx, diry, accel, energy);
		}

		fprintf(f, "1 1000\n");
		//Generate constructions
		for (j=0; j<10; j++) {
			l = rand() % 3;
			for (k=0; k<l; k++) {
				if (!(rand()%2))
					continue;
				side = 0;
				position = k*80/l + (rand())%10;
				type = img_constructions[(rand())%10];
				energy = 1+(rand())%9;
				dirx = 0;//-5+(rand())%5;
				diry = -1;//+(rand())%5;
				colide = ((rand())%12<10) ? 0 : 1;
				fprintf(f, "5 construction%d %s %d %d %d %d %d %d \n", curConstruction++, 
						type, side, position, dirx, diry,
						energy, colide);
			}
			fprintf(f, "1 1000\n");
		}

		//Write "wait for empty screen"
		fprintf(f, "4 obj%d invasion %d\n", curObj++, i);
	}

	fprintf(
			f,
			"2 finish0\n4 finish1 Congratulations!\n1 2000\n4 finish2 You reached the end of the level\n1 3000\n");

	//Exit program
	fclose(f);
	return 0;
}

