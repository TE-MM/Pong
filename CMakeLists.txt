cmake_minimum_required(VERSION 2.8)
project(Pong)

# version number
set(Pong_VERSION_MAJOR 0)
set(Pong_VERSION_MINOR 0)
set(Pong_VERSION_PATCH 0)

# specify output path of executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# include SFML include directory and recurse into CMake project
include_directories("${PROJECT_SOURCE_DIR}/extlibs/cmake/SFML/include")
add_subdirectory(extlibs/cmake/SFML)

# recurse into Pong source where executable is added
add_subdirectory(src/Pong)
