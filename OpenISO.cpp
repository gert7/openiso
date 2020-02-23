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
#undef main // per SDL.h

int main()
{
	ISO::instance instance;
	ISOGame game(&instance);

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

	for (;;) {
		if (quit)
			break;

		SDL_RenderClear(instance.ren);
		SDL_PollEvent(&e);
		switch (e.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
		{
			char dir = (char)instance.main_camera_direction;

			if (instance.kbstate.at(SDL_SCANCODE_RIGHT)) {
				dir |= (char)ISO::direction::Right;
				dir &= ~(char)ISO::direction::Left;
			}
			if (instance.kbstate.at(SDL_SCANCODE_LEFT)) {
				dir |= (char)ISO::direction::Left;
				dir &= ~(char)ISO::direction::Right;
			}
			if (instance.kbstate.at(SDL_SCANCODE_UP)) {
				dir |= (char)ISO::direction::Up;
				dir &= ~(char)ISO::direction::Down;
			}
			if (instance.kbstate.at(SDL_SCANCODE_DOWN)) {
				dir |= (char)ISO::direction::Down;
				dir &= ~(char)ISO::direction::Up;
			}
			instance.main_camera_direction = dir;
		}
			break;
		case SDL_KEYUP:
			if (!instance.kbstate.at(SDL_SCANCODE_RIGHT))
				instance.main_camera_direction &= ~(char)ISO::direction::Right;
			if (!instance.kbstate.at(SDL_SCANCODE_LEFT))
				instance.main_camera_direction &= ~(char)ISO::direction::Left;
			if (!instance.kbstate.at(SDL_SCANCODE_UP))
				instance.main_camera_direction &= ~(char)ISO::direction::Up;
			if (!instance.kbstate.at(SDL_SCANCODE_DOWN))
				instance.main_camera_direction &= ~(char)ISO::direction::Down;
			break;
		}

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

		for (int y = 0; y < 4; y++) {
			a.x = 32 - (y * 16);
			a.y = 32 + (y * 8);
			for (int x = 0; x < 4; x++) {
				a.x += 16;
				a.y += 8;
				ISO::apply_camera(&a, &destination_a, camera_x, camera_y);
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

