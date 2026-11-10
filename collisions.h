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

void execute_collision_barrel(Entity_t* barrel, Collision_result_t result_barrel);

void execute_collision_player(Entity_t* player, Collisions_all_t* all_results);

void map_border_colision(Entity_t entity, Collision_result_t* result);

void collision_entities_with_objects(Object object, Entity_t entity, Collision_result_t* result, int i);

void handle_ladder_colision(Object* ladders, Entity_t player, Collision_result_t* ladder_result);

void entity_player_collision(Entity_t** player, Entity_t* barrels, Collision_result_t* res_player_barrel);

void handle_collisions(Entity_t* player, Entity_t* barrels, Entity_t kong, Object* ladders, Object* platforms, Object*** purses, Collisions_all_t* all_results);

