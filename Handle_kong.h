#pragma once
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

Entity_t* delete_barrel(Entity_t* barrels, int* number_of_barels);

Entity_t* create_new_barrel(Entity_t* barrels, SDL_sprites_t SDL_sprites, int* number_of_barels);

Entity_t* handle_barrels(Entity_t* barrels, int* animation_stage, int* count_throw_time, int* number_of_barels, SDL_sprites_t SDL_sprites);

Entity_t* handle_kong(Entity_t kong, Entity_t* barrels, world_info_t world_info, SDL_pointers_t SDL_ptrs, SDL_sprites_t SDL_sprites);