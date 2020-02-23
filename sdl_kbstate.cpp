#include "sdl_kbstate.hh"

namespace ISO {
	sdl_kbstate::sdl_kbstate() {
		kbstate = SDL_GetKeyboardState(&size);
		if (kbstate == nullptr)
			ISO::post_error("SDL_GetKeyboardState", dline());
	}

	bool sdl_kbstate::at(SDL_Scancode scancode) {
		if ((uint32_t)scancode > size)
			throw std::out_of_range("Keyboard state out of range!");
		else
			return (bool)kbstate[scancode];
	}
}
