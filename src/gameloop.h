#ifndef __FASTSHIP_GAMELOOP_H__
#define __FASTSHIP_GAMELOOP_H__

#include "level.h"
#include <glib.h>
#include <SColor.h> 

extern "C" {
	typedef struct _gameloop {
		GList *levellist;
		level *lev;
		char *message;
		char msgstat[4096];
		int flag_wait_screen;
		int flag_message;
		int empty_screen; //Indicates if screen is empty
		int bg_offset;
		int bg_maxoffset;
		int getout; //User pressed esc
		gulong frametime;
		GTimer* gametimer; //To do the game run using same velocity on every computer
		gulong time_to_wait, time_elapsed;
		GTimer* waittimer; //To wait time_to_wait
	}gameloop;

	gameloop *gameloop_create(void);
	void gameloop_init(gameloop *g);
	int gameloop_run(gameloop *g);
	void gameloop_destroy(gameloop *g);
	int gameloop_nextitem(gameloop *g, levelitem *listitem);
	int gameloop_receive_keys(gameloop *g);
	void gameloop_process_constructions(gameloop *g);
	void gameloop_process_bonus(gameloop *g);
	void gameloop_process_bgunfires(gameloop *g);
	void gameloop_process_enemies(gameloop *g);
	void gameloop_process_explosions(gameloop *g);
	void gameloop_process_munitions(gameloop *g);
	void gameloop_endlevel(gameloop *g);
	void gameloop_draw_screen(gameloop *g);
	int gameloop_begin_draw_screen(gameloop *g);
	void gameloop_add_explosion(gameloop *g, sprite *s);
	int gameloop_process_animated(animated *an, player *p, sprite *target, int setdir,
			int flip);
}

#endif //__FASTSHIP_GAMELOOP_H__
