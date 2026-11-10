#pragma once
void init_player_data(Entity_t* player, SDL_sprites_t sprite);

void init_barrel_data(Entity_t* barrel, SDL_sprites_t sprite);

void init_platform_data(Object* platform, SDL_sprites_t* sprite, int first_plat_x, int first_plat_y, int place_in_array, int angle);

void init_ladder_data(Object* ladder, SDL_sprites_t* sprites, int x, int y, int height);

void init_kong_data(Entity_t* kong, SDL_sprites_t sprite);

void init_purse_data(Object* purse, SDL_sprites_t sprites, int x, int y);