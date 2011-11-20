#ifndef __FASTSHIP_ENEMY_H__
#define  __FASTSHIP_ENEMY_H__

#include "animated.h"
#include "player.h"

extern "C" {
	typedef struct _enemy {
		struct _animated animated;
		char enemy_type[256]; //What type of enemy will the enemy appear
		char gunmodifier[256]; //ID of the gun modifier
		char guntype[256]; //ID of the gun type
	}enemy;

	void enemy_init(enemy *en);
	void enemy_destroy(enemy *en);
	void enemy_fire(enemy *e, player *p, GList **fires);
}

#endif // __FASTSHIP_ENEMY_H__
