#ifndef _SDL_KBSTATE_H_
#define _SDL_KBSTATE_H_

#include <SDL2/SDL.h>

#include "debug.hpp"

namespace ISO {
	class sdl_kbstate {
		const Uint8* kbstate = nullptr;
		int size = -1;
	public:
		sdl_kbstate();
		bool at(SDL_Scancode scancode);
	};
}

#endif
