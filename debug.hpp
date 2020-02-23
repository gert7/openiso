#ifndef _DEBUG_HPP
#define _DEBUG_HPP

#include <iostream>
#include <cstdio>
#include <ctime>

// #include "buildopts.h"

#define DEBUG_REPORTING_LEVEL_DEBUG 1
#define DEBUG_REPORTING_LEVEL_NOTE  2
#define DEBUG_REPORTING_LEVEL_WARN  4
#define DEBUG_REPORTING_LEVEL_ERROR 8

#define DEBUG_REPORTING_LEVEL 1

static char clockstr[9] {0, 0, 0, 0, 0, 0, 0, 0, 0};

static void fetch_time() {
  time_t rawtime;
  struct tm* ptm;

  time(&rawtime);

  ptm = gmtime(&rawtime);

  snprintf(clockstr, sizeof(clockstr), "%02d:%02d:%02d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
}

#define _debug_rest(line) clockstr << " " << __FILE__ << ":" << __LINE__ << ": " << line << std::endl

#if DEBUG_REPORTING_LEVEL >= 8
#define debug(line) { \
  fetch_time(); \
  std::cout << "[D] " << _debug_rest(line); \
}
#else
#define debug(line) {}
#endif

 #if DEBUG_REPORTING_LEVEL >= 2
#define dwarn(line) { \
  fetch_time(); \
  std::cout << "[W] " << _debug_rest(line); \
}
#else
#define dwarn(line) {}
#endif

#if DEBUG_REPORTING_LEVEL >= 1
#define derro(line) { \
  fetch_time(); \
  std::cout << "[E] " << _debug_rest(line); \
}
#else
#define derro(line) {}
#endif

#if DEBUG_REPORTING_LEVEL >= 4
#define dnote(line) { \
  fetch_time(); \
  std::cout << "[N] " << _debug_rest(line); \
}
#else
#define dnote(line) {}
#endif

// SDL specific stuff

#include <SDL2/SDL.h>
#include "OpenISO.h"

struct _debug_file_line {
	const char* _FILE;
	int _LINE;
	_debug_file_line(const char* f, int l) : _FILE(f), _LINE(l) { }
};

#define dline() _debug_file_line(__FILE__, __LINE__)

namespace ISO {
    void post_error(const std::string& context, _debug_file_line dfileline);
}

#endif

