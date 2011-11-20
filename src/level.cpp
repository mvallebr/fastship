#include "level.h"
#include "player.h"
#include "common.h"
#include "pixmap.h"
#include "fssystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

level* level_create(void) {
	return (level *) malloc(sizeof(level));
}

int level_player1_lose(level *l) {
	((sprite *)(l->player1))->energy
			= PLAYER_INITIAL_ENERGY;
	//  allegro_message("player1 lose live!");
	//TODO fix play sound
	//play_sample(l->smplivelost, 255, 255, 1000, 0);
	(l->player1->lives)--;
	return (l->player1->lives)>0 ? 0 : 1;
}

int level_init(level *l, char *filename) {
	l->items = NULL;
	l->screen_enemies = NULL;
	l->screen_constructions = NULL;
	l->screen_bonus = NULL;
	l->screen_bgunfire = NULL;
	l->screen_fires =NULL;
	l->player1 = NULL;
	l->screen_explosions = NULL;
	//TODO fix play sound
	//l->bgmidi = load_midi("../sounds/bg.mid");
	//play_midi(l->bgmidi, 1);
	//l->smpfire=load_sample("../sounds/fire.wav");
	//l->smpcolide=load_sample("../sounds/colide.wav");
	//l->smplivelost=load_sample("../sounds/livelost.wav");

	if (!level_loadpixmaps(l)) {
		fprintf(stderr, "Error on loading image files!");
		return 0;
	}
	//Initialize player object
	if (!level_readplayer(l))
		return 0;
	char fullpath[1024];
	strcpy(fullpath, "");
	strcat(fullpath,
			fssystem_get_app_dir(get_singleton_fssystem()));
	strcat(fullpath, filename);
	if (!level_readlevelfile(l, fullpath)) {
		fprintf(stderr, "Couldn't read level file!");
		return 0;
	}
	//Initialize background
	//l->backbuffer = pixmap_create();
	//pixmap_init(l->backbuffer);
	//pixmap_alloc(l->backbuffer, SCREEN_WIDTH, SCREEN_HEIGHT);

	return 1;
}

int level_readplayer(level* l) {
	int i;
	l->player1 = player_create();
	if (!(l->player))
		return 0;
	player_init(l->player1);
	for (i=0; i<NUM_PLAYER; i++)
		l->player1->images[i] = l->player[i];
	((sprite *)(l->player1))->anim = l->player[0];
	return 1;
}

int level_loadpixmaps(level* l) {
	int i;
	char img_filename[2048];
	/*
	 for (i=0; i<NUM_ENEMIES; i++) {
	 l->enemies[i] = animation_create();
	 if (l->enemies[i]==NULL) {
	 fprintf(stderr, "Sorry, couldn't alloc memory for all images...");
	 return 0;
	 }
	 animation_init(l->enemies[i]);
	 strcpy(img_filename, "");
	 strcat(img_filename, fssystem_get_app_dir(get_singleton_fssystem()));
	 strcat(img_filename, IMG_ENEMIES_DIR);
	 if (!animation_loadfromfile(l->enemies[i], img_filename, img_enemies[i])) {
	 fprintf(stderr, "Error: Couldn't load all enemy images.\n");
	 return 0; //Fail
	 }
	 }
	 for (i=0; i<NUM_CONSTRUCTIONS; i++) {
	 l->constructions[i] = animation_create();
	 if (l->constructions[i]==NULL) {
	 fprintf(stderr, "Sorry, couldn't alloc memory for all images...");
	 return 0;
	 }
	 animation_init(l->constructions[i]);
	 strcpy(img_filename, "");
	 strcat(img_filename, fssystem_get_app_dir(get_singleton_fssystem()));
	 strcat(img_filename, IMG_CONSTRUCTIONS_DIR);		
	 if (!animation_loadfromfile(l->constructions[i], img_filename, img_constructions[i])) {
	 fprintf(stderr, "Error: Couldn't load all construction images.\n");
	 return 0; //Fail
	 }
	 }	 
	 for (i=0; i<NUM_BONUS; i++) {
	 l->bonus[i] = animation_create();
	 if (l->bonus[i]==NULL) {
	 fprintf(stderr, "Sorry, couldn't alloc memory for all images...");
	 return 0;
	 }
	 animation_init(l->bonus[i]);
	 strcpy(img_filename, "");
	 strcat(img_filename, fssystem_get_app_dir(get_singleton_fssystem()));
	 strcat(img_filename, IMG_BONUS_DIR);
	 //  	g_print("%d -> %s\n",i,img_filename);
	 if (!animation_loadfromfile(l->bonus[i], img_filename, img_bonus[i])) {
	 fprintf(stderr, "Error: Couldn't load all bonus images.\n");
	 return 0; //Fail
	 }
	 }
	 
	 for (i=0; i<NUM_GUNS; i++) {
	 l->guns[i] = animation_create();
	 if (l->guns[i]==NULL) {
	 fprintf(stderr, "Sorry, couldn't alloc memory for all images...");
	 return 0;
	 }
	 animation_init(l->guns[i]);
	 strcpy(img_filename, "");
	 strcat(img_filename, fssystem_get_app_dir(get_singleton_fssystem()));
	 strcat(img_filename, IMG_GUNS_DIR);
	 //  	g_print("%d -> %s\n",i,img_filename);
	 if (!animation_loadfromfile(l->guns[i], img_filename, img_guns[i])) {
	 fprintf(stderr, "Error: Couldn't load all guns images.\n");
	 return 0; //Fail
	 }
	 }

	 for (i=0; i<NUM_MUNITIONS; i++) {
	 l->munitions[i] = animation_create();
	 if (l->munitions[i]==NULL) {
	 fprintf(stderr, "Sorry, couldn't alloc memory for all images...");
	 return 0;
	 }
	 animation_init(l->munitions[i]);
	 strcpy(img_filename, "");
	 strcat(img_filename, fssystem_get_app_dir(get_singleton_fssystem()));
	 strcat(img_filename, IMG_MUNITIONS_DIR);
	 //  	g_print("%d -> %s\n",i,img_filename);
	 if (!animation_loadfromfile(l->munitions[i], img_filename, img_munitions[i])) {
	 fprintf(stderr, "Error: Couldn't load all enemy images.\n");
	 return 0; //Fail
	 }
	 }
	 */
	for (i=0; i<NUM_GROUNDS; i++) {
		l->grounds[i] = animation_create();
		if (l->grounds[i]==NULL) {
			fprintf(stderr, "Sorry, couldn't alloc memory for all images...");
			return 0;
		}
		animation_init(l->grounds[i]);
		strcpy(img_filename, "");
		strcat(
				img_filename,
				fssystem_get_app_dir(get_singleton_fssystem()));
		strcat(img_filename, IMG_GROUNDS_DIR);
		//  	g_print("%d -> %s\n",i,img_filename);
		if (!animation_loadfromfile(l->grounds[i],
				img_filename, img_grounds[i])) {
			fprintf(stderr, "Error: Couldn't load all ground images.\n");
			return 0; //Fail
		}
	}
	for (i=0; i<NUM_EXPLOSIONS; i++) {
		l->explosions[i] = animation_create();
		if (l->explosions[i]==NULL) {
			fprintf(stderr, "Sorry, couldn't alloc memory for all images...");
			return 0;
		}
		animation_init(l->explosions[i]);
		strcpy(img_filename, "");
		strcat(
				img_filename,
				fssystem_get_app_dir(get_singleton_fssystem()));
		strcat(img_filename, IMG_EXPLOSIONS_DIR);
		//  	g_print("%d -> %s\n",i,img_filename);
		if (!animation_loadfromfile(l->explosions[i],
				img_filename, img_explosions[i])) {
			fprintf(stderr, "Error: Couldn't load all explosion images.\n");
			return 0; //Fail
		}
	}
	for (i=0; i<NUM_PLAYER; i++) {
		l->player[i] = animation_create();
		if (l->player[i]==NULL) {
			fprintf(stderr, "Sorry, couldn't alloc memory for all images...");
			return 0;
		}
		animation_init(l->player[i]);
		strcpy(img_filename, "");
		strcat(
				img_filename,
				fssystem_get_app_dir(get_singleton_fssystem()));
		strcat(img_filename, IMG_PLAYER_DIR);
		//  	g_print("%d -> %s\n",i,img_filename);				
		if (!animation_loadfromfile(l->player[i],
				img_filename, img_player[i])) {
			fprintf(stderr, "Error: Couldn't load all enemy images.\n");
			return 0; //Fail
		}
	}

	return 1;
}

animation * level_load_animation(level* l, char *directory,
		char *animation_name) {
	animation * anim;
	char img_filename[1024];
	anim = animation_create();
	if (anim==NULL) {
		fprintf(stderr, "Sorry, couldn't alloc memory for all images...");
		return 0;
	}
	animation_init(anim);
	strcpy(img_filename, "");
	strcat(img_filename,
			fssystem_get_app_dir(get_singleton_fssystem()));
	strcat(img_filename, directory);
	if (!animation_loadfromfile(anim, img_filename,
			animation_name)) {
		fprintf(stderr, "Error: Couldn't load animation '%s' from '%s'\n", animation_name, directory);
		return NULL; //Fail
	}
	return anim;
}

int level_readlevelfile(level* l, char *filename) {
	FILE *f;
	char *buffer;
	//////////////////
	levelitem *li=NULL;
	int line;
	int major, minor;
	int temp;
	char type[256], idmod[256], idgun[256];
	int side, pos, directionx, directiony, velocityx,
			velocityy;
	int accel, energy, mstime, backgroundid, colide;
	char message[1024];
	int insertitem=1;
	char objName[1024];
	//////////////////
	f = fopen(filename, "rb");
	if (!f)
		return 0;

	fscanf(f, "%d.%d", &major, &minor);
	fscanf(f, "\n");
	fscanf(f, "%d", &(l->width));
	fscanf(f, "\n");
	fscanf(f, "%s", l->defaultGround);
	fscanf(f, "\n");
	fscanf(f, "%s", l->defaultGun);
	//    g_print("File version: %d.%d\n", major, minor);
	if ((major!=0) && (minor
	!=1)) {
		fprintf(stderr, "File version doesn't match!!\n");
		return 0;
	}
	line=1;
	buffer = (char *) g_malloc(2048 *sizeof(char));
	while (!feof(f)) {
		line++;
		fscanf(f, "\n");
		fgets(buffer, 2048, f); //Read the buffer from file
		if (feof(f))
			break; //End of file...
		buffer = g_strstrip(buffer);
		if (insertitem ==0)
			insertitem =1;
		else
			li = levelitem_create();
		//	g_print("%c\n", buffer[0]);
		switch (buffer[0]) {
		case '#': //Ignore, it is a comment
			insertitem =0;
			break;
		case '0': //Enemy
			sscanf(buffer,
					"%d %s %s %d %d %d %d %d %d %d %d %s %s",
					&temp, objName, type, &side, &pos, &directionx,
					&directiony, &velocityx, &velocityy,
					&accel, &energy, idgun, idmod);
			levelitem_init(li, TYPE_ENEMY);
			//Sets enemy properties
			strcpy(((enemy *)(li->item))->enemy_type, type);
			strcpy(((enemy *)(li->item))->guntype, idgun);
			strcpy(((enemy *)(li->item))->gunmodifier, idmod);

			//Sets animated properties
			((animated *)(li->item))->velocityx
					= velocityx;
			((animated *)(li->item))->velocityy
					= velocityy;
			((animated *)(li->item))->acceleration
					= accel;
			//Sets sprite properties
			if (!sprite_set_xy_from_pos_side(
					((sprite *)(li->item)), pos, side)) {
				fprintf(stderr, "Error on level file line %d!\n", line);
				return 0;
			}
			((sprite *)(li->item))->initialx = ((sprite *)(li->item))->x;
			((sprite *)(li->item))->initialy = ((sprite *)(li->item))->y;
			((sprite *)(li->item))->oldx = ((sprite *)(li->item))->x;
			((sprite *)(li->item))->oldy = ((sprite *)(li->item))->y;
			sprite_set_angle_from_direction(
					(sprite *)(li->item), directionx,
					directiony, 0);
			((sprite *)(li->item))->position = pos;
			((sprite *)(li->item))->screen_side = side;
			((sprite *)(li->item))->energy = energy;
			((sprite *)(li->item))->anim
					= level_load_animation(l, 
					IMG_ENEMIES_DIR,
							li->item->enemy.enemy_type);
			if (!((sprite *)(li->item))->anim) {
				fprintf(stderr, "Error: Couldn't load animation '%s' for enemy '%s'\n", li->item->enemy.enemy_type, type);
				return 0; //Fail
			}
			break;
		case '1': //Wait some time
			sscanf(buffer, "%d %d ", &temp, &mstime);
			levelitem_init(li, TYPE_WAITTIME);
			li->item->time_to_wait = mstime;
			break;
		case '2': //Wait for empty screen
			sscanf(buffer, "%d %s", &temp, objName);
			levelitem_init(li, TYPE_WAITSCREEN);
			break;
		case '3': //Change background
			sscanf(buffer, "%d %s %d ", &temp, objName, &backgroundid);
			levelitem_init(li, TYPE_CHANGEBG);
			li->item->backgroundid = backgroundid;
			break;
		case '4': //Pause and show a message
			sscanf(buffer, "%d %s %s", &temp, objName, message);
			g_strstrip(buffer);
			strcpy(message, buffer +2);
			levelitem_init(li, TYPE_MESSAGE);
			//	g_print("%s\n", message);
			strcpy(li->item->text_to_show, message);
			break;
		case '5': //Construction
			sscanf(buffer, "%d %s %s %d %d %d %d %d %d ",
					&temp, objName, type, &side, &pos, &directionx,
					&directiony, &energy, &colide);
			levelitem_init(li, TYPE_CONSTRUCTION);
			//Set construction properties
			((construction *)(li->item))->colide = colide;
			strcpy(((construction *)(li->item))->construction_type,
					type);
			//Sets sprite properties
			if (!sprite_set_xy_from_pos_side(
					((sprite *)(li->item)), pos, side)) {
				fprintf(stderr, "Error on level file line %d!\n", line);
				return 0;
			}
			((sprite *)(li->item))->initialx = ((sprite *)(li->item))->x;
			((sprite *)(li->item))->initialy = ((sprite *)(li->item))->y;
			sprite_set_angle_from_direction(
					(sprite *)(li->item), directionx,
					directiony, 1);
			((sprite *)(li->item))->position = pos;
			((sprite *)(li->item))->screen_side = side;
			((sprite *)(li->item))->energy = energy;

			((sprite *)(li->item))->anim
					= level_load_animation(
							l,
							IMG_CONSTRUCTIONS_DIR,
							li->item->construction.construction_type);
			if (!((sprite *)(li->item))->anim) {
				fprintf(stderr, "Error: Couldn't load animation '%s' for construction '%s'\n", li->item->construction.construction_type, type);
				return 0; //Fail
			}

			break;
		case '6': //Change gunfire
			sscanf(buffer,
					"%d %s %s %s %d %d %d %d %d %d %d %d ",
					&temp, objName, type, idmod, &side, &pos,
					&directionx, &directiony, &velocityx,
					&velocityy, &accel, &energy);

			levelitem_init(li, TYPE_GUNCHANGE);
			//Set gun fire properties
			strcpy(((bgunfire *)(li->item))->guntype, idgun);
			strcpy(((bgunfire *)(li->item))->gunmodifier, idmod);
			((bgunfire *)(li->item))->pguntype
					= level_load_animation(l, 
					IMG_MUNITIONS_DIR,
							li->item->bgunfire.guntype);
			if (!((bgunfire *)(li->item))->pguntype) {
				fprintf(stderr, "Error: Couldn't load animation '%s' for munition '%s'\n", li->item->bgunfire.guntype, type);
				return 0; //Fail
			}

			//Set animated properties
			((animated *)(li->item))->velocityx
					= velocityx;
			((animated *)(li->item))->velocityy
					= velocityy;
			((animated *)(li->item))->acceleration
					= accel;
			//Sets sprite properties
			if (!sprite_set_xy_from_pos_side(
					((sprite *)(li->item)), pos, side)) {
				fprintf(stderr, "Error on level file line %d!\n", line);
				return 0;
			}
			((sprite *)(li->item))->initialx = ((sprite *)(li->item))->x;
			((sprite *)(li->item))->initialy = ((sprite *)(li->item))->y;
			sprite_set_angle_from_direction(
					(sprite *)(li->item), directionx,
					directiony, 0);
			((sprite *)(li->item))->position = pos;
			((sprite *)(li->item))->screen_side = side;
			((sprite *)(li->item))->energy = energy;
			((sprite *)(li->item))->anim
					= level_load_animation(l, IMG_GUNS_DIR,
							li->item->bgunfire.gunmodifier);
			if (!((sprite *)(li->item))->anim) {
				fprintf(stderr, "Error: Couldn't load animation '%s' for gun '%s'\n", li->item->bgunfire.gunmodifier, type);
				return 0; //Fail
			}
			if ((l->player1->bgunfire==NULL) || (!strcmp(l->player1->bgunfire->guntype, l->defaultGun)))
				l->player1->bgunfire
						= (bgunfire *)(li->item);
			break;
		case '7': //Bonus
			sscanf(buffer,
					"%d %s %s %d %d %d %d %d %d %d %d ",
					&temp, objName, type, &side, &pos, &directionx,
					&directiony, &velocityx, &velocityy,
					&accel, &energy);
			levelitem_init(li, TYPE_BONUS);
			//Sets bonus properties
			strcpy(((bonus *)(li->item))->bonus_type, type);
			//Sets animated properties
			((animated *)(li->item))->velocityx
					= velocityx;
			((animated *)(li->item))->velocityy
					= velocityy;
			((animated *)(li->item))->acceleration
					= accel;
			//Sets sprite properties
			if (!sprite_set_xy_from_pos_side(
					((sprite *)(li->item)), pos, side)) {
				fprintf(stderr, "Error on level file line %d!\n", line);
				return 0;
			}
			((sprite *)(li->item))->initialx = ((sprite *)(li->item))->x;
			((sprite *)(li->item))->initialy = ((sprite *)(li->item))->y;
			sprite_set_angle_from_direction(
					(sprite *)(li->item), directionx,
					directiony, 0);
			((sprite *)(li->item))->position = pos;
			((sprite *)(li->item))->screen_side = side;
			((sprite *)(li->item))->energy = energy;
			((sprite *)(li->item))->anim
					= level_load_animation(l, 
					IMG_BONUS_DIR,
							li->item->bonus.bonus_type);

			break;
		default:
			fprintf(
			stderr,
			"levelfile: Sorry, but line %d is incorrect! Invalid char: %c\n",
			line, buffer[0]);
			break;
		}
		if (insertitem)
			l->items = g_list_append(l->items, li);
	}
	g_free(buffer);
	fclose(f);
	return 1;
}

int level_unload_level(level *l) {
	g_list_free(l->items);
	l->items = NULL;
	return 1;
}

