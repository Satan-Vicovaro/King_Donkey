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

void execute_collision_barrel(Entity_t* barrel, Collision_result_t result_barrel) {
	if (result_barrel.collision == true) {
		if (result_barrel.shift_x != 0) {
			barrel->pos_x += result_barrel.shift_x;
			result_barrel.shift_x = 0;
			barrel->vel_x = -barrel->vel_x;

		}
		if (result_barrel.shift_y != 0) {
			barrel->pos_y += result_barrel.shift_y;
			result_barrel.shift_y = 0;
			barrel->vel_y = barrel->vel_y / 4;
		}
		barrel->acc_y = result_barrel.change_acc_y_to;
	}
	barrel->acc_y = result_barrel.change_acc_y_to;
}

void execute_collision_player(Entity_t* player, Collisions_all_t* all_results) {

	printf("korzysta z drabiny? %d ", *all_results->result_player.ptr_to_using_ladder);
	if (all_results->result_player.collision == true && *all_results->result_player.ptr_to_using_ladder == false) {
		if (all_results->result_player.shift_x != 0) {
			player->pos_x += all_results->result_player.shift_x;
			all_results->result_player.shift_x = 0;

		}
		if (all_results->result_player.shift_y != 0) {
			player->pos_y += all_results->result_player.shift_y;
			all_results->result_player.shift_y = 0;
			player->vel_y = 0;
		}
	}
	player->acc_y = all_results->result_player.change_acc_y_to;
}

void map_border_colision(Entity_t entity, Collision_result_t* result) {
	int entity_left = entity.pos_x;									//EX	E---H	hitbox
	int entity_right = entity.pos_x + entity.anim_info.sprite_w;	//HX	|	|
	int entity_top = entity.pos_y;									//EY	|	|
	int entity_bottom = entity.pos_y + entity.anim_info.sprite_h;	//FY	F---G

	result->collision = true;
	if (entity_right > SCREEN_WIDTH) {
		result->shift_x = (SCREEN_WIDTH - 10 - entity_right);
	}
	else if (entity_left < 0) {
		result->shift_x = (0 + 10 - entity_left);
	}
	else if (entity_top < 0) {
		result->shift_y = -entity_top;
	}
	else if (entity_bottom > SCREEN_HEIGHT) {
		result->shift_y = (SCREEN_HEIGHT - entity_bottom);
	}
	else
		result->collision = false;
}

void collision_shift(int object_left, int object_right, int object_bottom, int object_top,
					 int entity_right, int entity_left, int entity_bottom, int entity_top, Collision_result_t* result) {
	
	if ((entity_bottom > object_top) && (entity_top < object_top)) {					//top colission
		result->shift_y = +object_top - entity_bottom;
		result->change_acc_y_to = 0;
		result->change_v_y_dir_to = 1;
		result->top_edge_collision = true;
	}
	else if ((object_bottom > entity_top) && (entity_top > object_top)) {				//bottom colission
		result->shift_y = -entity_top + object_bottom;
		result->change_v_y_dir_to = -1;
		result->change_v_y_dir_to = 0;
	}
	if (object_left < entity_left && entity_right < object_right && entity_top > object_top && object_bottom > entity_bottom) {

		result->entity_in_object = true;
	}
}

bool horizontal_aligment(int object_left, int object_right, int object_bottom, int object_top,
						  int entity_right, int entity_left, int entity_bottom, int entity_top,  Collision_result_t* result) {
	if (object_bottom > entity_top && entity_bottom > object_top) {
		if (object_left > entity_right) {
			result->entity_on_left_object = true;
		}
		else if (entity_left > object_right) {
			result->entity_on_right_object = true;
		}
		else {
		}
		return true;
	}
	return false;
}

bool vertical_aligment(int object_left,int entity_right,int entity_left,int object_right,
						int entity_bottom,int object_bottom,int object_top,Collision_result_t* result ) {
	if(object_right > entity_left && entity_right > object_left) {
		if (entity_bottom > object_bottom) {
			result->entity_under_object = true;
		}
		else if (entity_bottom < object_top) {
			result->entity_over_object = true;
		}
		else {
			result->touching_platform = true;
		}
		 return true;
	}
	return false;
}

void collision_entities_with_objects(Object object, Entity_t entity, Collision_result_t* result, int i) { //collision object with entity

	bool aligned_vertically = false;
	bool aligned_horizontally = false;
	int object_left = object.pos_x;								//AX	A---B	hitbox
	int object_right = object.pos_x + object.width;				//BX	|	|
	int object_top = object.pos_y;								//AY	|	|
	int object_bottom = object.pos_y + object.height;			//CY	C---D

	int entity_left = entity.pos_x;									//EX	E---H	hitbox
	int entity_right = entity.pos_x + entity.anim_info.sprite_w;	//HX	|	|
	int entity_top = entity.pos_y;									//EY	|	|
	int entity_bottom = entity.pos_y + entity.anim_info.sprite_h;	//FY	F---G
	if (result->collision == false)
		if ((entity_right > object_left || entity_left < object_right) && ((entity_bottom + RANGE) > object_top || (entity_top - RANGE) > object_bottom)) {
			
			aligned_vertically = vertical_aligment(object_left, entity_right, entity_left, object_right, entity_bottom, object_bottom, object_top, result);
			
			aligned_horizontally = horizontal_aligment(object_left, object_right, object_bottom, object_top, entity_right, entity_left,  entity_bottom, entity_top, result);
			
			if (aligned_vertically == true && aligned_horizontally == true) {
				result->collision = true;
				collision_shift(object_left, object_right, object_bottom, object_top, entity_right, entity_left, entity_bottom, entity_top, result);
			}
			//else {
				//result->shift_y = +object_top - entity_bottom;
				//result->change_acc_y_to = 0;
			//}
			if (result->touching_platform == true) {
				result->change_acc_y_to = 0;
			}
			else {
				result->change_acc_y_to = ACCELERATION;
			}
		}
		else {
			result->change_acc_y_to = ACCELERATION;
		}
}

void barrels_collision(Entity_t* barrels, Object* platforms, Collisions_all_t* all_results) {
	if (barrels != nullptr && barrels->num_of_entities != 0) {

		all_results->ptr_result_barrel = (Collision_result_t*)calloc(14, (barrels->num_of_entities) * sizeof(Collision_result_t*));

		for (int i = 0; i < barrels->num_of_entities; i++) {
			map_border_colision(barrels[i], &all_results->ptr_result_barrel[i]);

			for (int j = 0; j < platforms->number_of_objects; j++) {
				collision_entities_with_objects(platforms[j], barrels[i], &all_results->ptr_result_barrel[i], j);
			}
			all_results->ptr_result_barrel[i].ptr_to_using_ladder = nullptr;
		}
	}
	all_results->result_barrel.ptr_to_using_ladder = nullptr;
}

void handle_ladder_colision(Object* ladders, Entity_t player, Collision_result_t* ladder_result) {
	for (int i = 0; i < ladders->number_of_objects; i++) {
		collision_entities_with_objects(ladders[i], player, ladder_result, i);
	}
}

void entity_player_collision(Entity_t** player, Entity_t* entity, Collision_result_t* res_player_barrel) {
	Object entity_object;
	if (entity != nullptr)
		for (int i = 0; i < entity->num_of_entities; i++) {
			entity_object = create_object_form_entity(&entity_object, &entity[i]);
			collision_entities_with_objects(entity_object, **player, res_player_barrel, i);
			if (res_player_barrel->entity_over_object == true && res_player_barrel->collision == false) {
				player[0][0].points_earned = 500;
			}
			if (res_player_barrel->collision == true) {
				break;
			}
		}
}

void shift_purses(Object***** purses,int index_starting_shift) {
	
	for (int i = 0; index_starting_shift + i < purses[0][0][0][0]->number_of_objects - 1; i++) {
		purses[0][0][0][0][index_starting_shift + i + 1].number_of_objects = purses[0][0][0][0][index_starting_shift + i].number_of_objects;
		purses[0][0][0][0][index_starting_shift + i] = purses[0][0][0][0][index_starting_shift + i + 1]; //shifting purses by of from purse that player colided with
	}
	
	purses[0][0][0][0]->number_of_objects--;
	
	if(purses[0][0][0][0]->number_of_objects>0)
	****purses = (Object*)realloc(****purses, sizeof(Object) * purses[0][0][0][0]->number_of_objects);
	if (****purses == NULL) {
		printf("panika realloc purses sie nie udal");
		exit;
	}
}

void handle_purse_collision(Entity_t** player, Object**** purses) {
	if (***purses != nullptr) {
		Collision_result_t* purse_player_result=nullptr;
		purse_player_result = (Collision_result_t*)calloc(14, sizeof(Collision_result_t) * purses[0][0][0]->number_of_objects);
		
		for (int i = 0; i < purses[0][0][0]->number_of_objects; i++) {
			collision_entities_with_objects(purses[0][0][0][i], **player, &purse_player_result[i], i);
			if (purse_player_result[i].collision == true) {
				shift_purses(&purses, i);
				player[0]->points_earned = 500;
				break;
			}
		}
		free(purse_player_result);
	}
}

void handle_collisions(Entity_t* player, Entity_t* barrels, Entity_t kong, Object* ladders, Object* platforms,
						Object*** purses, Collisions_all_t* all_results) {

	barrels_collision(barrels, platforms, all_results);

	map_border_colision(*player, &all_results->result_player);

	handle_ladder_colision(ladders, *player, &all_results->result_ladder);
	if (*all_results->result_player.ptr_to_using_ladder == true && all_results->result_ladder.entity_in_object == false && all_results->result_ladder.top_edge_collision == false) {
		*all_results->result_player.ptr_to_using_ladder = false;
	}

	for (int i = 0; i < platforms->number_of_objects; i++) {
		if (*all_results->result_player.ptr_to_using_ladder == false)
			collision_entities_with_objects(platforms[i], *player, &all_results->result_player, i);
		if ((all_results->result_player.collision == true || (all_results->result_player.touching_platform == true))) {
			break;
		}
	}
	entity_player_collision(&player, barrels, &all_results->res_player_barrel);

	entity_player_collision(&player, &kong, &all_results->res_player_kong);

	handle_purse_collision(&player, &purses);
}
