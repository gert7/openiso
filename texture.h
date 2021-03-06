#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>
#include <SDL2/SDL.h>

#include "debug.hpp"
#include <SDL2/SDL_image.h>
#include <filesystem>

namespace fs = std::filesystem;

namespace ISO {
	class texture {
		SDL_Texture* tex_ = nullptr;
	public:
		texture(SDL_Renderer* ren, fs::path path){
			debug(path.string());
			tex_ = IMG_LoadTexture(ren, path.string().c_str());
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
