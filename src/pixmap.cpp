#include "pixmap.h"
#include <glib.h>

static int instanceCount=0;
pixmap *pixmap_create(void) {
	return (pixmap *) g_malloc(sizeof(pixmap));
	instanceCount++;
}
void pixmap_alloc(pixmap *pm, int w, int h) {
	//pm->image = create_bitmap(w, h);
	char name[1024];
	sprintf(name, "texture%d", instanceCount);
	pm->image = get_singleton_fssystem()->driver->addTexture(core::dimension2d<s32>(w,h), name);
}

void pixmap_init(pixmap *pm) {
	pm->image = NULL;
	//pm->pal = NULL;
}

void pixmap_destroy(pixmap *pm) {
	if (pm->image!=NULL)
		pm->image->drop();
	g_free(pm);
}

int pixmap_loadfromfile(pixmap *pm, char *filename) {
	printf("  Loading pixmap from file '%s'\n", filename); fflush(stdout);
	//printf("p = %p\t", get_singleton_fssystem());fflush(stdout);
	//printf("p = %p\t", get_singleton_fssystem()->driver);fflush(stdout);
	//printf("p = %p\n", get_singleton_fssystem()->driver->getTexture("C:/pastas/marcelo/projetos/Prog/C/fastship/images/enemy/sydney.bmp"));fflush(stdout);
	fflush(stdout);
	pm->image = get_singleton_fssystem()->driver->getTexture(filename);
	printf("'%s' has color format %d\n", filename, pm->image->getColorFormat()); fflush(stdout);
	//IImage *img = get_singleton_fssystem()->driver->createImageFromFile(filename);
	//pm->image = get_singleton_fssystem()->driver->addTexture("texture"+instanceCount, img);

	//    g_print("%p %s\n", pm->image, filename);
	if (!(pm->image)) {
		fprintf(stderr, "Could't load image!!!\n"); fflush(stderr);
		exit(-1);
	}
	pm->width = pm->image->getSize().Width;
	pm->height = pm->image->getSize().Height;
	//    pm->halfwidth  = (int)((pm->width)/2);
	//    pm->halfheight = (int)((pm->height)/2);
	pm->halfwidth = (int)((pm->width)/2.7);
	pm->halfheight = (int)((pm->height)/2);
	return 1;
}

void pixmap_draw(pixmap *pm, int x, int y, float angle) {
	//TODO implement rotation
	//rotate_sprite(dest->image, pm->image, x- pm->halfwidth, y- pm->halfheight,	angle);
	//get_singleton_fssystem()->driver->draw2DImage(pm->image, core::position2d<s32>(x- pm->halfwidth, y- pm->halfheight));
	/*char str[1024];
	sprintf(str, "x=%d y=%d w=%d h=%d\n", x- pm->halfwidth, y- pm->halfheight, pm->image->getSize().Width, pm->image->getSize().Height);
	fssystem_write_text(get_singleton_fssystem(),
					str, 300, 300);*/ 
	
	get_singleton_fssystem()->driver->draw2DImage(
				pm->image, 
				//core::rect<s32>(core::position2d<s32>(x- pm->halfwidth, y- pm->halfheight),	pm->image->getSize()),				
				core::position2d<s32>(x- pm->halfwidth, y- pm->halfheight),
				core::rect<s32>(core::position2d<s32>(0, 0), 								pm->image->getSize()),
				0, video::SColor(255, 255, 255, 255), true
				);
	//  g_print("%d ", fixtoi(angle));
}

void pixmap_tile(pixmap *pm, int x, int y, int right, int
bottom, int offset) {
	int i, j;
	for (i=x; i<right; i+=pm->width) {
		for (j=y-(pm->height)+offset; j<bottom+(pm->height); j+=pm->height) {
			//draw_sprite(dest->image, pm->image, i, j);
			//get_singleton_fssystem()->driver->draw2DImage(pm->image, core::position2d<s32>(i, j));
			pixmap_draw(pm, i+pm->halfwidth, j+pm->halfheight, 0);
		}
	}
}

