#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<SDL.h>

#include"conio2.h"
#include"init_everything.h"
#include"variables.h"
#include"draw_functions.h"
#include"init_entities.h"
#include"animation.h"
#include"collisions.h"
#include"create_obj.h"
#include"Handle_kong.h"
#include"game.h"

void movement_y(Entity_t* entity, double delta) {
	static int v1_y = 0;
	static int v2_y = 0;

	entity->vel_y += entity->acc_y * delta;

	entity->pos_y += entity->vel_y * delta;
}

void execute_movement(Entity_t* entity, double delta) {

	entity->pos_x += entity->vel_x * delta;

	movement_y(entity, delta);
}

void handle_motion(SDL_pointers_t SDL_ptrs, world_info_t world_info, Entity_t* player, Entity_t* barrels, Collisions_all_t* all_results) {
	static Anim_t anim_data;
	static double delta;
	static int tick = 0;
	static int tick_counter;
	static int animation_tick = 0;

	delta += world_info.delta * 1000; //delta from seconds to miliseconds

	if (delta / 10 >= 1) {
		animation_tick++;
		if (animation_tick >= ANIMATION_SPEED) {
			animation_tick = 0;
		}

		tick = floor(delta / 10);
		
		if (barrels != nullptr)
			for (int i = 0; i < barrels->num_of_entities; i++) {
				execute_collision_barrel(&barrels[i], all_results->ptr_result_barrel[i]);
				execute_movement(&barrels[i], tick);
				update_animation_data(&barrels[i], tick, all_results->ptr_result_barrel[i], animation_tick);
				upload_animation_data(&anim_data, &barrels[i]);
				animation(SDL_ptrs.screen, barrels->ptr_to_sprite, anim_data);
			}

		execute_collision_player(player, all_results);
		execute_movement(player, tick);
		update_animation_data(player, tick, all_results->result_player, animation_tick);
		upload_animation_data(&anim_data, player);
		animation(SDL_ptrs.screen, player->ptr_to_sprite, anim_data);
		
		delta = 0;
	}
	if (all_results->ptr_result_barrel != nullptr) {
		free(all_results->ptr_result_barrel);
	}


	if (barrels != nullptr)
		for (int i = 0; i < barrels->num_of_entities; i++) {
			upload_animation_data(&anim_data, &barrels[i]);
			animation(SDL_ptrs.screen, barrels->ptr_to_sprite, anim_data);
		}
	upload_animation_data(&anim_data, player);
	animation(SDL_ptrs.screen, player->ptr_to_sprite, anim_data);

}