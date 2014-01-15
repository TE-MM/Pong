cmake_minimum_required(VERSION 2.8)
project(Pong)

# determines system and compiler
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

# version number
set(Pong_VERSION_MAJOR 0)
set(Pong_VERSION_MINOR 0)
set(Pong_VERSION_PATCH 0)

# recurse into Pong source where executable is added
add_subdirectory(src/Pong)
