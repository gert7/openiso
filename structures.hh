#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

namespace ISO {
	enum class direction : char {
		None = 0,
		Left = 1,
		Right = 2,
		Up = 4,
		Down = 8
	};

	struct vertex {
		int x;
		int y;
	};

	using pixel_camera = vertex;
	using pixel_camera_speed = vertex;
}
#endif // !_STRUCTURES_H_
