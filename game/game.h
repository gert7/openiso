#ifndef _GAME_H_
#define _GAME_H_

#include "../OpenISO.h"
#include "../instance.hh"

class ISOGame {
	ISO::instance* instance;
public:
	ISOGame(ISO::instance*);
	void setup();
	void update();
	void draw();
};

#endif
