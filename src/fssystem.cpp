#include "fssystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

extern "C" {
fssystem *singletonSystem =
		(fssystem *) g_malloc(sizeof(fssystem));

fssystem *get_singleton_fssystem(void) {
	return singletonSystem;
}

char *fssystem_get_app_dir(fssystem *sys) {
	return sys->app_dir;
}

void fssystem_init(fssystem *sys, int argc, char *argv[],
		int screen_width, int screen_height) {
	// start up the engine
	sys->key_shifts=0;
	sys->key_pressed=0;
	FSEventReceiver *receiver1 = new FSEventReceiver();
	sys->device = createDevice(video::EDT_SOFTWARE,
			core::dimension2d<s32>(screen_width, screen_height),
			32, false, false, false, receiver1);
			if (sys->device == NULL) {
				fprintf(stderr,"Error creating the device driver!\n");
		exit(-1);
	}

	sys->driver = sys->device->getVideoDriver();
	if (sys->driver == NULL) {
		fprintf(stderr, "Error creating the video device driver!\n");
		exit(-1);
	}
	//Load font
	sys->font = sys->device->getGUIEnvironment()->getBuiltInFont();
	
	//Set caption
	sys->device->setWindowCaption(L"Fast Ship");
	//Calculates app dir
	if (strncmp(argv[0], "/cygdrive/", strlen("/cygdrive/")-1)==0) {
		sys->app_dir[0]=argv[0][strlen("/cygdrive/")];
		sys->app_dir[1]=':';
		sys->app_dir[2]='\0';
		strcat(sys->app_dir, argv[0]+strlen("/cygdrive/")+1);
	} else {
		strcpy(sys->app_dir, argv[0]);
	}
	int numSlashesToIgnore=1;
	for (int i=strlen(sys->app_dir)-1; i>=0; i--) {
		if ((sys->app_dir[i]=='/') || (sys->app_dir[i]=='\\')) {
			sys->app_dir[i+1]='\0';
			numSlashesToIgnore--;
			if (numSlashesToIgnore<0)
			break;
		}
	}
	printf("app dir = '%s'\n", sys->app_dir);fflush(stdout);
}
void fssystem_destroy(fssystem *sys) {
	if (sys->device)
	sys->device->drop();
}
int fssystem_keypressed(fssystem *sys) {
	return sys->key_pressed;
}
void fssystem_write_text(fssystem *sys, char *message,
		int x, int y) {	
	wchar_t wcstring[1024];
	for(int i=0; i<1024; i++) wcstring[i]=L'\0';
	mbstowcs(wcstring, message, strlen(message));
	if (sys->font)
		sys->font->draw(wcstring, core::rect<s32>(x,y,x+300,y+50),
		video::SColor(255,255,255,255));
	else 
		printf("nogui - msg >>> '%s' \n", message);	
}

}
