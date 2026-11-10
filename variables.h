#pragma once

#define SCREEN_WIDTH	1720 //px
#define SCREEN_HEIGHT	980  //px

#define DISTANCE_BETWEEN_2_LINES 30	//px
#define TEXT_SIZE 2 //multiplicative
#define DRAW_POINTS_ABOVE_PLAYER -50 //y px

#define STARTING_POS_P_X 1		//px
#define STARTING_POS_P_Y 850	//px

#define SPRITE_SCALE 4		// multiplicative
#define ANIMATION_SPEED 3	//lower = faster

#define KONG_POS_X 10
#define KONG_POS_Y 122

#define BARREL_SPAWN_POINT_X KONG_POS_X + 20	//px
#define BARREL_SPAWN_POINT_Y KONG_POS_Y + 20	//px
#define BARREL_SPEED 20	//px/delta

#define p_velocity 5	//px/delta
#define ACCELERATION 1		//px/delta
#define JUMP_POWER 18		//px/delta

#define LEFT -1
#define RIGHT -2
#define USING_LADDER -3

#define SLOPE 10 //in PX

#define RANGE 125 //px range i which jumping over barrel is detected

#define LADDER_WIDTHNESS 3	// multiplicative

#define FIRST_LVL_NUM_OF_PURSES 5

#define MAX_NUMBER_OF_BARRELS 100
#define FIRST_LVL_NUM_1ST_PLATFROMS 4	//number of first platforms
#define FIRST_LVL_NUM_OF_PLATFORMS 33
#define FIRST_LVL_NUM_OF_LADDERS 3

static int first_platform_x_y[FIRST_LVL_NUM_1ST_PLATFROMS][2] = { {0,940}, {-20,700}, {0,250}, {200,550} };
static int num_of_platforms[FIRST_LVL_NUM_1ST_PLATFROMS] = { 9,8,8,8 };
static int angle_of_platforms[FIRST_LVL_NUM_1ST_PLATFROMS] = { 0,-1,0,1 };

static int ladder_info_x_y[FIRST_LVL_NUM_OF_LADDERS][2] = { {1000,745} ,{250,545}, {1220,245} };
static int ladder_info_height[FIRST_LVL_NUM_OF_LADDERS] = { 50,43,65 };

static int purses_info_x_y[FIRST_LVL_NUM_OF_PURSES][2] = { {600,695},{0,400},{1500,600},{1170,214},{400,904} };

typedef struct colours {
	int black = 0;
	int green = 0;
	int red = 0;
	int blue = 0;
}colours;

typedef struct world_info_t {
	int frames = 0;

	double fpsTimer = 0;
	double fps = 0;

	double worldTime = 0;

	double delta = 0;

	int t1 = 0;
	int t2 = 0;
}world_info_t;

typedef struct Anim_t {;
	int sprite_x = NULL;
	int sprite_y = NULL;
	int sprite_h = NULL;
	int sprite_w = NULL;

	bool direction_matters = NULL;
	int direction = NULL;

	int sprite_destination_x = NULL;
	int sprite_destination_y = NULL;

	int sprite_scale = NULL;
	int movement_frame = NULL;
}Anim_t;

typedef struct SDL_pointers_t {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* screen = nullptr;
	SDL_Texture* scrtex = nullptr;
}SDL_pointers_t;

typedef struct SDL_sprites_t {

	SDL_Surface* charset = nullptr;
	SDL_Surface* hydraulik = nullptr;
	SDL_Surface* plumber = nullptr;
	SDL_Surface* barrel = nullptr;
	SDL_Surface* platform_short = nullptr;
	SDL_Surface* platform_long = nullptr;
	SDL_Surface* ladder = nullptr;
	SDL_Surface* kong = nullptr;
	SDL_Surface* purse = nullptr;

}SDL_sprites_t;

typedef struct Entity_t { //struct for player and barrels

	double acc_y = 1;
	double  vel_x = 0;
	double  vel_y = 0;
	int pos_x = STARTING_POS_P_X;
	int pos_y = STARTING_POS_P_Y;
	SDL_Surface* ptr_to_sprite = nullptr;
	bool is_barrel = false;
	int num_of_entities = 1;
	int points_earned = 0;

	Anim_t anim_info;

}Entity_t;

typedef struct Object { //immovable objects: ladders, platforms, purses
	SDL_Surface* ptr_to_sprite = nullptr;

	int pos_x = 0;
	int pos_y = 0;
	int height = 0;
	int width = 0;

	int number_of_objects = 0;

}Object;


typedef struct Collision_result_t {
	
	bool entity_under_object = false;
	bool entity_over_object = false;
	bool entity_on_left_object = false;
	bool entity_on_right_object = false;
	bool entity_in_object = false;
	bool top_edge_collision = false;
	bool touching_platform = false;
	bool collision = false;
	int shift_x = 0;		//amount of px to shift back the player if collision accur
	int shift_y = 0;		//amount of px to shift back the player if collision accur
	double change_acc_y_to = 0;
	int change_v_y_dir_to = 0;
	bool* ptr_to_using_ladder = nullptr;
	bool barrel_used_to_count_points = false;

}Collision_result_t;

typedef struct Collisions_all_t {
	
	Collision_result_t result_ladder;
	Collision_result_t result_barrel;
	Collision_result_t result_player;
	Collision_result_t res_player_barrel;
	Collision_result_t res_player_kong;
	Collision_result_t* ptr_result_barrel=nullptr;
	Collision_result_t* ptr_result_purse = nullptr;

}Collisions_all_t;
