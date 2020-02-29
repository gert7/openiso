#ifndef _SDL_KBSTATE_H_
#define _SDL_KBSTATE_H_

#include <SDL2/SDL.h>

#include "debug.hpp"

namespace ISO {
	/**
		Wrapper for SDL Keyboard state. Returns state of SDL_Scancode.  */
	class sdl_kbstate {
		const Uint8* kbstate = nullptr;
		int size = -1;
	public:
		sdl_kbstate();
		/**
			Check if key with given scancode is currently held down.  */
		bool at(SDL_Scancode scancode);
	};
}

#endif
