#include <iostream>
#include <SDL2/SDL.h>
#include "game.h"

ISOGame::ISOGame(ISO::instance* instance): instance(instance) {
}

void ISOGame::setup() {

}

void ISOGame::update() {
	SDL_SetWindowTitle(instance->win, "Beenus");
}

void ISOGame::draw() {

}

