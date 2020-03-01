#include "tilemap.hh"
#include "debug.hpp"
#include "OpenISO.h"

#include <algorithm>
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
			if (csv.eof()) {
				height = y;
				break;
			}

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

	void tilemap::convert_to_binary(tilemap const& inmap, fs::path path) {
		std::vector<char> result;
		result.push_back((char) inmap.width); // lsb
		result.push_back((char) (inmap.width >> 8)); // msb
		result.push_back((char) inmap.height); // lsb
		result.push_back((char) (inmap.height >> 8)); // msb
		for (const auto& y : inmap.map)
			for (const auto& x : y)
				result.push_back((char) x);

		auto beep = std::ofstream("tilemap.tmap", std::ofstream::out);
		beep.write(result.data(), result.size());
	}

	tilemap tilemap::convert_from_binary(fs::path path) {
		std::ifstream tmap(path.c_str(), std::ios::in);
		uint8_t wls, wms, hls, hms;
		uint8_t single;
		int width, height;

		tmap >> wls >> wms >> hls >> hms;
		width = wls + (wms << 8);
		height = hls + (hms << 8);
		auto result = tilemap(width, height);
		for(auto& y : result.map)
			for (auto& x : y) {
				tmap >> single;
				x = single;
			}

		return result;
	}
}
