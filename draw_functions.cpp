#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<SDL.h>
#include"variables.h"
#include"conio2.h"
#include"draw_functions.h"

//#define  NUM_PLATFORMS_IN_ROW 7
//#define  LADDER_WIDTHNESS 3

// narysowanie napisu txt na powierzchni screen, zaczynajπc od punktu (x, y)
// charset to bitmapa 128x128 zawierajπca znaki
void DrawString(SDL_Surface* screen, int x, int y, const char* text,
	SDL_Surface* charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8 * TEXT_SIZE;
	d.h = 8 * TEXT_SIZE;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x ;
		d.y = y ;
		SDL_BlitScaled(charset, &s, screen, &d);
		x += 8 * TEXT_SIZE;
		text++;
	};
};

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) lewy gorny rog sprite na ekranie
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = sprite->w * SPRITE_SCALE;
	dest.h = sprite->h * SPRITE_SCALE ;
	SDL_BlitScaled(sprite, NULL, screen, &dest);
};

void draw_ladder_surface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y,int height) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = sprite->w * LADDER_WIDTHNESS * SPRITE_SCALE;
	dest.h = height;
	SDL_BlitScaled(sprite, NULL, screen, &dest);
}

// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
// bπdü poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

// rysowanie prostokπta o d≥ugoúci bokÛw l i k
// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

void draw_platforms(SDL_Surface* screen, Object* platforms) {
	for (int i = 0; i < platforms->number_of_objects; i++) {
		DrawSurface(screen, platforms[i].ptr_to_sprite, platforms[i].pos_x, platforms[i].pos_y);
	}
}

void draw_ladders(SDL_Surface* screen, Object* ladders) {
	for (int i = 0; i < ladders->number_of_objects; i++) {
		draw_ladder_surface(screen,ladders[i].ptr_to_sprite,ladders[i].pos_x,ladders[i].pos_y, ladders[i].height);
	}
}

void draw_purses(SDL_Surface* screen, Object* purses) {
	for(int i = 0; i < purses->number_of_objects; i++) {
	DrawSurface(screen, purses[i].ptr_to_sprite, purses[i].pos_x, purses[i].pos_y);
	}
}

void draw_static_surfaces(SDL_Surface* screen, colours *col_t, Object* platforms,Object* ladders, Object* purses,world_info_t world_info,SDL_Surface* charset) {
	
	SDL_FillRect(screen, NULL, col_t->black);

	DrawRectangle(screen, SCREEN_WIDTH * 0.50, SCREEN_HEIGHT * 0.01, SCREEN_WIDTH * 1.00 - SCREEN_WIDTH * 0.55, SCREEN_HEIGHT*0.24, col_t->green, col_t->red);

	draw_texts(screen, world_info, charset);
	
	draw_platforms(screen, platforms);

	draw_ladders(screen, ladders);

	draw_purses(screen, purses);
}

void draw_texts(SDL_Surface* screen, world_info_t world_info, SDL_Surface* charset) {
	char text[128];
	sprintf(text, "Czas trwania = %.1lf s", world_info.worldTime);
	DrawString(screen, SCREEN_WIDTH * 0.51, SCREEN_HEIGHT * 0.01 + DISTANCE_BETWEEN_2_LINES, text, charset);
	
	sprintf(text, "%.0lf klatek / s", world_info.fps);
	DrawString(screen, SCREEN_WIDTH * 0.51, SCREEN_HEIGHT * 0.01 + 2 * DISTANCE_BETWEEN_2_LINES, text, charset);
	
	sprintf(text, "Delta = %.10lf", world_info.delta);
	DrawString(screen, SCREEN_WIDTH * 0.51, SCREEN_HEIGHT * 0.01 + 3 * DISTANCE_BETWEEN_2_LINES, text, charset);
	
	sprintf(text, "Wykonane_punkty:");
	DrawString(screen, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.01 + DISTANCE_BETWEEN_2_LINES, text, charset);
	
	sprintf(text, "Podstawowe");
	DrawString(screen, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.01 + 2 * DISTANCE_BETWEEN_2_LINES, text, charset);
	
	sprintf(text, "skok");
	DrawString(screen, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.01 + 3 * DISTANCE_BETWEEN_2_LINES, text, charset);

	sprintf(text, "beczki");
	DrawString(screen, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.01 + 4 * DISTANCE_BETWEEN_2_LINES, text, charset);

	sprintf(text, "animacje");
	DrawString(screen, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.01 + 5 * DISTANCE_BETWEEN_2_LINES, text, charset);

	sprintf(text, "pochylone platformy");
	DrawString(screen, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.01 + 6 * DISTANCE_BETWEEN_2_LINES, text, charset);
	
	sprintf(text, "liczenie punktow");
	DrawString(screen, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.01 + 7 * DISTANCE_BETWEEN_2_LINES, text, charset);
}

void draw_colission_info(SDL_Surface* screen, Collisions_all_t all_results, SDL_Surface* charset) {
	char text[128];
	if (all_results.res_player_barrel.collision == true) {
		sprintf(text, "Kolizja beczka!!");
		DrawString(screen, SCREEN_WIDTH * 0.51, SCREEN_HEIGHT * 0.01 + 4 * DISTANCE_BETWEEN_2_LINES, text, charset);
	}
	if (all_results.res_player_kong.collision == true) {
		sprintf(text, "Kolizja  z kongiem!!");
		DrawString(screen, SCREEN_WIDTH * 0.51, SCREEN_HEIGHT * 0.01 + 4 * DISTANCE_BETWEEN_2_LINES, text, charset);
	}
}

void draw_points(SDL_Surface* screen, Entity_t *player, SDL_Surface* charset,world_info_t world_info,bool win) {
	char text[128];
	static int count_points = 0;
	static int count_input_time = 0;
	static int count_draw_time = 0;
	static bool flag = false;

	count_input_time += world_info.delta * 1000;//in miliseconds
	
	if (win == true) {
		count_points = 0;
	}
	if(count_input_time >500 && player->points_earned!=0){
		
		count_points += player->points_earned;
		count_input_time = 0;
		flag = true;
	}
	if (flag == true) {
		count_draw_time += world_info.delta * 1000;//in miliseconds
		if (count_draw_time > 500) {
			count_draw_time = 0;
			flag = false;
		}
		sprintf(text, "+500");
		DrawString(screen, player->pos_x, player->pos_y + DRAW_POINTS_ABOVE_PLAYER, text, charset);
	}

	sprintf(text, "punkty: %d", count_points);
	DrawString(screen, SCREEN_WIDTH * 0.51, SCREEN_HEIGHT * 0.01 + 5 * DISTANCE_BETWEEN_2_LINES, text, charset);

	player->points_earned = 0;
}