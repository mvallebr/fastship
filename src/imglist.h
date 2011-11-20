#ifndef __FASTSHIP_IMAGELIST_H__
#define  __FASTSHIP_IMAGELIST_H__

#include <glib.h>

extern "C" {
	typedef struct _imagelist {
		GList* pixmaps; //List of images
	}imagelist;
}

#endif // __FASTSHIP_LEVEL_H__
