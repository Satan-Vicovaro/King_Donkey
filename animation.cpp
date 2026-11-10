#include<math.h>
#include<stdio.h>
#include<string.h>
#include<SDL.h>

#include"conio2.h"
#include"init_everything.h"
#include"variables.h"
#include"draw_functions.h"
#include"init_entities.h"

void animation(SDL_Surface* screen, SDL_Surface* surface, Anim_t anim_data) {
	SDL_Rect animation_source, animation_destinaton;
	int stage_of_movement = anim_data.movement_frame;

	animation_source.x = 0 + anim_data.sprite_w * stage_of_movement / SPRITE_SCALE;
	if (anim_data.direction_matters == true) {
		if (anim_data.direction == RIGHT)
			animation_source.y = 0;
		else if (anim_data.direction == LEFT) {
			animation_source.y = anim_data.sprite_h / SPRITE_SCALE;
		}
		else if (anim_data.direction == USING_LADDER)
			animation_source.y = 2 * anim_data.sprite_h / SPRITE_SCALE;
		else {
			animation_source.y = 0;
		}
	}
	else animation_source.y = 0;

	animation_source.h = anim_data.sprite_h / SPRITE_SCALE;
	animation_source.w = anim_data.sprite_w / SPRITE_SCALE;

	animation_destinaton.x = anim_data.sprite_destination_x;
	animation_destinaton.y = anim_data.sprite_destination_y;
	animation_destinaton.h = anim_data.sprite_h;
	animation_destinaton.w = anim_data.sprite_w;

	SDL_BlitScaled(surface, &animation_source, screen, &animation_destinaton);

	gotoxy(1, 6);
	printf("stage_of_movement: %d", stage_of_movement);
}

void update_animation_data(Entity_t* entity, int tick, Collision_result_t result_ladder,int animation_tick) {

	if (entity->vel_x != 0 || entity->vel_y != 0) {
		animation_tick += tick;
		if (animation_tick >= ANIMATION_SPEED) {
			entity->anim_info.movement_frame++;
			if (entity->anim_info.movement_frame == 3) {
				entity->anim_info.movement_frame = 0;
			}

			if (entity->vel_x != 0) {
				if (entity->vel_x > 0) {
					entity->anim_info.direction = LEFT;
				}
				else if (entity->vel_x < 0)
					entity->anim_info.direction = RIGHT;
				if (entity->acc_y == 1) {
					entity->anim_info.movement_frame = 1;
				}
			}

			if (entity->is_barrel == false) {
				if (*result_ladder.ptr_to_using_ladder == true) {
					entity->anim_info.direction = USING_LADDER;
				}
			}
		}

	}
}

void upload_animation_data(Anim_t* anim_data, Entity_t* player) {
	anim_data->sprite_x = 0;
	anim_data->sprite_y = 0;

	anim_data->sprite_h = player->anim_info.sprite_h;
	anim_data->sprite_w = player->anim_info.sprite_w;

	anim_data->direction_matters = player->anim_info.direction_matters;
	anim_data->direction = player->anim_info.direction;

	anim_data->sprite_destination_x = player->pos_x;
	anim_data->sprite_destination_y = player->pos_y;

	//anim_data->sprite_scale = player->anim_info.sprite_scale;
	anim_data->movement_frame = player->anim_info.movement_frame;
}