#ifndef _INSTANCE_H_
#define _INSTANCE_H_

#include "sdl_kbstate.hh"

namespace ISO {
	enum class direction : char {
		None  = 0,
		Left  = 1,
		Right = 2,
		Up    = 4,
		Down  = 8
	};

	void apply_camera(SDL_Rect* source, SDL_Rect* destination, int x, int y);

	struct vertex {
		int x;
		int y;
	};

	using pixel_camera = vertex;
	using pixel_camera_speed = vertex;

	struct instance {
		SDL_Window* win = nullptr;
		SDL_Renderer* ren = nullptr;

		pixel_camera main_camera{ 0, 0 };
		pixel_camera_speed main_camera_speed{ 4, 4 };
		char main_camera_direction{ (char)direction::None };

		SDL_Event l_event;
		bool quit = false;

		sdl_kbstate kbstate = sdl_kbstate();
		bool instance::handle_event(SDL_Event* e);
		void update_camera();

		instance();
		~instance();
	};
}

#endif