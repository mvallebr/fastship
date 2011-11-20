#include "player.h"
#include "common.h"
#include "gunfire.h"

void player_fire(player *p, GList *enemies,
		GList *constructions, GList **fires/*, animation *gun_imgs[]*//*, SAMPLE *sample*/) {
	static int countf =0;
	gunfire *newfires[8]; //Maximum eith gunfires will be created
	int energy=1;
	countf = ++countf % (p->fire_period);
	if (countf!=0)
		return;
	else
		countf = 0;
	//TODO fix play sound    
	//play_sample(sample, 100, 150, 1000, 0);
	//printf("%d %d\n", p->gunmodifier, p->lives);
	//TODO fix gun type
	/*switch (p->guntype) {
	 default:
	 energy = 1;
	 break;
	 }*/
	//TODO fix gun mod
	/*switch (p->gunmodifier) {
	 case GUNMOD_UNIDIR:*/
	newfires[0] = gunfire_create();
	gunfire_init(newfires[0]);
	newfires[0]->is_enemy = 0;
	//strcpy(newfires[0]->gunfire_type, p->guntype);
	*fires = g_list_prepend(*fires, newfires[0]);
	//Set animated properties      
	((animated *)(newfires[0]))->velocityx = 0;
	((animated *)(newfires[0]))->velocityy = -5;// ((p->velocity/MIN_VELOCITY)+1);
	((animated *)(newfires[0]))->acceleration = ACCEL_AY;
	//Sets sprite properties
	((sprite *)(newfires[0]))->x = ((sprite *)p)->x;
	((sprite *)(newfires[0]))->y = ((sprite *)p)->y
			- animation_get_halfheight(((sprite *)p)->anim);
	((sprite *)(newfires[0]))->initialx = ((sprite *)(newfires[0]))->x;
	((sprite *)(newfires[0]))->initialy = ((sprite *)(newfires[0]))->y;
	((sprite *)(newfires[0]))->oldx = ((sprite *)(newfires[0]))->x;
	((sprite *)(newfires[0]))->oldy = ((sprite *)(newfires[0]))->y;
	sprite_set_angle_from_direction(
			(sprite *)(newfires[0]), 0, 1, 0);
	((sprite *)(newfires[0]))->energy = energy;

	((sprite *)(newfires[0]))->anim
			= p->bgunfire->pguntype;
	/*	break;
	 case GUNMOD_DISP4:
	 break;
	 case GUNMOD_DISP8:
	 break;
	 case GUNMOD_TRI:
	 break;
	 case GUNMOD_TRI2:
	 break;
	 case GUNMOD_TELEG:
	 break;
	 case GUNMOD_TRI2TELEG:
	 break;
	 default:
	 break;
	 }*/
}

player *player_create(void) {
	return (player *) g_malloc(sizeof(player));
}
void player_init(player *p) {
	sprite_init((sprite *) p);
	p->side = PCENTER;
	p->velocity = (MAX_VELOCITY+MIN_VELOCITY)/2;
	p->lives = PLAYER_INITIAL_LIVES;
	p->money = 0;
	//strcpy(p->gunmodifier, "");
	//strcpy(p->guntype, "fireball");
	p->bgunfire = NULL;
	((sprite *)p)->energy
			= PLAYER_INITIAL_ENERGY;
	((sprite *)p)->x = (int)(SCREEN_WIDTH/2);
	((sprite *)p)->y = (int)(8*SCREEN_HEIGHT
			/10);
	((sprite *)p)->initialx = ((sprite *)p)->x;
	((sprite *)p)->initialy = ((sprite *)p)->y;
	p->fire_period = 3;
}

//Move player within rectangle x,y,x+w,y+h
void player_move_inside(player *p, int x, int y, int w,
		int h, int side, int
		dx, int dy) {
	sprite_move(((sprite *)p), dx, dy);

	if ( (((sprite *)p)->x)
			- (animation_get_halfwidth(((sprite *)p)->anim) )<x)
		((sprite *)p)->x =x
				+ (animation_get_halfwidth(((sprite *)p)->anim));
	else if ( (((sprite *)p)->x)
			-(animation_get_halfwidth(((sprite *)p)->anim)) >= x+w
			- (animation_get_width(p->images[side])))
		((sprite *)p)->x =x+w
				- (animation_get_width(p->images[side]))
				+ (animation_get_halfwidth(((sprite *)p)->anim));

	if ( (((sprite *)p)->y)
			-(animation_get_halfheight(((sprite *)p)->anim))<y)
		((sprite *)p)->y =y
				+ (animation_get_halfheight(((sprite *)p)->anim));
	else if ( (((sprite *)p)->y)
			-(animation_get_halfheight(((sprite *)p)->anim)) > y+h
			- (animation_get_height(p->images[side])))
		((sprite *)p)->y =y+h
				- (animation_get_height(p->images[side]))
				+ (animation_get_halfheight(((sprite *)p)->anim));
	p->side = side;
}
void player_draw(player *p) {
	char str[1024];
	sprintf(str, "%d %d", ((sprite *)p)->x, ((sprite *)p)->y);
	fssystem_write_text(get_singleton_fssystem(), str, 170,			10);
	animation_draw(p->images[p->side], ((sprite *)p)->x, ((sprite *)p)->y, ((sprite *)p)->direction);
}
