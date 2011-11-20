#ifndef __FASTSHIP_EXPLOSION_H__
#define __FASTSHIP_EXPLOSION_H__

#include "sprite.h"
#include "player.h"
#include "animated.h"

extern "C" {
	typedef struct _explosion {
		struct _animated animated;
		int num_animations_made;
		int index_image;
	}explosion;

	explosion *explosion_create(void);
	void explosion_init(explosion *ex);
	void explosion_draw(explosion *ex, animation *explosions[]);
}

#endif // __FASTSHIP_EXPLOSION_H__
