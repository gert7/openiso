// OpenISO.cpp : Defines the entry point for the application.
//

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

constexpr int tilemap[4][4]
{
	{1, 0, 1, 0},
	{1, 1, 1, 0},
	{1, 0, 0, 0},
	{0, 1, 1, 0}
};

int main()
{
	ISO::instance instance;
	ISOGame game(&instance);
	ISO::tilemap tilemap(ISO::append_resource("roman.csv"));

	game.setup();

	SDL_Init(SDL_INIT_VIDEO);
	instance.win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (instance.win == nullptr) ISO::post_error("SDL_CreateWindow", dline());

	instance.ren = SDL_CreateRenderer(instance.win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance.ren == nullptr) ISO::post_error("SDL_CreateRenderer", dline());
	
	auto tile_png_path = ISO::append_resource("tile.bmp");
	auto tex = ISO::texture(instance.ren, tile_png_path);

	SDL_Rect a = { 32, 32, 32, 32 };
	SDL_Event e;
	bool quit = false;

	// SDL_RenderSetScale(instance.ren, 3.0f, 3.0f);

	for (;;) {
		if (quit)
			break;

		SDL_RenderClear(instance.ren);
		SDL_PollEvent(&e);
		quit = instance.handle_event(&e);

		int cam_speed_x = instance.main_camera_speed.x;
		int cam_speed_y = instance.main_camera_speed.y;
		if (instance.main_camera_direction & (char)ISO::direction::Left)
			instance.main_camera.x -= cam_speed_x;
		if (instance.main_camera_direction & (char)ISO::direction::Right)
			instance.main_camera.x += cam_speed_x;
		if (instance.main_camera_direction & (char)ISO::direction::Up)
			instance.main_camera.y -= cam_speed_y;
		if (instance.main_camera_direction & (char)ISO::direction::Down)
			instance.main_camera.y += cam_speed_y;
		
		int camera_x = instance.main_camera.x;
		int camera_y = instance.main_camera.y;
		SDL_Rect destination_a{ 0,0,0,0 };

		game.update();

		for (int y = 0; y < tilemap.height; y++) {
			a.x = 32 - (y * 16);
			a.y = 32 + (y * 8);
			for (int x = 0; x < tilemap.width; x++) {
				a.x += 16;
				a.y += 8;
				ISO::apply_camera(&a, &destination_a, camera_x, camera_y);
				if(tilemap.map.at(y).at(x) > 0)
					SDL_RenderCopy(instance.ren, tex.tex(), NULL, &destination_a);
			}
		}
		a = { 32, 32, 32, 32 };
		SDL_RenderPresent(instance.ren);
		SDL_Delay(10);
	}

	SDL_Quit();
	return 0;
}

