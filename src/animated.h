#ifndef __FASTSHIP_ANIMATED_H__
#define  __FASTSHIP_ANIMATED_H__

#include "sprite.h"

extern "C" {
	enum {
		ACCEL_NONE=0,
		ACCEL_AX,
		ACCEL_RX,
		ACCEL_AY,
		ACCEL_RY,
		ACCEL_C,
		ACCEL_LATERAL,
		ACCEL_TELEG,
		ACCEL_BOTTOM,
		ACCEL_DIAGONAL,
		ACCEL_DIAGONAL30,
	};

	typedef struct _animated {
		struct _sprite sprite; //Parent
		int velocityx; //Velocity on the x axis
		int velocityy; //Velocity on the y axis
		int acceleration;//Id of the acceleration
		//private
		int auxcount;
		int auxvx;
		int auxvy;
	}animated;

	animated *animated_create(void);
	void animated_init(animated *an);
}

#endif // __FASTSHIP_ANIMATED_H__
