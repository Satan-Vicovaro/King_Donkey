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

int main(int argc, char** argv) {
	int quit = 0;
	int key_pressed = false;
	bool using_ladder = false;
	bool win = false;
	
	SDL_pointers_t SDL_ptrs;
	SDL_sprites_t SDL_sprites;

	colours col_t; //colours_table
	world_info_t world_info;

	Entity_t player;
	Entity_t* barrels = nullptr;
	Entity_t kong;

	Object* purses = nullptr;
	Object ladders[FIRST_LVL_NUM_OF_LADDERS];
	Object platforms[FIRST_LVL_NUM_OF_PLATFORMS];


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}
	if (SDL_start(&SDL_ptrs, &SDL_sprites, &col_t) == 1)
		return 1;
	generate_scr(&SDL_ptrs);
	

	while (!quit) {
		init_player_data(&player, SDL_sprites);
		init_kong_data(&kong, SDL_sprites);	
		create_purses(&purses, SDL_sprites,purses_info_x_y);
		create_ladders(ladders, SDL_sprites, ladder_info_x_y, ladder_info_height);
		create_platforms(platforms, &SDL_sprites, first_platform_x_y, num_of_platforms, angle_of_platforms);

		game(SDL_ptrs, SDL_sprites, player, barrels, kong, ladders, platforms, &purses, world_info, col_t, &quit, win);
		reset_information(purses);
	}

	execute_close(SDL_ptrs);
	clear_sprites(SDL_sprites);
	return 0;
};