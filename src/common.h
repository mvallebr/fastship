#ifndef __FASTSHIP_COMMON_H__
#define __FASTSHIP_COMMON_H__

//Preferences
#define PLAYER_INITIAL_ENERGY 30
#define PLAYER_INITIAL_LIVES  2

//Screen resolution
#define SCREEN_WIDTH  480
#define SCREEN_HEIGHT 640

// each second, background advances (1 000 000 / TIME_FRAME ) * VELOCITY_BG pixels
// Being delayMS the delay per miliseconds, yPos diff is calculated as follows
//   yDelta = delayMS * VELOCITY / (TIME_FRAME/1000)
//Player velocity, pixels per frame
#define MAX_VELOCITY 14
#define MIN_VELOCITY 14

#define BG_PLAYER_FACTOR 5
#define VELOCITY_BG ((int)(((MAX_VELOCITY+MIN_VELOCITY)/2)/BG_PLAYER_FACTOR))

#define STEP_VELOCITY 1
#define SIDE_VELOCITY 8
//Player velocity multiplier = velocity of the player sprite inside screen
#define VELOCITY_MULTIPLIER 1

//Number of explosion animations
#define NUM_EXPLOSION_ANIMS 2

//Minimum time to show each frame , in microseconds
#define TIME_FRAME 50000
#define FRAMES_BY_SECOND (1000000/TIME_FRAME)
#define NUM_SECONDS_MESSAGE_APPEARS 4

extern "C" {
	//Sides of screen
	enum {
		SIDE_TOP=0,
		SIDE_LEFT,
		SIDE_BOTTOM,
		SIDE_RIGHT
	};

	//Gun modifiers
	enum {
		GUNMOD_UNIDIR,
		GUNMOD_DISP4,
		GUNMOD_DISP8,
		GUNMOD_TRI,
		GUNMOD_TRI2,
		GUNMOD_TELEG,
		GUNMOD_TRI2TELEG,
	};

#define NUM_GROUNDS 4
#define NUM_EXPLOSIONS 1
#define NUM_PLAYER 3

	//#define IMG_DIR 				"../images/"
	//#define IMG_DIR 				"C:/md59956/workspaces/workspaceMvalle/fastship/images/"	
#define IMG_DIR 				"images/"
#define IMG_ENEMIES_DIR     	IMG_DIR"enemy/"
#define IMG_CONSTRUCTIONS_DIR   IMG_DIR"construction/"
#define IMG_EXPLOSIONS_DIR      IMG_DIR"explosion/"
#define IMG_BONUS_DIR           IMG_DIR"bonus/"
#define IMG_GROUNDS_DIR         IMG_DIR"grounds/"
#define IMG_GUNS_DIR            IMG_DIR"guns/"
#define IMG_MUNITIONS_DIR       IMG_DIR"munition/"
#define IMG_PLAYER_DIR          IMG_DIR"player/"
#define IMG_EXT 				".png"

	/*
	extern char *img_enemies[];
	extern char *img_constructions[];	
	extern char *img_bonus[];	
	extern char *img_guns[];
	extern char *img_munitions[];
	*/
	extern char *img_grounds[];
	extern char *img_explosions[];
	extern char *img_player[];
}

#endif // __FASTSHIP_COMMON_H__
