#pragma once

#include<math.h>
#include<stdio.h>
#include<string.h>
#include<SDL.h>
#include"variables.h"
#include"conio2.h"


void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);

void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);

void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);

void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

void draw_platforms(SDL_Surface* screen, Object* platforms);

void draw_static_surfaces(SDL_Surface* screen, colours* col_t, Object* platforms, Object* ladders, Object* purses,world_info_t world_info, SDL_Surface* charset);

void draw_texts(SDL_Surface* screen, world_info_t world_info, SDL_Surface* charset);

void draw_ladders(SDL_Surface* screen, Object* ladders);

void draw_ladder_surface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y, int additional_width);

void draw_colission_info(SDL_Surface* screen, Collisions_all_t all_results, SDL_Surface* charset);

void draw_points(SDL_Surface* screen, Entity_t* player, SDL_Surface* charset,world_info_t world_info, bool win);