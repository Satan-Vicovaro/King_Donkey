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
#include"handle_motion.h"

void time_counter(world_info_t* world_info) {
	// w tym momencie t2-t1 to czas w milisekundach,
	// jaki uplyna³ od ostatniego narysowania ekranu
	// delta to ten sam czas w sekundach
	world_info->t2 = SDL_GetTicks();

	world_info->delta = (world_info->t2 - world_info->t1) * 0.001;
	world_info->t1 = world_info->t2;
	world_info->worldTime += world_info->delta;
}

void frames_counter(world_info_t* world_info) {
	world_info->fpsTimer += world_info->delta;
	if (world_info->fpsTimer > 0.5) {
		world_info->fps = world_info->frames * 2;
		world_info->frames = 0;
		world_info->fpsTimer -= 0.5;
	};
}

void reset_information(Object* purses) {
	if (purses != nullptr) {
		free(purses);
	}
}

void check_win(bool* win,int *quit, Collisions_all_t all_results) {
	if (all_results.res_player_kong.collision == true) {
		*quit = 1;
		*win = true;
	}
	if (all_results.res_player_barrel.collision == true) {
		*win = true;
	}
}

void handle_events(SDL_Event* event, int* quit, Entity_t* player, Object* ladders, Collisions_all_t all_results, bool* using_ladder,bool* win) {
	int key_pressed = false;
	while (SDL_PollEvent(event)) {
		switch (event->type) {
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym) {

			case SDLK_ESCAPE:
				*quit = 1;
				break;

			case SDLK_a:
				player->vel_x = -p_velocity;
				key_pressed = true;
				break;

			case SDLK_d:
				player->vel_x = +p_velocity;
				key_pressed = true;
				break;

			case SDLK_w:
				if (all_results.result_ladder.entity_in_object == true) {
					player->vel_y = -p_velocity;
					*using_ladder = true;
					all_results.result_player.ptr_to_using_ladder = using_ladder;
					key_pressed = true;
				}
				break;

			case SDLK_s:
				if (all_results.result_ladder.collision == true) {
					player->vel_y = p_velocity;
					*using_ladder = true;
					all_results.result_player.ptr_to_using_ladder = using_ladder;
					key_pressed = true;
				}
				break;
			case SDLK_SPACE:
				if (player->vel_y == 0 && all_results.result_player.collision == false) {
					player->vel_y = -JUMP_POWER;
					player->acc_y = ACCELERATION;
				}
				break;
			case SDLK_n:
				*win = true;
				break;
			}

			break;
		case SDL_KEYUP:
			if (key_pressed == false) {
				switch (event->key.keysym.sym) {
				case SDLK_a:
					if (player->vel_x == -p_velocity)
						player->vel_x = 0;
					break;
				case SDLK_d:
					if (player->vel_x == +p_velocity)
						player->vel_x = 0;
					break;
				case SDLK_w:
					if (player->vel_y == -p_velocity)
						player->vel_y = 0;
					break;

				case SDLK_s:
					if (player->vel_y == +p_velocity)
						player->vel_y = 0;
					break;

				default:
					break;
				}
			}
			break;
		case SDL_QUIT:
			*quit = 1;
			break;
		};
	};
}

void game(SDL_pointers_t SDL_ptrs, SDL_sprites_t SDL_sprites, Entity_t player, Entity_t* barrels, Entity_t kong,
		  Object* ladders, Object* platforms, Object** purses, world_info_t world_info, colours col_t, int *quit, bool win) {
	
	SDL_Event event;
	static bool using_ladder = false;

	world_info.t1 = SDL_GetTicks();
	while (!( win == true || *quit == 1)) {
		Collisions_all_t all_results;
		all_results.result_player.ptr_to_using_ladder = &using_ladder;

		time_counter(&world_info);
		frames_counter(&world_info);

		draw_static_surfaces(SDL_ptrs.screen, &col_t, platforms, ladders, *purses, world_info, SDL_sprites.charset);

		barrels = handle_kong(kong, barrels, world_info, SDL_ptrs, SDL_sprites);

		handle_collisions(&player, barrels, kong, ladders, platforms, &purses, &all_results);

		handle_events(&event, quit, &player, ladders, all_results, &using_ladder,&win);

		handle_motion(SDL_ptrs, world_info, &player, barrels, &all_results);

		draw_colission_info(SDL_ptrs.screen, all_results, SDL_sprites.charset);
		draw_points(SDL_ptrs.screen, &player, SDL_sprites.charset,world_info,win);

		world_info.frames++;
		generate_scr(&SDL_ptrs);

		check_win(&win,quit, all_results);
	}
}