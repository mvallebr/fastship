#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "levitem.h"
#include "enemy.h"
#include "bgunfire.h"
#include "bonus.h"
#include "construc.h"

levelitem* levelitem_create(void) {
	return (levelitem *) g_malloc(sizeof(levelitem));
}

void levelitem_init(levelitem *li, int type) {
	li->item = (litem *)g_malloc(sizeof(litem));
	li->type = type;
	switch (type) {
	case TYPE_WAITTIME:
	case TYPE_WAITSCREEN:
	case TYPE_CHANGEBG:
	case TYPE_MESSAGE:
		return;
		break;
	case TYPE_ENEMY:
		enemy_init((enemy *)(li->item));
		break;
	case TYPE_CONSTRUCTION:
		construction_init((construction *)(li->item));
		break;
	case TYPE_GUNCHANGE:
		bgunfire_init((bgunfire *)(li->item));
		break;
	case TYPE_BONUS:
		bonus_init((bonus *)(li->item));
		break;
	default:
		g_print("Error: Invalid inicialization of level item!\n");
		break;
	}
	animated_init((animated *)(li->item));

}

void levelitem_destroy(levelitem *li) {
	g_free(li->item);
	g_free(li);
}
