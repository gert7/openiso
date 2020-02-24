#ifndef _RESOURCEPATH_H
#define _RESOURCEPATH_H

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace ISO {
	const fs::path resource_path() {
		return fs::current_path() / "res";
	}

	fs::path append_resource(fs::path suffix) {
		fs::path uri = resource_path();
		uri /= suffix;
		return uri;
	}
}

#endif // !_RESOURCEPATH_H
