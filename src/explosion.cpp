#include "explosion.h"
#include "common.h"
#include <glib.h>

explosion *explosion_create(void) {
	return (explosion *) g_malloc(sizeof(explosion));
}
void explosion_init(explosion *ex) {
	animated_init((animated *)ex);
	ex->num_animations_made = 0;
	ex->index_image = 0;
}

void explosion_draw(explosion *ex, animation *explosions[]) {
	animation_draw((explosions[ex->index_image]), ((sprite *)ex)->x, ((sprite *)ex)->y, ((sprite *)ex)->direction);
	//Check if animation reached its end
	if (explosions[ex->index_image]->current_frame==0) {
		// Check number of time animation repeats
		ex->index_image ++;
		if (ex->index_image>=NUM_EXPLOSIONS) {
			ex->num_animations_made ++;
			ex->index_image = 0;
		}
	}
}
