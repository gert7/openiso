#include "OpenISO.h"
#include "debug.hpp"
#include "resourcepath.h"
#include "texture.h"
#include <SDL2/SDL.h>

#include "game/game.h"

#include "sdl_kbstate.hh"
#include "instance.hh"
#include "tilemap.hh"

#undef main // per SDL.h

int main()
{
	ISO::instance instance;
	ISOGame game(&instance);
	ISO::tilemap tilemap(ISO::append_resource("roman.csv"));
	ISO::tilemap::convert_to_binary(tilemap);

	game.setup();

	SDL_Init(SDL_INIT_VIDEO);
	instance.win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (instance.win == nullptr) ISO::post_error("SDL_CreateWindow", dline());

	instance.ren = SDL_CreateRenderer(instance.win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance.ren == nullptr) ISO::post_error("SDL_CreateRenderer", dline());
	
	auto tile_png_path = ISO::append_resource("tile.bmp");
	auto tex = ISO::texture(instance.ren, tile_png_path);

	SDL_Rect a = { 32, 32, 32, 32 };
	bool quit = false;

	for (;;) {
		if (SDL_PollEvent(&instance.l_event)) {
			game.update();
			instance.quit = instance.handle_event(&instance.l_event);
		}

		if (instance.quit)
			break;

		SDL_RenderClear(instance.ren);
		instance.update_camera();

		int camera_x = instance.main_camera.x;
		int camera_y = instance.main_camera.y;
		SDL_Rect destination_a{ 0, 0, 0, 0 };


		for (int y = 0; y < tilemap.height; y++) {
			a.x = 32 - (y * 16);
			a.y = 32 + (y * 8);
			for (int x = 0; x < tilemap.width; x++) {
				a.x += 16;
				a.y += 8;
				ISO::apply_camera_rectangle(&a, &destination_a, camera_x, camera_y);
				if(tilemap.map.at(y).at(x) > 0)
					SDL_RenderCopy(instance.ren, tex.tex(), NULL, &destination_a);
			}
		}
		game.draw();
		a = { 32, 32, 32, 32 };
		SDL_RenderPresent(instance.ren);
		SDL_Delay(10);
	}

	SDL_Quit();
	return 0;
}

