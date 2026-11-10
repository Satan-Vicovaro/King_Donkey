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


void execute_close(SDL_pointers_t SDL_ptrs);

void clear_sprites(SDL_sprites_t SDL_sprites);

SDL_Texture* LoadTexture(char filepath[], SDL_Renderer* render_target);

void generate_scr(SDL_pointers_t* SDL_ptrs);

void create_colours(colours* colors_tab, SDL_Surface* screen);

bool init_surfaces(SDL_pointers_t* SDL_ptrs, SDL_sprites_t* SDL_sprites);

bool SDL_start(SDL_pointers_t* SDL_ptrs, SDL_sprites_t* SDL_sprites, colours* col_t);

bool init_screen(SDL_pointers_t* SDL_ptrs);