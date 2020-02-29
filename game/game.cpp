#include <iostream>
#include <SDL2/SDL.h>
#include "game.h"

ISOGame::ISOGame(ISO::instance* instance): instance(instance) { }

void ISOGame::setup() {

}

SDL_Rect e{1, 250, 500, 250};
SDL_Rect border1{1, 240, 500, 10};

void ISOGame::update() {
}

void ISOGame::draw() {
	SDL_SetRenderDrawColor(instance->ren, 0, 225, 32, 255);
	SDL_RenderFillRect(instance->ren, &e);
	SDL_SetRenderDrawColor(instance->ren, 0, 255, 0, 255);
	SDL_RenderFillRect(instance->ren, &border1);
	SDL_SetRenderDrawColor(instance->ren, 0, 0, 0, 0);
}

