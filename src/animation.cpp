#include "animation.h"
#include "common.h"
#include <dirent.h>
#include <glib.h>

animation *animation_create(void) {
	animation *anim =
			(animation *) g_malloc(sizeof(animation));
	anim->size = 0;
	anim->current_frame = 0;
	return anim;
}
void animation_init(animation *an) {
	an->size = 0;
	an->current_frame = 0;
	an->num_animations_made = 0;
}
gint compare_char(const void *a, const void *b) {
	if (a==NULL)
		return 0;
	if (b==NULL)
		return 0;
	return (gint) strcasecmp((char *)a, (char *)b);
}
bool animation_loadfromfile(animation *an, char *dir,
		char *file) {
	char fullpath[1024];
	strcpy(fullpath, dir);
	strcat(fullpath, file);
	GList *filelist = NULL;
	DIR *directory = opendir(fullpath);
	struct dirent *files;
	if (directory==NULL)
		return false;
	while (files=readdir(directory)) {
		char *temp = (char *) g_malloc(1024*sizeof(char));
		strcpy(temp, files->d_name);
		//if (files->d_type!=8) continue;        //it's not a file, skip
		if (strlen(temp)<5) {
			g_free(temp);
			continue; //No file extension, skip
		}
		//Incorrect extension, skip		
		if (strcasecmp((temp)
				+strlen(temp)-4, IMG_EXT)) {			
			printf(
					"\tfile '%s' has INcorrect extension - '%s'. NOT LOADING\n",
					temp, (temp)
							+strlen(temp)-4);
			fflush(stdout);
			g_free(temp);
			continue;
		} else {
			printf(
					"\tfile '%s' has correct extension - '%s'\n",
					temp, (temp)
							+strlen(temp)-4);
			fflush(stdout);
		}
		printf(" Loading file '%s' to animation '%s'\n",
				temp, file);
		fflush(stdout);
		filelist = g_list_insert_sorted(filelist, temp,
				compare_char);
	}
	GList *current = g_list_first(filelist);
	while ((current!=NULL) && (current->data!=NULL)) {
		printf(" Loading pixmap '%s' \n",
				(char *)current->data);
		an->pixmaps[an->size] = pixmap_create();
		pixmap_init(an->pixmaps[an->size]);
		strcpy(fullpath, dir);
		strcat(fullpath, file);
		strcat(fullpath, "/");
		strcat(fullpath, (char *)current->data);
		//strcat(fullpath, IMG_EXT);		
		if (!pixmap_loadfromfile(an->pixmaps[an->size],
				fullpath))
			return false;
		an->size++;
		g_free(current->data);
		current->data = NULL;
		current = current->next;
	}		
	g_list_free(filelist);			
	return true;
}

void animation_draw(animation *an, int x, int y, float angle) {
	animation_draw_frame(an, an->current_frame, x, y, angle);
	animation_advance_frames(an, 1);
}
void animation_draw_frame(animation *an, int frame, int x,
		int y, float angle) {
	if (an->size<=0)
		return;	
	pixmap_draw(an->pixmaps[an->current_frame], x, y, angle);
}
void animation_tile(animation *an, int x, int y, int right,
		int bottom, int offset) {
	animation_tile_frame(an, an->current_frame, x, y,
			right, bottom, offset);
	animation_advance_frames(an, 1);
}
void animation_tile_frame(animation *an, int frame, int x,
		int y, int right, int
		bottom, int offset) {
	if (an->size<=0)
		return;
	pixmap_tile(an->pixmaps[an->current_frame], x, y,
			right, bottom, offset);
}

void animation_set_frame(animation *an, int frame) {
	an->current_frame = frame;	
	if (an->size<=0)
		return;
	while (an->current_frame>=an->size) {
		an->num_animations_made++;
		an->current_frame-=an->size;
	}
}

int animation_get_halfwidth(animation *an) {
	if (an->size<=0)
		return 0;
	return an->pixmaps[an->current_frame]->halfwidth;
}
int animation_get_halfheight(animation *an) {
	if (an->size<=0)
		return 0;
	return an->pixmaps[an->current_frame]->halfheight;
}
int animation_get_width(animation *an) {
	if (an->size<=0)
		return 0;
	return an->pixmaps[an->current_frame]->width;
}
int animation_get_height(animation *an) {
	if (an->size<=0)
		return 0;
	return an->pixmaps[an->current_frame]->height;
}
void animation_advance_frames(animation *an, int num_frames) {	
	animation_set_frame(an, an->current_frame+num_frames);
}
