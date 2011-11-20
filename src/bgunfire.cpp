#include "bgunfire.h"

void bgunfire_init(bgunfire *bgf) {
	bgf->pguntype = (animation *)NULL;
}
void bgunfire_destroy(bgunfire *bgf) {
}
void bgunfire_draw(bgunfire *bgf) {
	sprite_draw((sprite *)bgf);
	animation_draw(bgf->pguntype, ((sprite *)bgf)->x, ((sprite *)bgf)->y, ((sprite *)bgf)->direction);
}

