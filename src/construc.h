#ifndef __FASTSHIP_CONSTRUCTION_H__
#define  __FASTSHIP_CONSTRUCTION_H__

#include "sprite.h"

extern "C" {
	typedef struct _construction {
		struct _sprite sprite;
		char construction_type[256]; //Type of construction
		int colide; //Indicate if the construction object can colide or not
	}construction;

	void construction_init(construction *co);
	void construction_destroy(construction *co);
}

#endif // __FASTSHIP_CONSTRUCTION_H__
