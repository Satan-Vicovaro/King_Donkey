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
#include"game.h"

void movement_y(Entity_t* entity, double delta);

void execute_movement(Entity_t* entity, double delta);

void handle_motion(SDL_pointers_t SDL_ptrs, world_info_t world_info, Entity_t* player, Entity_t* barrels, Collisions_all_t* all_results);