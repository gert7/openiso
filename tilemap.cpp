#include "tilemap.hh"
#include "debug.hpp"
#include "OpenISO.h"

#include <sstream>
#include <string>
#include <fstream>
#include <filesystem>

namespace ISO {
	void tilemap::init_map_(int width, int height) {
		map = std::vector<std::vector<int>>
			(height, std::vector<int>(width));
	}

	tilemap::tilemap(int width, int height): 
		width(width),
		height(height)
	{
		init_map_(width, height);
	}

	tilemap::tilemap(fs::path path) {
		std::fstream csv(path.c_str(), std::ios::in);
		debug(path);
		map = std::vector<std::vector<int>>();
		map.emplace_back(); // y = 0

		int value = 0;
		char unit = '\0';
		int width = -1, height = -1;
		int x = 0, y = 0;

		for (;;) {
			if (csv.eof()) {
				height = y;
				break;
			}

			csv >> std::noskipws >> value >> unit;

			if (unit == '\n') {
				map.at(y).emplace_back(value);
				if (width == -1)
					width = x + 1;
				else if ((width - 1) != x) {
					debug(width);
					debug(x);
					throw ISO::fatal_error();
				}

				x = 0;
				y++;
				map.emplace_back();
			}
			else if(unit == ',') {
				if (width > -1 && x >= width)
					derro("Tilemap row longer than previously described!");
				map.at(y).emplace_back(value);
				x++;
			}
			else {
				derro("Invalid character in tilemap CSV!");
			}
		}
		this->height = height;
		this->width = width;
	}

	// void tilemap::convert_to_binary() {
	// }

}
