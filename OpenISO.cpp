// OpenISO.cpp : Defines the entry point for the application.
//

#include "OpenISO.h"
#include "debug.hpp"
#include "resourcepath.h"
#include "texture.h"
#include <SDL2/SDL.h>
#undef main

#include "game/game.h"

namespace ISO {
	struct instance {
		SDL_Window* win;
		SDL_Renderer* ren;

		~instance() {
			if (win != nullptr)
				SDL_DestroyWindow(win);
			if (ren != nullptr)
				SDL_DestroyRenderer(ren);
			SDL_Quit();
		}
	};
}

int main()
{
	ISO::instance instance;

	SDL_Init(SDL_INIT_VIDEO);
	instance.win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (instance.win == nullptr) post_error("SDL_CreateWindow", dline());

	instance.ren = SDL_CreateRenderer(instance.win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance.ren == nullptr) post_error("SDL_CreateRenderer", dline());
	
	auto tile_png_path = ISO::append_resource("tile.bmp");

	auto tex = ISO::texture(instance.ren, tile_png_path);

	SDL_Rect a = { 32, 32, 32, 32 };

	SDL_Event e;

	for (int i = 0; i < 1000; i++) {
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT)
			break;
		for (int i = 0; i < 100; i++) {
			SDL_RenderCopy(instance.ren, tex.tex(), NULL, &a);
			a.x += 16;
			a.y += 8;
		}
		a.x = 32 - (i * 16);
		a.y = 32 + (i * 8);
		SDL_RenderPresent(instance.ren);
		SDL_Delay(10);
	}

	SDL_Quit();
	return 0;
}

