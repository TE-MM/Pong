cmake_minimum_required(VERSION 2.8)
project(Pong)

# determines system and compiler
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

# version number
set(Pong_VERSION_MAJOR 0)
set(Pong_VERSION_MINOR 0)
set(Pong_VERSION_PATCH 0)

# set paths
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")

# link the appropriate libraries for the OS
if(WINDOWS)
    if(ARCH_32BITS)
        set(SFML_ROOT "C:\\Program Files (x86)\\SFML")
    elseif(ARCH_64BITS)
        set(SFML_ROOT "C:\\Program Files\\SFML")
    endif()
    find_package(SFML 2 COMPONENTS window graphics system main REQUIRED)
    include_directories(${SFML_INCLUDE_DIR})
else()
    find_package(SFML 2 COMPONENTS window graphics system REQUIRED)
    include_directories(${SFML_INCLUDE_DIR})
endif()

# recurse into Pong source where executable is added
add_subdirectory(src/Pong)

### TESTING ###

include(CTest)

# add testing
add_subdirectory(test)
