#include "gunfire.h"
#include <glib.h>

gunfire *gunfire_create(void) {
	return (gunfire *)g_malloc(sizeof(gunfire));
}

void gunfire_init(gunfire *g) {
	animated_init((animated *)g);
}
