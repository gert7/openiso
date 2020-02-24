#include "debug.hpp"

namespace ISO {
    void post_error(const std::string& context, _debug_file_line dfileline) {
        fetch_time();
        std::cout << clockstr << " " << context << " Error: " << SDL_GetError() << "\n";
        std::cout << "Fatal error in " << dfileline._FILE << "(" << dfileline._LINE << ")";
        throw ISO::fatal_error();
    }

    std::stringstream dss0 = std::stringstream();
}
