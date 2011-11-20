#ifndef __FASTSHIP_BGUNFIRE_H__
#define  __FASTSHIP_BGUNFIRE_H__

#include "animated.h"

extern "C" {
	typedef struct _bgunfire {
		struct _animated animated; //Parent
		struct _animation *pguntype;
		char gunmodifier[256]; //ID of the gun modifier
		char guntype[256]; //ID of the gun type
	}bgunfire;

	void bgunfire_init(bgunfire *bgf);
	void bgunfire_destroy(bgunfire *bgf);
	void bgunfire_draw(bgunfire *bgf);
}

#endif // __FASTSHIP_BGUNFIRE_H__
