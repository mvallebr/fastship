#ifndef __FASTSHIP_GUNFIRE_H__
#define  __FASTSHIP_GUNFIRE_H__

#include "animated.h"

extern "C" {
	typedef struct _gunfire {
		struct _animated animated;
		char gunfire_type[256]; //What type of enemy will the enemy appear
		int is_enemy; //Is this comming from a enemy?
	}gunfire;

	gunfire *gunfire_create(void);
	void gunfire_init (gunfire *g);
}

#endif // __FASTSHIP_GUNFIRE_H__
