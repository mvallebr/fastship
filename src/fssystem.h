#ifndef __FASTSHIP_SYSTEM_H__
#define  __FASTSHIP_SYSTEM_H__

#include <irrlicht.h>
using namespace irr;

extern "C" {
	enum keys {
		FS_KEY_X = KEY_KEY_X,
		FS_KEY_Z = KEY_KEY_Z,
		FS_KEY_UP = KEY_UP,
		FS_KEY_DOWN = KEY_DOWN,
		FS_KEY_LEFT = KEY_LEFT,
		FS_KEY_RIGHT = KEY_RIGHT,
		FS_KEY_ESC = KEY_ESCAPE
	};

	enum shifts {
		KB_SHIFT_FLAG=1
	};
	typedef struct _fssystem {
		IrrlichtDevice *device;
		video::IVideoDriver* driver;
		gui::IGUIFont* font;
		char key[1024];
		int key_shifts;
		int key_pressed;
		char app_dir[1024];
	}fssystem;

	fssystem *get_singleton_fssystem(void);
	void fssystem_init(fssystem *sys, int argc, char *argv[], int screen_width, int screen_height);
	void fssystem_destroy(fssystem *sys);
	int fssystem_keypressed(fssystem *sys);
	char *fssystem_get_app_dir(fssystem *sys);
	void fssystem_write_text(fssystem *sys, char *message,
			int x, int y);
}

class FSEventReceiver : public IEventReceiver {
public:
	FSEventReceiver() : IEventReceiver() {
		//resets the key buffer		
		for (int i=0; i<1024; i++)
		get_singleton_fssystem()->key[i]='\0';
	}
	virtual bool OnEvent(const SEvent& event) {		
		//printf("Event occured!\n"); fflush(stdout);
		if (/*node != 0 && */event.EventType == irr::EET_KEY_INPUT_EVENT) {
			//printf("\nState of key %d is %d\n", event.KeyInput.Key, event.KeyInput.PressedDown); fflush(stdout);
			//printf("\nESC key code is %d \n", FS_KEY_ESC); fflush(stdout);
			get_singleton_fssystem()->key[event.KeyInput.Key]=event.KeyInput.PressedDown;
			(event.KeyInput.PressedDown) ? get_singleton_fssystem()->key_pressed++ : get_singleton_fssystem()->key_pressed--;
			//printf("\nState of SHIFT key is %d\n\n", event.KeyInput.Shift); fflush(stdout);
			get_singleton_fssystem()->key_shifts = event.KeyInput.Shift;
			return true;
		}
		return false;
	}
};

#endif // __FASTSHIP_SYSTEM_H__
