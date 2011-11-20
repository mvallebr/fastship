#ifndef __FASTSHIP_BONUS_H__
#define  __FASTSHIP_BONUS_H__

#include "animated.h"

extern "C" {
	enum {
		BONUS_ENERGY1=0,
		BONUS_ENERGY2,
		BONUS_LIFE,
		BONUS_MONEY1,
		BONUS_MONEY2
	};

	typedef struct _bonus {
		struct _animated animated;
		char bonus_type[256]; //ID of the bonus type
	}bonus;

	void bonus_init(bonus *bo);
	void bonus_destroy(bonus *bo);
}
#endif // __FASTSHIP_BONUS_H__
