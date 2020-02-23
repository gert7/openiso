# CMakeList.txt : CMake project for OpenISO, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("OpenISO" VERSION 0.1)

option(OISO_LUA_SUPPORT "Enable Lua support" YES)

configure_file(cmake_bridge.h.in cmake_bridge.h)

# Add source to this project's executable.
add_executable (OpenISO "OpenISO.cpp" "OpenISO.h")

add_subdirectory("game")

find_package(Vulkan REQUIRED)

target_link_directories(OpenISO PUBLIC "lib")
target_link_directories(OpenISO PUBLIC "lib/x64")
target_include_directories(OpenISO PRIVATE "include")
if(MSVC)
	configure_file("lib/x64/SDL2.dll" "${CMAKE_BINARY_DIR}/SDL2.dll" COPYONLY)
	configure_file("lib/x64/libjpeg-9.dll" "${CMAKE_BINARY_DIR}/libjpeg-9.dll" COPYONLY)
	configure_file("lib/x64/libpng16-16.dll" "${CMAKE_BINARY_DIR}/libpng16-16.dll" COPYONLY)
	configure_file("lib/x64/libtiff-5.dll" "${CMAKE_BINARY_DIR}/libtiff-5.dll" COPYONLY)
	configure_file("lib/x64/libwebp-7.dll" "${CMAKE_BINARY_DIR}/libwebp-7.dll" COPYONLY)
	configure_file("lib/x64/SDL2_image.dll" "${CMAKE_BINARY_DIR}/SDL2_image.dll" COPYONLY)
	configure_file("lib/x64/zlib1.dll" "${CMAKE_BINARY_DIR}/zlib1.dll" COPYONLY)
endif()

target_link_libraries(OpenISO "${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2.lib")
target_link_libraries(OpenISO "${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2main.lib")
target_link_libraries(OpenISO "${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2_image.lib")
target_link_libraries(OpenISO "${CMAKE_BINARY_DIR}/game/TheGame.lib")
# find_library(SDL2 NAMES "SDL2" PATHS "lib/x64")
# find_library(SDL2_IMAGE NAMES "SDL2_image" PATHS "lib/x64")

link_directories("lib/x64")

# add_library(SDL2 SHARED IMPORTED)
# add_library(SDL2_image SHARED IMPORTED)

# target_link_libraries(OpenISO SDL2)
# target_link_libraries(OpenISO SDL2_image)

# TODO: Add tests and install targets if needed.
