#include <stdio.h>
#include <glib.h>
#include <string.h>

#include "gameloop.h"
#include "level.h"
#include "levitem.h"
#include "gunfire.h"
#include "explosion.h"
#include "fssystem.h"

gameloop *gameloop_create(void) {
	return (gameloop *)g_malloc(sizeof(gameloop));
}
void gameloop_init(gameloop *g) {
	g->message = NULL;
	g->flag_wait_screen=0;
	g->flag_message=0;
	g->bg_offset=0;
	g->getout=0;
	g->time_to_wait = 0;
	g->time_elapsed =0;
}
void gameloop_destroy(gameloop *g) {
}
int gameloop_nextitem(gameloop *g, levelitem *listitem) {
	switch (listitem->type) {
	case TYPE_WAITTIME:
		//rest(listitem->item->time_to_wait);
		g_timer_reset(g->waittimer);
		g->time_to_wait = (listitem->item->time_to_wait)
				* 1000;
		g->time_elapsed = 0;
		break;
	case TYPE_WAITSCREEN:
		g->flag_wait_screen = 1; //Set
		break;
	case TYPE_CHANGEBG:
		break;
	case TYPE_MESSAGE:
		g->message = listitem->item->text_to_show;
		fssystem_write_text(get_singleton_fssystem(),
				g->message, 50, 10);
		//textout(screen, font, g->message, 50, 10, -1);
		g->flag_message
				=NUM_SECONDS_MESSAGE_APPEARS*FRAMES_BY_SECOND;
		//clear_keybuf();
		break;
	case TYPE_CONSTRUCTION:
		g->lev->screen_constructions = g_list_prepend(
				g->lev->screen_constructions,
				&(listitem->item->construction));
		break;
	case TYPE_GUNCHANGE:
		g->lev->screen_bgunfire = g_list_prepend(
				g->lev->screen_bgunfire,
				&(listitem->item->bgunfire));
		break;
	case TYPE_BONUS:
		g->lev->screen_bonus = g_list_prepend(
				g->lev->screen_bonus,
				&(listitem->item->bonus));
		break;
	case TYPE_ENEMY:
		g->lev->screen_enemies = g_list_prepend(
				g->lev->screen_enemies,
				&(listitem->item->enemy));
		break;
	default:
		fprintf(stderr, "Oooopppssss.... Level with incorrect items...");
		return 0;
		break;
	}
	return 1;
}

int gameloop_receive_keys(gameloop *g) {
	fssystem * sys = get_singleton_fssystem();
	//Process player	
	g->lev->player1->side = PCENTER;
	if (get_singleton_fssystem()->key_shifts & KB_SHIFT_FLAG) {
		player_fire(g->lev->player1,
				g->lev->screen_enemies,
				g->lev->screen_constructions,
				&(g->lev->screen_fires)
		//TODO play this sound
		//, g->lev->smpfire );
		);
		//    key_shifts=0;
	}

	if (fssystem_keypressed(sys)) {
		if (sys->key[FS_KEY_ESC])
			g->getout = 1;

		if (sys->key[FS_KEY_UP])
			player_move_inside(g->lev->player1, 0, 0, 
			SCREEN_WIDTH, 
			SCREEN_HEIGHT, PCENTER, 0, -VELOCITY_MULTIPLIER
					*SIDE_VELOCITY);
		else if (sys->key[FS_KEY_DOWN])
			player_move_inside(g->lev->player1, 0, 0, 
			SCREEN_WIDTH, 
			SCREEN_HEIGHT, PCENTER, 0, 
			VELOCITY_MULTIPLIER*SIDE_VELOCITY);

		if (sys->key[FS_KEY_LEFT])
			player_move_inside(g->lev->player1, 0, 0, 
			SCREEN_WIDTH, 
			SCREEN_HEIGHT, PLEFT, -VELOCITY_MULTIPLIER
					*SIDE_VELOCITY, 0);
		//-VELOCITY_MULTIPLIER*(int)((g->lev->player1->velocity)),0);
		else if (sys->key[FS_KEY_RIGHT])
			player_move_inside(g->lev->player1, 0, 0, 
			SCREEN_WIDTH, 
			SCREEN_HEIGHT, PRIGHT, 
			VELOCITY_MULTIPLIER*SIDE_VELOCITY, 0);
		//VELOCITY_MULTIPLIER*(int)((g->lev->player1->velocity)),0);
		if (sys->key[FS_KEY_X]) {
			(g->lev->player1->velocity)+=STEP_VELOCITY;
			if ((g->lev->player1->velocity)>MAX_VELOCITY)
				g->lev->player1->velocity=MAX_VELOCITY;
		}
		if (sys->key[FS_KEY_Z]) {
			(g->lev->player1->velocity)-=STEP_VELOCITY;
			if ((g->lev->player1->velocity)<MIN_VELOCITY)
				g->lev->player1->velocity=MIN_VELOCITY;
		}
	}
	return 1;
}

void gameloop_process_constructions(gameloop *g) {
	GList *listtemp;
	listtemp = g_list_first(g->lev->screen_constructions);
	if (listtemp!=NULL)
		g->empty_screen=0;
	while (listtemp!=NULL) {
		sprite_move(((sprite *)(listtemp->data)), 0,
				(int)(VELOCITY_BG));
		sprite_draw(((sprite *)(listtemp->data)));
		if (!sprite_intersect_rect(
				(sprite *)(listtemp->data), 0, 0, 
				SCREEN_WIDTH, SCREEN_HEIGHT)) {//is outside screen
			g->lev->screen_constructions = g_list_remove(
					g->lev->screen_constructions,
					listtemp->data);
			listtemp=g->lev->screen_constructions;
			continue;
		}
		if (((construction *)(listtemp->data))->colide)
			if (sprite_intersect(
					(sprite *)(g->lev->player1),
					(sprite *)(listtemp->data))) {
				if (sprite_lose_energy(
						(sprite *)(g->lev->player1),
						((sprite *)(listtemp->data))->energy))
					if (level_player1_lose(g->lev)) {
						gameloop_add_explosion(g,
								(sprite *)(g->lev->player1));
						printf("You lost the game!");
						fssystem_write_text(
								get_singleton_fssystem(),
								"You lost the game", 50,
								100);
						g->getout=1; //Get out of the level, player loose
					}
				if (sprite_lose_energy(
						(sprite *)(listtemp->data),
						((sprite *)(g->lev->player1))->energy)) {
					//Add explosion on place
					gameloop_add_explosion(g,
							(sprite *)(listtemp->data));
					//Remove construction from list
					g->lev->screen_constructions
							= g_list_remove(
									g->lev->screen_constructions,
									listtemp->data);
					listtemp=g->lev->screen_constructions;
				}
			}
		if (listtemp!=NULL)
			listtemp = g_list_next(listtemp);
	}
}
void gameloop_process_bonus(gameloop *g) {
	GList *listtemp;
	listtemp = g_list_first(g->lev->screen_bonus);
	if (listtemp!=NULL)
		g->empty_screen=0;
	while (listtemp!=NULL) {
		gameloop_process_animated(
				(animated *)(listtemp->data),
				g->lev->player1,
				(sprite *)(g->lev->player1), 0, 0);
		sprite_draw(((sprite *)(listtemp->data)));
		if (!sprite_intersect_rect(
				(sprite *)(listtemp->data), 0, 0, 
				SCREEN_WIDTH, SCREEN_HEIGHT)) {//is outside screen
			g->lev->screen_bonus = g_list_remove(
					g->lev->screen_bonus, listtemp->data);
			listtemp=g->lev->screen_bonus;
			continue;
		}
		if (sprite_intersect((sprite *)(g->lev->player1),
				(sprite *)(listtemp->data))) {
			if (sprite_lose_energy(
					(sprite *)(listtemp->data),
					((sprite *)(g->lev->player1))->energy)) {
				if ( !strcmp(
						((bonus *)(listtemp->data))->bonus_type,
						"energy")) {
					((sprite *)(g->lev->player1))->energy
							+= 50;
				} else if ( !strcmp(
						((bonus *)(listtemp->data))->bonus_type,
						"energy2")) {
					((sprite *)(g->lev->player1))->energy
							+= 200;
				} else if ( !strcmp(
						((bonus *)(listtemp->data))->bonus_type,
						"life")) {
					(g->lev->player1)->lives += 1;
				} else if ( !strcmp(
						((bonus *)(listtemp->data))->bonus_type,
						"money")) {
					(g->lev->player1)->money += 500;
				} else if ( !strcmp(
						((bonus *)(listtemp->data))->bonus_type,
						"money2")) {
					(g->lev->player1)->money += 1000;
				} else {
					g_print(
							"Invalid bonus type: '%s'",
							((bonus *)(listtemp->data))->bonus_type);
				}
				g->lev->screen_bonus = g_list_remove(
						g->lev->screen_bonus,
						listtemp->data);
				listtemp=g->lev->screen_bonus;
			}
		}
		//g_print("enemy = %p\n", (listtemp->data));
		if (listtemp!=NULL)
			listtemp = g_list_next(listtemp);
	}
}
void gameloop_process_bgunfires(gameloop *g) {
	GList *listtemp;
	listtemp = g_list_first(g->lev->screen_bgunfire);
	if (listtemp!=NULL)
		g->empty_screen=0;
	while (listtemp!=NULL) {
		gameloop_process_animated(
				(animated *)(listtemp->data),
				g->lev->player1,
				(sprite *)(g->lev->player1), 1, 0);
		bgunfire_draw(((bgunfire *)(listtemp->data)));
		if (!sprite_intersect_rect(
				(sprite *)(listtemp->data), 0, 0, 
				SCREEN_WIDTH, SCREEN_HEIGHT)) {//is outside screen
			g->lev->screen_bgunfire
					= g_list_remove(
							g->lev->screen_bgunfire,
							listtemp->data);
			listtemp=g->lev->screen_bgunfire;
			continue;
		}
		if (sprite_intersect((sprite *)(g->lev->player1),
				(sprite *)(listtemp->data))) {
			if (sprite_lose_energy(
					(sprite *)(listtemp->data),
					((sprite *)(g->lev->player1))->energy)) {
				//strcpy(g->lev->player1->gunmodifier,  ((bgunfire *)(listtemp->data))->gunmodifier); 
				//strcpy(g->lev->player1->guntype, ((bgunfire *)(listtemp->data))->guntype);
				g->lev->player1->bgunfire
						= (bgunfire *)(listtemp->data);
				g->lev->screen_bgunfire = g_list_remove(
						g->lev->screen_bgunfire,
						listtemp->data);
				listtemp=g->lev->screen_bgunfire;
			}
		}
		//g_print("enemy = %p\n", (listtemp->data));
		if (listtemp!=NULL)
			listtemp = g_list_next(listtemp);
	}
}
void gameloop_process_enemies(gameloop *g) {
	GList *listtemp;
	listtemp = g_list_first(g->lev->screen_enemies);
	if (listtemp!=NULL)
		g->empty_screen=0;
	while (listtemp!=NULL) {
		gameloop_process_animated(
				(animated *)(listtemp->data),
				g->lev->player1,
				(sprite *)(g->lev->player1), 1, 0);
		//sprite_move(((sprite *)(listtemp->data)), 0, (int)((g->lev->player1->velocity)/MIN_VELOCITY));
		sprite_draw(((sprite *)(listtemp->data)));
		if (!sprite_intersect_rect(
				(sprite *)(listtemp->data), 0, 0, 
				SCREEN_WIDTH, SCREEN_HEIGHT)) {//is outside screen
			g->lev->screen_enemies = g_list_remove(
					g->lev->screen_enemies, listtemp->data);
			listtemp=g->lev->screen_enemies;
			continue;
		}
		if (sprite_intersect((sprite *)(g->lev->player1),
				(sprite *)(listtemp->data))) {
			if (sprite_lose_energy(
					(sprite *)(g->lev->player1),
					((sprite *)(listtemp->data))->energy))
				if (level_player1_lose(g->lev)) {
					gameloop_add_explosion(g,
							(sprite *)(g->lev->player1));
					printf("You lost the game!");
					fssystem_write_text(
							get_singleton_fssystem(),
							"You lost the game!", 50, 100);
					g->getout=1; //Get out of the level, player loose
				}
			if (sprite_lose_energy(
					(sprite *)(listtemp->data),
					((sprite *)(g->lev->player1))->energy)) {
				gameloop_add_explosion(g,
						(sprite *)(listtemp->data));
				g->lev->screen_enemies = g_list_remove(
						g->lev->screen_enemies,
						listtemp->data);
				listtemp=g->lev->screen_enemies;
			}
		}
		//g_print("enemy = %p\n", (listtemp->data));
		if (listtemp!=NULL)
			listtemp = g_list_next(listtemp);
	}
}
void gameloop_process_explosions(gameloop *g) {
	GList *listtemp;
	listtemp = g_list_first(g->lev->screen_explosions);
	while (listtemp!=NULL) {
		//    g_print("%p ", ((gunfire *)(listtemp->data)));    
		//    animated_process((animated *)(listtemp->data), g->lev->player1,(sprite *)(g->lev->player1), 1, 0);    
		explosion_draw(((explosion *)(listtemp->data)),
				g->lev->explosions);
		if ( (!sprite_intersect_rect(
				(sprite *)(listtemp->data), 0, 0, 
				SCREEN_WIDTH, SCREEN_HEIGHT)) //is outside screen
				//num animations reached
				|| (((explosion *)(listtemp->data))->num_animations_made
						>= NUM_EXPLOSION_ANIMS)) {
			g->lev->screen_explosions = g_list_remove(
					g->lev->screen_explosions,
					listtemp->data);
			listtemp=g->lev->screen_explosions;
			continue;
		}

		//g_print("enemy = %p\n", (listtemp->data));
		if (listtemp!=NULL)
			listtemp = g_list_next(listtemp);
	}
}

void gameloop_process_munitions(gameloop *g) {
	GList *listtemp, *listtemp2;
	int alredy_taken=0;
	listtemp = g_list_first(g->lev->screen_fires);
	while (listtemp!=NULL) {//Process fire motion
		//    g_print("%p ", ((gunfire *)(listtemp->data)));    
		alredy_taken=0;
		gameloop_process_animated(
				(animated *)(listtemp->data),
				g->lev->player1,
				(sprite *)(g->lev->player1), 1, 0);
		sprite_draw(((sprite *)(listtemp->data)));

		if (!sprite_intersect_rect(
				(sprite *)(listtemp->data), 0, 0, 
				SCREEN_WIDTH, SCREEN_HEIGHT)) {//is outside screen
			g->lev->screen_fires = g_list_remove(
					g->lev->screen_fires, listtemp->data);
			listtemp=g->lev->screen_fires;
			continue;
		}
		if (( (gunfire *)(listtemp->data))->is_enemy) {//Colision with player
			if (sprite_intersect(
					(sprite *)(g->lev->player1),
					(sprite *)(listtemp->data))) {
				if (sprite_lose_energy(
						(sprite *)(g->lev->player1),
						((sprite *)(listtemp->data))->energy))
					if (level_player1_lose(g->lev)) {
						gameloop_add_explosion(g,
								(sprite *)(g->lev->player1));
						printf("You lost the game!");
						fssystem_write_text(
								get_singleton_fssystem(),
								"You lost the game!", 50,
								100);
						g->getout=1; //Get out of the level, player loose
					}
				if (sprite_lose_energy(
						(sprite *)(listtemp->data),
						((sprite *)(g->lev->player1))->energy)) {
					g->lev->screen_fires = g_list_remove(
							g->lev->screen_fires,
							listtemp->data);
					listtemp=g->lev->screen_fires;
				}
			}
		} else { //colide with constuctions and enemies
			listtemp2
					= g_list_first(g->lev->screen_enemies);
			while (listtemp2!=NULL) {
				if (sprite_intersect_absrect(
						(sprite *)(listtemp2->data),
						((sprite *)(listtemp->data))->oldx,
						((sprite *)(listtemp->data))->oldy,
						((sprite *)(listtemp->data))->x,
						((sprite *)(listtemp->data))->y,
						animation_get_halfwidth(((sprite *)(listtemp->data))->anim),
						animation_get_halfheight(((sprite *)(listtemp->data))->anim)) ) {
					g->lev->player1->money
							+= ((sprite *)(listtemp->data))->energy;
					gameloop_add_explosion(g,
							(sprite *)(listtemp2->data));
					if (sprite_lose_energy(
							(sprite *)(listtemp2->data),
							((sprite *)(listtemp->data))->energy)) {
						//	    gameloop_add_explosion(g, (sprite *)(listtemp2->data));
						//listtemp3 = g_list_next(listtemp2);
						g->lev->screen_enemies
								= g_list_remove(
										g->lev->screen_enemies,
										listtemp2->data);
						listtemp2=g->lev->screen_enemies;
						//listtemp2=listtemp3;
						continue;
					}
					if (sprite_lose_energy(
							(sprite *)(listtemp->data),
							((sprite *)(listtemp2->data))->energy)) {
						g->lev->screen_fires
								= g_list_remove(
										g->lev->screen_fires,
										listtemp->data);
						listtemp=g->lev->screen_fires;
						alredy_taken=1;
						break;
					}
				}
				if (listtemp2!=NULL)
					listtemp2 = g_list_next(listtemp2);
			}

			if ((listtemp==NULL) || alredy_taken)
				continue;
			listtemp2
					= g_list_first(g->lev->screen_constructions);
			while (listtemp2!=NULL) {
				if (sprite_intersect_absrect(
						(sprite *)(listtemp2->data),
						((sprite *)(listtemp->data))->oldx,
						((sprite *)(listtemp->data))->oldy,
						((sprite *)(listtemp->data))->x,
						((sprite *)(listtemp->data))->y,
						animation_get_halfwidth(((sprite *)(listtemp->data))->anim),
						animation_get_halfheight(((sprite *)(listtemp->data))->anim))
						&& (((construction *)(listtemp2->data))->colide)) {
					g->lev->player1->money
							+= ((sprite *)(listtemp->data))->energy;
					gameloop_add_explosion(g,
							(sprite *)(listtemp2->data));
					if (sprite_lose_energy(
							(sprite *)(listtemp2->data),
							((sprite *)(listtemp->data))->energy)) {
						//listtemp3 = g_list_next(listtemp2);
						g->lev->screen_constructions
								= g_list_remove(
										g->lev->screen_constructions,
										listtemp2->data);
						listtemp2=g->lev->screen_enemies;
						//listtemp2=listtemp3;
						continue;
					}
					if (sprite_lose_energy(
							(sprite *)(listtemp->data),
							((sprite *)(listtemp2->data))->energy)) {
						g->lev->screen_fires
								= g_list_remove(
										g->lev->screen_fires,
										listtemp->data);
						listtemp=g->lev->screen_fires;
						break;
					}
				}
				if (listtemp2!=NULL)
					listtemp2 = g_list_next(listtemp2);
			}
		}

		//g_print("enemy = %p\n", (listtemp->data));
		if (listtemp!=NULL)
			listtemp = g_list_next(listtemp);
	}
}
void gameloop_endlevel(gameloop *g) {
	//End of the level
	if ((g->levellist)==NULL)
		fprintf(stdout, "Congratulations! You win!");
	else
		fprintf(stdout, "You loose... I said to you I am the best...");
}

int gameloop_begin_draw_screen(gameloop *g) {
	if (!get_singleton_fssystem()->device->run())
		return 0;
	get_singleton_fssystem()->driver->beginScene(false, false,
			video::SColor(255, 100, 101, 140));
	return 1;
}

void gameloop_draw_screen(gameloop *g) {
	//Show statistics
	sprintf(g->msgstat,
			"[Vel.:%d] [Lives:%d] [En.:%d] d[$:%d]",
			g->lev->player1->velocity,
			g->lev->player1->lives, ((sprite *)(g->lev->player1))->energy,
			g->lev->player1->money);
	fssystem_write_text(get_singleton_fssystem(),
			g->msgstat, 10, 10);
	//Now place on screen
	//vsync();
	//    draw_sprite(screen, g->lev->backbuffer->image, 0, 0);
	//blit(g->lev->backbuffer->image, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	get_singleton_fssystem()->driver->endScene();
}

int gameloop_run(gameloop *g) {
	gulong temp;
	levelitem *listitem;
	int i;
	int num_levels = 17;
	char
			levels[][100]= { "./levels/level1.fas",
					"./levels/level2.fas",
					"./levels/level3.fas",
					"./levels/level4.fas",
					"./levels/level5.fas",
					"./levels/level6.fas",
					"./levels/level7.fas",
					"./levels/level8.fas",
					"./levels/level9.fas",
					"./levels/level10.fas",
					"./levels/level11.fas",
					"./levels/level12.fas",
					"./levels/level13.fas",
					"./levels/level14.fas",
					"./levels/level15.fas",
					"./levels/level16.fas",
					"./levels/level17.fas" };
	//Create and load level
	g->lev = level_create();

	level_init(g->lev, levels[0]);

	for (i=1; i<num_levels; i++) {
		g->levellist = g_list_first(g->lev->items);
		//Init offset for background scrool
		g->bg_maxoffset
				= animation_get_height(g->lev->grounds[1]);
		//Init timers
		g->gametimer = g_timer_new();
		g_timer_start(g->gametimer);
		g->waittimer = g_timer_new();
		g_timer_start(g->waittimer);
		//Enter the game loop
		while (((g->levellist)!=NULL)
				&& (get_singleton_fssystem()->device->run())) {
			//Wait minimum time frame be reached
			while ((g->frametime<TIME_FRAME)
					&& (get_singleton_fssystem()->device->run())) {
				g_timer_elapsed(g->gametimer,
						&(g->frametime));
			}
			g->getout = g->getout
					|| (!gameloop_begin_draw_screen(g));
			//Reset counter, frame will begin
			g_timer_reset(g->gametimer);
			g->frametime=0;
			//If getout is seted, game finished...
			if (g->getout)
				break;
			//Read level itens until find a wait screen level item or a
			//   message level item
			temp = (gulong) g_timer_elapsed(g->waittimer,
					&(g->time_elapsed));
			g->time_elapsed = (1000000)*temp
					+ g->time_elapsed;
			if (g->time_elapsed>g->time_to_wait) {
				g->time_to_wait = 0;
				g->time_elapsed = 0;
			}
			//printf("%ld %ld\n", g->time_elapsed, g->time_to_wait);
			while (((((g->levellist)!=NULL)
					&& (!(g->flag_wait_screen))
					&& ((g->time_elapsed)
							>=(g->time_to_wait))))
					&& (get_singleton_fssystem()->device->run())) {
				// && (!(g->flag_message))) {
				listitem = (levelitem *)((g->levellist)->data);
				//        g_print("%p\n", &(listitem->item->enemy));
				if (!gameloop_nextitem(g, listitem)) { //Proccess this item
					return 0;
				}
				(g->levellist)
						= g_list_next((g->levellist));
			}

			g->empty_screen=1;
			gameloop_receive_keys(g);

			//Draw background on memory pixmap...
			animation_tile(g->lev->grounds[1], 0, 0, 
			SCREEN_WIDTH, SCREEN_HEIGHT, g->bg_offset);
			//Update offset for background scrool
			g->bg_offset
					=(g->bg_offset
							+ (int)(VELOCITY_BG)) % g->bg_maxoffset;
			//If flag_message is seted, a message should be showed
			if (g->flag_message) {
				fssystem_write_text(
						get_singleton_fssystem(),
						g->message, 250, 10);
				//textout(g->lev->backbuffer->image, font, g->message, 50, 10, -1);
				//rest(2000); //Show the message during some time...
				g->flag_message--;
			}

			//Process all sprites
			gameloop_process_constructions(g);
			gameloop_process_bonus(g);
			gameloop_process_bgunfires(g);
			gameloop_process_munitions(g);
			gameloop_process_enemies(g);

			//Draw player
			player_draw(g->lev->player1);
			gameloop_process_explosions(g);

			//If screen is empty and is waiting it, go to next item
			if (g->empty_screen)
				g->flag_wait_screen=0;

			gameloop_draw_screen(g);
		}
		if (i!=num_levels)
			level_unload_level(g->lev);
		if (!level_readlevelfile(g->lev, levels[i])) {
			printf("Couldn't read level file ´%s´!",
					levels[i]);
			return 0;
		}
	}
	if (!g->getout)
		fprintf(stdout, "You won all levels!!! Congratulations!!!");
	return 1;
}

void gameloop_add_explosion(gameloop *g, sprite *s) {
	//Add explosion from sprite
	explosion *a;
	a = explosion_create();
	explosion_init(a);
	//strncpy((char *)a, (char *)s, sizeof(sprite));
	((sprite *)a)->x = s->x;
	((sprite *)a)->y = s->y;
	((sprite *)a)->direction = s->direction;
	((sprite *)a)->anim = s->anim;
	/*  ((sprite *)a)->energy = s->energy;
	 ((sprite *)a)->oldx = s->oldx;
	 ((sprite *)a)->oldy = s->oldy;
	 ((sprite *)a)->initialx = s->initialx;
	 ((sprite *)a)->initialy = s->initialy;
	 ((sprite *)a)->screen_side = s->screen_side;
	 ((sprite *)a)->position = s->position;*/
	g->lev->screen_explosions = g_list_prepend(
			g->lev->screen_explosions, a);

	//TODO fix play sound
	//play_sample(g->lev->smpcolide, 255, 255, 1000, 0);
}

int gameloop_process_animated(animated *an, player *p,
		sprite *target, int setdir, int flip) {
	//Use actual velocity
	sprite_move(((sprite *)an), an->velocityx,
			an->velocityy);
	//-(int)(p->velocity /MIN_VELOCITY )+1);
	//Modify velocity according acceleration
	switch (an->acceleration) {
	case ACCEL_NONE:
		//Do nothing
		sprite_move(((sprite *)(an)), 0,
				(int)(VELOCITY_BG));
		if (setdir)
			sprite_set_angle_from_direction((sprite *)an,
					an->velocityx, an->velocityy
							+(int)((p->velocity)
									/MIN_VELOCITY), flip);
		break;
	case ACCEL_AX:
		sprite_move(((sprite *)(an)), 0,
				(int)((p->velocity)/MIN_VELOCITY));
		if (setdir)
			sprite_set_angle_from_direction((sprite *)an,
					an->velocityx, an->velocityy
							+(int)((p->velocity)
									/MIN_VELOCITY), flip);
		an->auxcount++;
		if ((an->auxcount % 10)==0)
			an->velocityx ++;
		break;
	case ACCEL_RX:
		sprite_move(((sprite *)(an)), 0,
				(int)((p->velocity)/MIN_VELOCITY));
		if (setdir)
			sprite_set_angle_from_direction((sprite *)an,
					an->velocityx, an->velocityy
							+(int)((p->velocity)
									/MIN_VELOCITY), flip);
		an->auxcount++;
		if ((an->auxcount % 10)==0)
			an->velocityx --;
		break;
	case ACCEL_AY:
		sprite_move(((sprite *)(an)), 0,
				(int)(VELOCITY_BG));
		if (setdir)
			sprite_set_angle_from_direction((sprite *)an,
					an->velocityx, an->velocityy
							+(int)(VELOCITY_BG), flip);
		an->auxcount++;
		if ((an->auxcount % 10)==0)
			an->velocityy --;
		break;
	case ACCEL_RY:
		sprite_move(((sprite *)(an)), 0,
				(int)(VELOCITY_BG));
		if (setdir)
			sprite_set_angle_from_direction((sprite *)an,
					an->velocityx, an->velocityy
							+(int)(VELOCITY_BG), flip);
		an->auxcount++;
		if ((an->auxcount % 3)==0)
			an->velocityy ++;
		break;
	case ACCEL_C:
		sprite_move(((sprite *)(an)), 0,
				(int)(VELOCITY_BG/2));
		if (setdir)
			sprite_set_angle_from_direction((sprite *)an,
					an->velocityx, an->velocityy
							+(int)(VELOCITY_BG/2), flip);
		an->auxcount++;
		if (an->auxcount < 50)
			break;
		if ((an->auxcount % 15)==0) {
			an->auxvx = an->velocityx;
			an->auxvy = an->velocityy;
			an->velocityx = an->auxvy;
			an->velocityy = -an->auxvx;
		}
		break;
	case ACCEL_LATERAL:
		sprite_move(((sprite *)(an)), 0,
				(int)(VELOCITY_BG));
		if (setdir)
			sprite_set_angle_from_direction((sprite *)an,
					an->velocityx, an->velocityy
							+(int)(VELOCITY_BG), flip);
		an->auxcount++;
		if (an->auxcount > 40) {
			if ((an->auxcount % 10)==0) {
				if (an->velocityx >0)
					an->velocityx--;
				an->velocityy--;
			}
		}
		break;
	case ACCEL_TELEG:
		sprite_move(((sprite *)(an)), 0,
				(int)(VELOCITY_BG/4));
		if (setdir)
			sprite_set_angle_from_direction((sprite *)an,
					an->velocityx, an->velocityy
							+(int)(VELOCITY_BG/4), flip);
		an->auxcount++;
		if (an->auxcount > 300)
			break;
		if ((an->auxcount % 20)==0) {
			an->auxvx = (an->velocityx <0) ? -an->velocityx
					: an->velocityx;
			an->auxvy = (an->velocityy <0) ? -an->velocityy
					: an->velocityy;
			an->velocityx = (target->x - ((sprite *)an)->x);
			an->velocityx = (an->velocityx <0) ? -an->auxvx
					: an->auxvx;
			an->velocityy = (target->y - ((sprite *)an)->y);
			an->velocityy = (an->velocityy <0) ? -an->auxvy
					: an->auxvy;
		}
		break;
	case ACCEL_BOTTOM:
		if (setdir)
			sprite_set_angle_from_direction((sprite *)an,
					an->velocityx, an->velocityy, flip);
		an->auxcount++;
		if (an->auxcount < 50) {
			an->auxvx = an->velocityx;
			an->auxvy = an->velocityy;
		}
		if ((an->auxcount > 50) && (an->auxcount < 100)) {
			if ((an->auxcount % 10)==0) {
				if (an->velocityx != 0)
					an->velocityx
							+= (an->velocityx >0) ? -1 : 1;
				if (an->velocityy != 0)
					an->velocityy
							+= (an->velocityy >0) ? -1 : 1;
			}
		}
		if (an->auxcount > 100) { 
			if (an->velocityx != an->auxvx)
				an->velocityx += (an->auxvx >0) ? 1 : -1;
			if (an->velocityy != an->auxvy)
				an->velocityy += (an->auxvy >0) ? 1 : -1;
		}
		break;
	case ACCEL_DIAGONAL:
		if (setdir)
			sprite_set_angle_from_direction((sprite *)an,
					an->velocityx, an->velocityy, flip);
		if (((sprite *)an)->screen_side & 1)
			break;
		if (((sprite *)an)->x < 0) {
			an->velocityx = -an->velocityx;
			((sprite *)an)->x = 0;
		} else if (((sprite *)an)->x > SCREEN_WIDTH-((pixmap *)an)->halfwidth) {
			an->velocityx = -an->velocityx;
			((sprite *)an)->x
					= SCREEN_WIDTH-((pixmap *)an)->halfwidth;
		}
		break;
	case ACCEL_DIAGONAL30:
		if (setdir)
			sprite_set_angle_from_direction((sprite *)an,
					an->velocityx, an->velocityy, flip);
		if (((sprite *)an)->screen_side & 1)
			break;
		/*{*/
		char str[1000];
		sprintf(str, "%d %d", ((sprite *)an)->x, ((sprite *)an)->initialx);
		/*textout(screen, font, str, 50, 70, -1); 
		 }*/
		fssystem_write_text(get_singleton_fssystem(), str,	250, 120);
		if (((sprite *)an)->x < ((sprite *)an)->initialx - (int)(3
				*SCREEN_WIDTH/10)) {
			an->velocityx = -an->velocityx;
			((sprite *)an)->x = ((sprite *)an)->initialx
					- (int)(3*SCREEN_WIDTH/10);
		} else if (((sprite *)an)->x > ((sprite *)an)->initialx + (int)(3
				*SCREEN_WIDTH/10)) {
			an->velocityx = -an->velocityx;
			((sprite *)an)->x = ((sprite *)an)->initialx
					+ (int)(3*SCREEN_WIDTH/10);
		}
		if (((sprite *)an)->x < 0) {
			an->velocityx = -an->velocityx;
			((sprite *)an)->x = 0;
		} else if (((sprite *)an)->x > SCREEN_WIDTH-((pixmap *)an)->halfwidth) {
			an->velocityx = -an->velocityx;
			((sprite *)an)->x
					= SCREEN_WIDTH-((pixmap *)an)->halfwidth;
		}
		break;
	default:
		//do nothing
		break;
	}
	return 1;
}

