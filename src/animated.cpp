#include "animated.h"
#include "common.h"
#include <glib.h>

animated *animated_create(void) {
	return (animated *) g_malloc(sizeof(animated));
}
void animated_init(animated *an) {
	sprite_init((sprite *)an);
	an->auxcount=0;
	an->auxvx=0;
	an->auxvy=0;
}

