#include "sprite.h"
#include "common.h"
#include <glib.h>

int sprite_lose_energy(sprite *sp, int energy) {
	sp->energy -= energy;
	return ((sp->energy)<0) ? 1 : 0;
}
int sprite_intersect_rect(sprite *sp, int x, int y, int w, int h) {
	if ((sp->x)-(animation_get_halfwidth(sp->anim)) > x+w)
		return 0;
	if ((sp->y)-(animation_get_halfheight(sp->anim)) > y+h)
		return 0;
	if ((sp->x)+(animation_get_halfwidth(sp->anim)) < x)
		return 0;
	if ((sp->y)+(animation_get_halfheight(sp->anim)) < y)
		return 0;
	return 1;
}
int sprite_intersect_absrect(sprite *sp, int x1, int y1, int x2, int y2, int w,
		int h) {
	static int temp;
	if (x1>x2) {
		temp=x1;
		x1=x2;
		x2=temp;
	}
	if (y1>y2) {
		temp=y1;
		y1=y2;
		y2=temp;
	}
	if ((sp->x)-(animation_get_halfwidth(sp->anim)) > x2+ w)
		return 0;
	if ((sp->y)-(animation_get_halfheight(sp->anim)) > y2+ h)
		return 0;
	if ((sp->x)+(animation_get_halfwidth(sp->anim)) < x1 - w)
		return 0;
	if ((sp->y)+(animation_get_halfheight(sp->anim)) < y1 -h)
		return 0;
	return 1;
}
int sprite_intersect(sprite *sp, sprite *sp2) {
	if ((sp->x)-(animation_get_halfwidth(sp->anim)) > sp2->x + animation_get_halfwidth(sp2->anim))
		return 0;
	if ((sp->y)-(animation_get_halfheight(sp->anim)) > sp2->y + animation_get_halfheight(sp2->anim))
		return 0;
	if ((sp->x)+(animation_get_halfwidth(sp->anim)) < sp2->x - animation_get_halfwidth(sp2->anim))
		return 0;
	if ((sp->y)+(animation_get_halfheight(sp->anim)) < sp2->y - animation_get_halfheight(sp2->anim))
		return 0;
	return 1;
}

sprite *sprite_create(void) {
	return (sprite *) malloc(sizeof(sprite));
}
void sprite_init(sprite *sp) {
	sp->anim = NULL;
}
void sprite_draw(sprite *sp) {
	animation_draw(sp->anim, sp->x, sp->y, sp->direction);
	//  g_print("%d ", fixtoi(sp->direction));
}

void sprite_move(sprite *sp, int dx, int dy) {
	sp->oldx=sp->x;
	sp->oldy=sp->y;
	sp->x += dx;
	sp->y += dy;
}

void sprite_set_angle_from_direction(sprite *sp, int directionx,
		int directiony, int flip) {
	//TODO check the angles
	if (!flip) {
		if (directionx==0)
			sp->direction = 128; //itofix(128);
		else if (directiony==0) {
			if (directionx<0)
				sp->direction = -64; //itofix(-64);
			else
				sp->direction = 64; // itofix(64);
		} else {
			if (directionx<0)
				sp->direction = 64; //fadd(itofix(64), fatan(itofix(directiony/directionx)));
			else
				sp->direction = -64; //fadd(itofix(-64), fatan(itofix(directiony/directionx)));
		}
	} else {
		if (directionx==0)
			sp->direction = 0; //itofix(0);
		else if (directiony==0) {
			if (directionx<0)
				sp->direction = 64; //itofix(64);
			else
				sp->direction = -64; //itofix(-64);
		} else {
			if (directionx<0)
				sp->direction = -64; //TODO calculate the tangent 
					//fadd(itofix(-64), fatan(itofix(directiony/directionx)));
			else
				sp->direction = 64; //fadd(itofix(64), fatan(itofix(directiony/directionx)));
		}
	}
	//    sp->direction =  fatan(itofix(directiony/directionx));
	//sp->direction = itofix(32); //fasin(ftofix((directiony/directionx)%256));
	//g_print("%d ", fixtoi(sp->direction));
	//    g_print("%d %d - ", directionx, directiony);
}
int sprite_set_xy_from_pos_side(sprite *sp, int pos, int side) {
	if ((pos<0) || (pos>100)) {
		fprintf(stderr, "Error: invalid position!\n");
		return 0;
	}
	switch (side) {
	case SIDE_TOP:
		sp->x = (int)((pos*SCREEN_WIDTH)/100);
		sp->y = 0;//sp->pixmap->halfheight;
		break;
	case SIDE_LEFT:
		sp->x = 0;//	sp->pixmap->halfwidth;
		sp->y = (int)((pos*SCREEN_HEIGHT)/100);
		break;
	case SIDE_BOTTOM:
		sp->x = (int)((pos*SCREEN_WIDTH)/100);// - sp->pixmap->halfheight;
		sp->y = SCREEN_HEIGHT;
		break;
	case SIDE_RIGHT:
		sp->x = SCREEN_WIDTH;// - sp->pixmap->halfwidth;
		sp->y = (int)((pos*SCREEN_HEIGHT)/100);
		break;
	default:
		fprintf(stderr, "Error: invalid side!\n");
		return 0;
		break;
	}
	return 1;
}
