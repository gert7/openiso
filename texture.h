#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>
#include <SDL2/SDL.h>

#include "debug.hpp"
#include <SDL2/SDL_image.h>

namespace ISO {
	class texture {
		SDL_Texture* tex_ = nullptr;
	public:
		texture(SDL_Renderer* ren, const std::string& path){
			tex_ = IMG_LoadTexture(ren, path.c_str());
			if (tex_ == nullptr) 
				ISO::post_error("LoadTexture", dline());
		}

		~texture() {
			SDL_DestroyTexture(tex_);
		}

		SDL_Texture* tex() const {
			return tex_;
		}
	};
}

#endif // !_TEXTURE_H
