#include<math.h>
#include<stdio.h>
#include<string.h>
#include<SDL.h>

#include"conio2.h"
#include"init_everything.h"
#include"variables.h"
#include"draw_functions.h"
#include"init_entities.h"

void execute_close(SDL_pointers_t SDL_ptrs) {
	SDL_FreeSurface(SDL_ptrs.screen);
	SDL_DestroyTexture(SDL_ptrs.scrtex);
	SDL_DestroyWindow(SDL_ptrs.window);
	SDL_DestroyRenderer(SDL_ptrs.renderer);
	SDL_Quit();
}

void clear_sprites(SDL_sprites_t SDL_sprites) {
	SDL_FreeSurface(SDL_sprites.barrel);
	SDL_FreeSurface(SDL_sprites.charset);
	SDL_FreeSurface(SDL_sprites.hydraulik);
	SDL_FreeSurface(SDL_sprites.kong);
	SDL_FreeSurface(SDL_sprites.ladder);
	SDL_FreeSurface(SDL_sprites.platform_short);
	SDL_FreeSurface(SDL_sprites.platform_long);
	SDL_FreeSurface(SDL_sprites.plumber);
}

SDL_Texture* LoadTexture(char filepath[], SDL_Renderer* render_target) {
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = SDL_LoadBMP(filepath);
	if (surface == NULL)
		printf("Loading texture error: %s", SDL_GetError());
	else {
		texture = SDL_CreateTextureFromSurface(render_target, surface);
		if (texture == NULL)
			printf("Creating texture error: %s", SDL_GetError());
	}
	SDL_FreeSurface(surface);
	return texture;
}

void generate_scr(SDL_pointers_t* SDL_ptrs) {
	SDL_UpdateTexture(SDL_ptrs->scrtex, NULL, SDL_ptrs->screen->pixels, SDL_ptrs->screen->pitch);
	SDL_RenderCopy(SDL_ptrs->renderer, SDL_ptrs->scrtex, NULL, NULL);
	SDL_RenderPresent(SDL_ptrs->renderer);
}

void create_colours(colours* colors_tab, SDL_Surface* screen) {
	colors_tab->black = SDL_MapRGB(screen->format, 0, 0, 0);
	colors_tab->green = SDL_MapRGB(screen->format, 150, 223, 30);
	colors_tab->red = SDL_MapRGB(screen->format, 245, 0, 52);
	colors_tab->blue = SDL_MapRGB(screen->format, 19, 236, 236);
}

bool init_surfaces(SDL_pointers_t* SDL_ptrs, SDL_sprites_t* SDL_sprites) {

	SDL_sprites->charset = SDL_LoadBMP("./bitmapy/cs8x8.bmp");
	if (SDL_sprites->charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		execute_close(*SDL_ptrs);
		return 1;
	};
	SDL_SetColorKey(SDL_sprites->charset, true, 0x000000);

	//SDL_sprites->hydraulik = SDL_LoadBMP("./bitmapy/hydraulik.bmp");
	//if (SDL_sprites->hydraulik == NULL) {
	//	printf("SDL_LoadBMP(hydraulik.bmp) error: %s\n", SDL_GetError());
	//	execute_close(*SDL_ptrs);
	//	return 1;
	//};
	//SDL_SetColorKey(SDL_sprites->hydraulik, true, 0x005b7f);

	SDL_sprites->plumber = SDL_LoadBMP("./bitmapy/plumber_movement_animation_full.bmp");
	if (SDL_sprites->plumber == NULL) {
		printf("SDL_LoadBMP(plumber_movement_animation_full.bmp) error: %s\n", SDL_GetError());
		execute_close(*SDL_ptrs);
		return 1;
	};
	SDL_SetColorKey(SDL_sprites->plumber, true, 0x005b7f);

	SDL_sprites->platform_long = SDL_LoadBMP("./bitmapy/platfrom_long.bmp");
	if (SDL_sprites->platform_long == NULL) {
		printf("SDL_LoadBMP(platfrom_long.bmp) error: %s\n", SDL_GetError());
		execute_close(*SDL_ptrs);
		return 1;
	};
	SDL_SetColorKey(SDL_sprites->platform_long, true, 0x005b7f);

	SDL_sprites->barrel = SDL_LoadBMP("./bitmapy/barrels.bmp");
	if (SDL_sprites->barrel == NULL) {
		printf("SDL_LoadBMP(barrels.bmp) error: %s\n", SDL_GetError());
		execute_close(*SDL_ptrs);
		return 1;
	};
	SDL_SetColorKey(SDL_sprites->barrel, true, 0x005b7f);

	SDL_sprites->ladder = SDL_LoadBMP("./bitmapy/ladder_short.bmp");
	if (SDL_sprites->ladder == NULL) {
		printf("SDL_LoadBMP(ladder_short.bmp) error: %s\n", SDL_GetError());
		execute_close(*SDL_ptrs);
		return 1;
	};
	//SDL_SetColorKey(SDL_sprites->ladder, true, 0x000000);

	SDL_sprites->kong = SDL_LoadBMP("./bitmapy/Kong_King.bmp");
	if (SDL_sprites->ladder == NULL) {
		printf("SDL_LoadBMP(Kong_King.bmp) error: %s\n", SDL_GetError());
		execute_close(*SDL_ptrs);
		return 1;
	};
	SDL_SetColorKey(SDL_sprites->kong, true, 0x005b7f);

	SDL_sprites->purse = SDL_LoadBMP("./bitmapy/purse.bmp");
	if (SDL_sprites->purse == NULL) {
		printf("SDL_LoadBMP(purse.bmp) error: %s\n", SDL_GetError());
		execute_close(*SDL_ptrs);
		return 1;
	};
	SDL_SetColorKey(SDL_sprites->purse, true, 0x005b7f);

	return 0;
}

bool SDL_start(SDL_pointers_t* SDL_ptrs, SDL_sprites_t* SDL_sprites, colours* col_t) {
	if (init_screen(SDL_ptrs) == 1)
		return 1;

	create_colours(col_t, SDL_ptrs->screen);

	if (init_surfaces(SDL_ptrs, SDL_sprites) == 1)
		return 1;

	return 0;
}

bool init_screen(SDL_pointers_t* SDL_ptrs) {

	SDL_ptrs->window = SDL_CreateWindow("Donkey King", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

	if (SDL_ptrs->window == NULL) {
		printf("CreateWindow error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_ptrs->renderer = SDL_CreateRenderer(SDL_ptrs->window, -1, 0);

	if (SDL_ptrs->renderer == NULL) {
		printf("Renderer error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_SetRenderDrawColor(SDL_ptrs->renderer, 150, 180, 200, 255);
	SDL_RenderSetLogicalSize(SDL_ptrs->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	SDL_ptrs->screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	SDL_ptrs->scrtex = SDL_CreateTexture(SDL_ptrs->renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	return 0;
}