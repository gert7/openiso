#ifndef _RESOURCEPATH_H
#define _RESOURCEPATH_H

#include <string>

namespace ISO {
	const char* resource_path() {
		return "./";
	}

	std::string append_resource(std::string suffix) {
		std::string uri;
		uri += resource_path();	
		uri += suffix;
		return uri;
	}
}

#endif // !_RESOURCEPATH_H
