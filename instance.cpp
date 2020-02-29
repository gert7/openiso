#include "instance.hh"

namespace ISO {
	void apply_camera_rectangle(SDL_Rect* source, SDL_Rect* destination, int x, int y) {
		destination->w = source->w;
		destination->h = source->h;
		destination->x = source->x - x;
		destination->y = source->y - y;
	}

	instance::instance() {
		SDL_memset(&l_event, 0, sizeof(l_event));
		l_event.type = SDL_USEREVENT;
	}

	instance::~instance() {
		if (win != nullptr)
			SDL_DestroyWindow(win);
		if (ren != nullptr)
			SDL_DestroyRenderer(ren);
		SDL_Quit();
	}

	void instance::reset_event() {

	}

	bool instance::handle_event(SDL_Event* e) {
		switch (e->type) {
		case SDL_QUIT:
			return true;
			break;
		case SDL_KEYDOWN:
		{
			char dir = (char)main_camera_direction;

			if (kbstate.at(SDL_SCANCODE_RIGHT)) {
				dir |= (char)ISO::direction::Right;
				dir &= ~(char)ISO::direction::Left;
			}
			if (kbstate.at(SDL_SCANCODE_LEFT)) {
				dir |= (char)ISO::direction::Left;
				dir &= ~(char)ISO::direction::Right;
			}
			if (kbstate.at(SDL_SCANCODE_UP)) {
				dir |= (char)ISO::direction::Up;
				dir &= ~(char)ISO::direction::Down;
			}
			if (kbstate.at(SDL_SCANCODE_DOWN)) {
				dir |= (char)ISO::direction::Down;
				dir &= ~(char)ISO::direction::Up;
			}
			main_camera_direction = dir;
		}
		break;
		case SDL_KEYUP:
			if (!kbstate.at(SDL_SCANCODE_RIGHT))
				main_camera_direction &= ~(char)ISO::direction::Right;
			if (!kbstate.at(SDL_SCANCODE_LEFT))
				main_camera_direction &= ~(char)ISO::direction::Left;
			if (!kbstate.at(SDL_SCANCODE_UP))
				main_camera_direction &= ~(char)ISO::direction::Up;
			if (!kbstate.at(SDL_SCANCODE_DOWN))
				main_camera_direction &= ~(char)ISO::direction::Down;
			break;
		}
		return false;
	}

	void instance::update_camera() {
		int cam_speed_x = main_camera_speed.x;
		int cam_speed_y = main_camera_speed.y;
		if (main_camera_direction & (char)ISO::direction::Left)
			main_camera.x -= cam_speed_x;
		if (main_camera_direction & (char)ISO::direction::Right)
			main_camera.x += cam_speed_x;
		if (main_camera_direction & (char)ISO::direction::Up)
			main_camera.y -= cam_speed_y;
		if (main_camera_direction & (char)ISO::direction::Down)
			main_camera.y += cam_speed_y;
	}
}

