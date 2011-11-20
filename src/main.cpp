#include <string.h>
#include "main.h"
#include "gameloop.h"
#include "common.h"
#include "fssystem.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

int main(int argc, char *argv[]) {
	gameloop *g;
	int w= SCREEN_WIDTH;
	int h= SCREEN_HEIGHT;

	// Init system
	fssystem *sys = get_singleton_fssystem();
	fssystem_init(sys, argc, argv, w, h);	
	//Run game loop
	g = gameloop_create();	
	gameloop_init(g);	
	gameloop_run(g);	
	gameloop_destroy(g);	

	//Destroy everything and quit
	fssystem_destroy(sys);

	return 0;
}

