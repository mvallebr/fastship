#ifndef __FASTSHIP_PLAYER_H__
#define  __FASTSHIP_PLAYER_H__

#include "sprite.h"
#include "common.h"
#include "bgunfire.h"
#include <glib.h>

extern "C" {
	enum {
		PCENTER=0,
		PLEFT,
		PRIGHT
	};

	typedef struct _player {
		struct _sprite sprite;
		int lives; //Number of lives the  player have
		int velocity; //Vertical velocity of the player
		//char gunmodifier[256]; //gun modifier of the gun type
		//char guntype[256]; //type of gun used by the player
		struct _bgunfire *bgunfire;
		int money; //Amount of money the player alredy have
		int fire_period; //Period to fire. If 1, always fire. If 2, once fire, once not..
		//private
		int side; //Side to where player is going
		struct _animation *images[NUM_PLAYER];
	}player;

	player *player_create(void);
	void player_init(player *p);
	//Move inside rectangle x, y, w, h, with velocity, on direction direction
	void player_move_inside(player *p, int x, int y, int w, int h, int side, int
			dx, int dy);
	void player_draw(player *p);
	//TODO fix play sound
	void player_fire(player *p, GList *enemies, GList *constructions, GList **fires/*, animation *gun_imgs[]*//*, SAMPLE *sample*/);
}

#endif // __FASTSHIP_PLAYER_H__
