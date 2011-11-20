#ifndef __FASTSHIP_LEVEL_H__
#define __FASTSHIP_LEVEL_H__

#include <glib.h>
#include "common.h"
#include "animation.h"
#include "levitem.h"
#include "player.h"

extern "C" {
	typedef struct _level {
		//struct _animation *backbuffer;
		/*
		struct _animation *enemies[NUM_ENEMIES];
		struct _animation *constructions[NUM_CONSTRUCTIONS];		
		struct _animation *bonus[NUM_BONUS];		
		struct _animation *guns[NUM_GUNS];
		struct _animation *munitions[NUM_MUNITIONS];
		*/
		int width;
		char defaultGround[1024], defaultGun[1024];
		struct _animation *grounds[NUM_GROUNDS];
		struct _animation *explosions[NUM_EXPLOSIONS];
		struct _animation *player[NUM_PLAYER];
		GList *items; //List of level items
		GList *screen_enemies; //List of enemies current on the screen
		GList *screen_constructions; //List of constructions current on the screen
		GList *screen_bonus; //List of bonus current on the screen
		GList *screen_bgunfire; //List of change gun bonus current on the screen
		GList *screen_fires; //List of gunfires on screen
		GList *screen_explosions; //List of explosions on screen
		struct _player *player1;
		//TODO fix play sound
		//SAMPLE *smpfire, *smpcolide, *smplivelost;
		//MIDI   *bgmidi;
	}level;

	level* level_create(void);
	int level_init(level *l, char *filename);
	int level_readlevelfile(level* l, char *filename);
	int level_unload_level(level *l);
	int level_loadpixmaps(level* l);
	int level_readplayer(level* l);
	int level_player1_lose(level *l);
}

#endif // __FASTSHIP_LEVEL_H__
