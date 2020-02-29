cmake_minimum_required (VERSION 3.8)

project ("ISOGame" VERSION 0.1)

add_library(Game STATIC "game.cpp" "game.h")

target_include_directories(Game PUBLIC "../include")
target_include_directories(Game PUBLIC "${PROJECT_BINARY_DIR}/..")
