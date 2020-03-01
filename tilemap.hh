#ifndef _TILEMAP_H_
#define _TILEMAP_H_

#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

namespace ISO {
	struct tilemap {
	private:
		void init_map_(int x, int y);
	public:
		int width;
		int height;
		std::vector<std::vector<int>> map;

		tilemap(int width, int height);
		tilemap(fs::path path);
		static void convert_to_binary(tilemap const&, fs::path path);
		static tilemap convert_from_binary(fs::path path);
	};
}

#endif // !_TILEMAP_H_
