#include<math.h>
#include<stdio.h>
#include<string.h>
#include<SDL.h>

#include"conio2.h"
#include"init_everything.h"
#include"variables.h"
#include"draw_functions.h"
#include"init_entities.h"

//#define SLOPE 10 //in PX

void init_player_data(Entity_t* player, SDL_sprites_t sprite) {
	player->pos_x = STARTING_POS_P_X;
	player->pos_y = STARTING_POS_P_Y;
	player->acc_y = ACCELERATION;
	player->ptr_to_sprite = sprite.plumber;
	player->anim_info.sprite_h = 16 * SPRITE_SCALE;	//16 = size of this sprite
	player->anim_info.sprite_w = 16 * SPRITE_SCALE; //16 = size of this sprite
	player->anim_info.sprite_scale = SPRITE_SCALE;
	player->anim_info.sprite_x = 0;
	player->anim_info.sprite_y = 0;
	player->anim_info.direction_matters = true;
}

void init_barrel_data(Entity_t* barrel, SDL_sprites_t sprite) {
	barrel->pos_x = BARREL_SPAWN_POINT_X;
	barrel->pos_y = BARREL_SPAWN_POINT_Y;
	barrel->vel_x = BARREL_SPEED;
	barrel->vel_y = NULL;
	barrel->acc_y = ACCELERATION;
	barrel->ptr_to_sprite = sprite.barrel;
	barrel->is_barrel = true;
	barrel->anim_info.sprite_h = 10 * SPRITE_SCALE;	//10 = size of this sprite
	barrel->anim_info.sprite_w = 12 * SPRITE_SCALE; //12 = size of this sprite
	barrel->anim_info.sprite_scale = SPRITE_SCALE;
	barrel->anim_info.sprite_x = 0;
	barrel->anim_info.sprite_y = 0;
	barrel->anim_info.direction_matters = false;
}

void init_platform_data(Object* platform, SDL_sprites_t* sprite, int first_plat_x, int first_plat_y, int place_in_array, int angle) {
	platform->ptr_to_sprite = sprite->platform_long;
	platform->height = 8 * SPRITE_SCALE;	//8 = size of this sprite
	platform->width = 48 * SPRITE_SCALE;	//48 = size of this sprite

	platform->pos_x = first_plat_x + place_in_array * platform->width;
	platform->pos_y = first_plat_y - place_in_array * SLOPE * angle;
}

void init_ladder_data(Object* ladder, SDL_sprites_t* sprites, int x, int y, int height) {
	ladder->ptr_to_sprite = sprites->ladder;
	ladder->height = height * SPRITE_SCALE;
	ladder->width = 8 * LADDER_WIDTHNESS * SPRITE_SCALE;	//8 = size of this sprite
	ladder->pos_x = x;
	ladder->pos_y = y;
}

void init_kong_data(Entity_t* kong, SDL_sprites_t sprite) {
	kong->pos_x = KONG_POS_X;
	kong->pos_y = KONG_POS_Y;
	kong->acc_y = NULL;
	kong->vel_x = NULL;
	kong->acc_y = ACCELERATION;
	kong->is_barrel = false;
	kong->ptr_to_sprite = sprite.kong;
	kong->anim_info.sprite_h = 32 * SPRITE_SCALE;   //32 = size of this sprite
	kong->anim_info.sprite_w = 42 * SPRITE_SCALE;	//42 = size of this sprite
	kong->anim_info.sprite_scale = SPRITE_SCALE;
	kong->anim_info.sprite_x = 0;
	kong->anim_info.sprite_y = 0;
	kong->anim_info.sprite_destination_x = KONG_POS_X;
	kong->anim_info.sprite_destination_y = KONG_POS_Y;
	kong->anim_info.direction_matters = false;
}

void init_purse_data(Object* purse, SDL_sprites_t sprites, int x, int y) {
	purse->ptr_to_sprite = sprites.purse;
	purse->height = 9 * SPRITE_SCALE;	//9 = size of this sprite
	purse->width = 9 * SPRITE_SCALE;	//9 = size of this sprite
	purse->pos_x = x;
	purse->pos_y = y;
}
