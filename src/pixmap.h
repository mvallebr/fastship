#ifndef __FASTSHIP_PIXMAP_H__
#define __FASTSHIP_PIXMAP_H__

#include <irrlicht.h>
#include "fssystem.h"
using irr::video::ITexture;
using irr::video::IImage;

extern "C" {
	typedef struct _pixmap {
		ITexture* image;
		//RGB *pal;
		int width, height; //Width and height of the pixmap
		int halfwidth, halfheight; //Width/2 and height/2 of the pixmap
	}pixmap;

	pixmap *pixmap_create(void);
	void pixmap_alloc(pixmap *pm, int w, int h);
	void pixmap_init(pixmap *pm);
	void pixmap_destroy(pixmap *pm);
	int pixmap_loadfromfile(pixmap *pm, char *filename);
	void pixmap_draw(pixmap *pm, int x, int y, float angle);
	void pixmap_tile(pixmap *pm, int x, int y, int right, int
			bottom, int offset);

}
#endif  //__FASTSHIP_PIXMAP_H__
