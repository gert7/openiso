#ifndef _ROOM_H_
#define _ROOM_H_

#include "tilemap.hh"

namespace ISO {
	class room {
		tilemap tmap;
		pixel_camera main_camera{ 0, 0 };
	};
}

#endif // !_ROOM_H_
