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

Object create_object_form_entity(Object* barrel_object, Entity_t* barrels);

void create_platforms(Object* platforms, SDL_sprites_t* SDL_sprites,
	int first_platform_x_y[][2], int num_of_platforms[], int angle_of_platforms[]);

void create_ladders(Object* ladders, SDL_sprites_t sprites, int ladder_info_x_y[][2], int* ladder_info_height);

void create_purses(Object** purses, SDL_sprites_t SDL_sprites, static int purses_info_x_y[][2]);