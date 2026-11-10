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


Object create_object_form_entity(Object* barrel_object, Entity_t* barrels) {
	barrel_object->ptr_to_sprite = barrels->ptr_to_sprite;

	barrel_object->pos_x = barrels->pos_x;
	barrel_object->pos_y = barrels->pos_y;
	barrel_object->height = barrels->anim_info.sprite_h;
	barrel_object->width = barrels->anim_info.sprite_w;

	barrel_object->number_of_objects = barrels->num_of_entities;

	return *barrel_object;
}

void create_platforms(Object* platforms, SDL_sprites_t* SDL_sprites,
					 int first_platform_x_y[][2], int num_of_platforms[], int angle_of_platforms[]) {

	int place_in_array = 0;
	for (int i = 0; i < FIRST_LVL_NUM_1ST_PLATFROMS; i++) {
		for (int j = 0; j < num_of_platforms[i]; j++) {
			init_platform_data(&platforms[place_in_array], SDL_sprites, first_platform_x_y[i][0], first_platform_x_y[i][1], j, angle_of_platforms[i]);
			platforms[i].number_of_objects = place_in_array;
			place_in_array++;
		}
	}
	platforms->number_of_objects = place_in_array;
}

void create_ladders(Object* ladders, SDL_sprites_t sprites, int ladder_info_x_y[][2], int* ladder_info_height) {
	int i = 0;
	for (i = 0; i < FIRST_LVL_NUM_OF_LADDERS; i++) {
		init_ladder_data(&ladders[i], &sprites, ladder_info_x_y[i][0], ladder_info_x_y[i][1], ladder_info_height[i]);
	}
	ladders->number_of_objects = i;
}

void create_purses(Object** purses, SDL_sprites_t SDL_sprites, static int purses_info_x_y[][2]) {
	int i = 0;
	*purses = (Object*)malloc(FIRST_LVL_NUM_OF_PURSES * sizeof(Object));
	if (*purses == NULL) {
		printf("panika malloc na torepki sie nie udal");
		exit;
	}
	else {
		for (i = 0; i < FIRST_LVL_NUM_OF_PURSES; i++) {
			init_purse_data(&purses[0][i], SDL_sprites, purses_info_x_y[i][0], purses_info_x_y[i][1]);
		}
		purses[0]->number_of_objects = i;
	}
}