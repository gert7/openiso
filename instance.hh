#ifndef _INSTANCE_H_
#define _INSTANCE_H_

#include "structures.hh"
#include "sdl_kbstate.hh"

namespace ISO {

	void apply_camera_rectangle(SDL_Rect* source, SDL_Rect* destination, int x, int y);


	struct instance {
		SDL_Window* win = nullptr;
		SDL_Renderer* ren = nullptr;

		pixel_camera main_camera{ 0, 0 };
		pixel_camera_speed main_camera_speed{ 4, 4 };
		char main_camera_direction{ (char)direction::None };

		SDL_Event l_event;
		bool event_present = false;
		bool quit = false;
		bool camera_locked = false;

		sdl_kbstate kbstate = sdl_kbstate();
		/** 
			State that an event is present to be handled. */
		void instance::set_event();
		/**
			Zero out the oncoming event. */
		void instance::reset_event();
		/**
			Have the engine handle this event. This is called whenever an SDL event remains
			in the l_event member. */
		bool instance::handle_event(SDL_Event* e);
		/**
			Update the camera given the current directions and speeds.  */
		void update_camera();

		instance();
		~instance();
	};
}

#endif