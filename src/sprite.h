#ifndef __FASTSHIP_SPRITE_H__
#define  __FASTSHIP_SPRITE_H__

#include "animation.h"

extern "C" {
	typedef struct _sprite {
		float direction; //Angle of the direction
		int energy; //Amount of energy of the sprite
		int x, y; //Position of the center of the sprite
		int oldx, oldy;
		int initialx; //Initial x position
		int initialy; //Initial y position
		struct _animation *anim;

		int screen_side; //Side where the sprite will appear
		int position; //Position in % of the side. Where on the side will the sprite appear?
	}sprite;

	sprite *sprite_create(void);
	void sprite_init(sprite *sp);
	void sprite_draw(sprite *sp);
	void sprite_move(sprite *sp, int dx, int dy);
	void sprite_set_angle_from_direction(sprite *sp, int directionx, int directiony, int flip);
	int sprite_set_xy_from_pos_side(sprite *sp, int pos, int side);
	int sprite_intersect_rect(sprite *sp, int x, int y, int w, int h);
	int sprite_intersect(sprite *sp, sprite *sp2);
	int sprite_intersect_absrect(sprite *sp, int x1, int y1, int x2, int y2, int w, int h);
	int sprite_lose_energy(sprite *sp, int energy);
}

#endif // __FASTSHIP_SPRITE_H__
