cmake_minimum_required (VERSION 3.8)

project ("OpenISO" VERSION 0.1)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

option(OISO_LUA_SUPPORT "Enable Lua support" YES)
set(OISO_DEBUG_LEVEL 8 CACHE STRING "Debug level 8 = debug, 4 = note, 2 = warn, 1 = error")

configure_file(cmake_bridge.h.in cmake_bridge.h)

# Add source to this project's executable.
add_executable (OpenISO "OpenISO.cpp" "OpenISO.h"
		"instance.cpp" "instance.hh"
		"debug.cpp" "debug.hpp"
		"sdl_kbstate.cpp" "sdl_kbstate.hh"
		"tilemap.cpp" "tilemap.hh"
		"room.hh" "structures.hh")

# target_sources (OpenISO PUBLIC "game/game.cpp")

add_subdirectory("game")
target_link_libraries(OpenISO "${CMAKE_BINARY_DIR}/game/Game.lib")

target_link_directories(OpenISO PUBLIC "lib")
target_link_directories(OpenISO PUBLIC "lib/x64")
target_include_directories(OpenISO PRIVATE "include")
target_include_directories(OpenISO PUBLIC ${PROJECT_BINARY_DIR})

if(MSVC)
	configure_file("lib/x64/SDL2.dll" "${CMAKE_BINARY_DIR}/SDL2.dll" COPYONLY)
	configure_file("lib/x64/libjpeg-9.dll" "${CMAKE_BINARY_DIR}/libjpeg-9.dll" COPYONLY)
	configure_file("lib/x64/libpng16-16.dll" "${CMAKE_BINARY_DIR}/libpng16-16.dll" COPYONLY)
	configure_file("lib/x64/libtiff-5.dll" "${CMAKE_BINARY_DIR}/libtiff-5.dll" COPYONLY)
	configure_file("lib/x64/libwebp-7.dll" "${CMAKE_BINARY_DIR}/libwebp-7.dll" COPYONLY)
	configure_file("lib/x64/SDL2_image.dll" "${CMAKE_BINARY_DIR}/SDL2_image.dll" COPYONLY)
	configure_file("lib/x64/zlib1.dll" "${CMAKE_BINARY_DIR}/zlib1.dll" COPYONLY)
endif()

file(COPY "game/res" DESTINATION "${CMAKE_BINARY_DIR}")

target_link_libraries(OpenISO "${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2.lib")
target_link_libraries(OpenISO "${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2main.lib")
target_link_libraries(OpenISO "${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2_image.lib")
# find_library(SDL2 NAMES "SDL2" PATHS "lib/x64")
# find_library(SDL2_IMAGE NAMES "SDL2_image" PATHS "lib/x64")

link_directories("lib/x64")

# add_library(SDL2 SHARED IMPORTED)
# add_library(SDL2_image SHARED IMPORTED)

# target_link_libraries(OpenISO SDL2)
# target_link_libraries(OpenISO SDL2_image)

# TODO: Add tests and install targets if needed.
