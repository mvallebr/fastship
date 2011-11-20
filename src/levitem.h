#ifndef __FASTSHIP_LEVELITEM_H__
#define  __FASTSHIP_LEVELITEM_H__

#include "levitem.h"
#include "enemy.h"
#include "construc.h"
#include "bonus.h"
#include "bgunfire.h"

extern "C" {
	enum {
		TYPE_ENEMY=0,
		TYPE_WAITTIME,
		TYPE_WAITSCREEN,
		TYPE_CHANGEBG,
		TYPE_MESSAGE,
		TYPE_CONSTRUCTION,
		TYPE_GUNCHANGE,
		TYPE_BONUS
	};

	typedef union _litem {
		struct _enemy enemy;
		struct _construction construction;
		struct _bonus bonus;
		struct _bgunfire bgunfire;
		int time_to_wait; //time to wait in miliseconds
		int backgroundid;
		char text_to_show[1024]; //Text to show before user key press
	}litem;

	typedef struct _levelitem {
		litem *item;
		int type; //Type of item
	}levelitem;

	levelitem* levelitem_create(void);
	void levelitem_destroy(levelitem *li);
	void levelitem_init(levelitem *li, int type);
}

#endif // __FASTSHIP_LEVELITEM_H__
