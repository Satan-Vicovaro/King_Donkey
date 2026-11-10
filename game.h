#pragma once
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

void time_counter(world_info_t* world_info);

void frames_counter(world_info_t* world_info);

void reset_information(Object* purses);

void check_win(bool* win,int *quit, Collisions_all_t all_results);

void handle_events(SDL_Event* event, int* quit, Entity_t* player, Object* ladders, Collisions_all_t all_results, bool* using_ladder,bool* win);


void game(SDL_pointers_t SDL_ptrs, SDL_sprites_t SDL_sprites, Entity_t player, Entity_t* barrels, Entity_t kong,
			Object* ladders, Object* platforms, Object** purses, world_info_t world_info, colours col_t, int *quit, bool win);