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

Entity_t* create_new_barrel(Entity_t* barrels, SDL_sprites_t SDL_sprites, int* number_of_barels) {
	(*number_of_barels)++;
	if (*number_of_barels >= 2) {
		barrels = (Entity_t*)realloc(barrels, sizeof(Entity_t) * (*number_of_barels));
	}
	else {
		barrels = (Entity_t*)malloc(sizeof(Entity_t) * (*number_of_barels));
	}
	if (barrels == NULL) {
		printf("PANIKA MALLOC NA BECZKI UMARL");
		exit;
	}
	else
		init_barrel_data(&barrels[*number_of_barels - 1], SDL_sprites);

	return barrels;
}

Entity_t* delete_barrel(Entity_t* barrels, int* number_of_barels) {
	for (int i = 0; i < *number_of_barels - 1; i++) {
		barrels[i] = barrels[i + 1];
	}
	(*number_of_barels)--;
	if (*number_of_barels > 0)
		barrels = (Entity_t*)realloc(barrels, sizeof(Entity_t) * (*number_of_barels));
	if (barrels == NULL) {
		printf("PANIKA MALLOC NA BECZKI UMARL");
		exit;
	}
	return barrels;
}

Entity_t* handle_barrels(Entity_t* barrels, int* animation_stage, int* count_throw_time, int* number_of_barels, SDL_sprites_t SDL_sprites) {
	
	if (*count_throw_time > 1000) {//1 second
		*count_throw_time = 0;
		(*animation_stage)++;
		if (*animation_stage == 3) {//3= 3 stage of animation (throwing a barrel)
			barrels = create_new_barrel(barrels, SDL_sprites, number_of_barels);
		}
		if (*animation_stage == 4) {
			*animation_stage = 0;
		}
	}
	if (*number_of_barels > MAX_NUMBER_OF_BARRELS) {
		barrels = delete_barrel(barrels, number_of_barels);
	}
	return barrels;
}

Entity_t* handle_kong(Entity_t kong, Entity_t* barrels, world_info_t world_info, SDL_pointers_t SDL_ptrs, SDL_sprites_t SDL_sprites) {
	static int count_throw_time = 0;
	static int number_of_barels = 0;
	static int animation_stage = 0;
	
	if (barrels == nullptr) {
		number_of_barels = 0;
	}
	
	count_throw_time += world_info.delta * 1000;

	barrels = handle_barrels(barrels, &animation_stage, &count_throw_time, &number_of_barels, SDL_sprites);

	kong.anim_info.movement_frame = animation_stage;
	animation(SDL_ptrs.screen, kong.ptr_to_sprite, kong.anim_info);

	if (barrels != nullptr)
		barrels->num_of_entities = number_of_barels;

	return barrels;
}