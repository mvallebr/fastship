#ifndef __FASTSHIP_ANIMATION_H__
#define  __FASTSHIP_ANIMATION_H__

#include "pixmap.h"
#define MAX_ANIMATION_PIXMAPS 100

extern "C" {
	typedef struct _animation {
		struct _pixmap *pixmaps[MAX_ANIMATION_PIXMAPS];
		int current_frame;
		int size;
		int num_animations_made;
	}animation;

	animation *animation_create(void);
	void animation_init(animation *an);
	bool animation_loadfromfile(animation *an, char *dir, char *file);
	void animation_draw(animation *an, int x, int y, float angle);
	void animation_tile(animation *an, int x, int y, int right, int
			bottom, int offset);
	void animation_draw_frame(animation *an, int frame, int x, int y, float angle);
	void animation_tile_frame(animation *an, int frame, int x, int y, int right, int
			bottom, int offset);
	void animation_set_frame(animation *an, int frame);
	int animation_get_halfwidth(animation *an);
	int animation_get_halfheight(animation *an);
	int animation_get_width(animation *an);
	int animation_get_height(animation *an);
	void animation_advance_frames(animation *an, int num_frames);
}

#endif // __FASTSHIP_ANIMATION_H__
