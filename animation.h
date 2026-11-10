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

void animation(SDL_Surface* screen, SDL_Surface* surface, Anim_t anim_data);

void update_animation_data(Entity_t* entity, int tick, Collision_result_t result_ladder, int animation_tick);

void upload_animation_data(Anim_t* anim_data, Entity_t* player);