#include "instance.hh"

namespace ISO {
	void apply_camera(SDL_Rect* source, SDL_Rect* destination, int x, int y) {
		destination->w = source->w;
		destination->h = source->h;
		destination->x = source->x - x;
		destination->y = source->y - y;
	}

	instance::~instance() {
		if (win != nullptr)
			SDL_DestroyWindow(win);
		if (ren != nullptr)
			SDL_DestroyRenderer(ren);
		SDL_Quit();
	}
}

