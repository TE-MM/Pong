cmake_minimum_required(VERSION 2.8)
project(Pong)

# determines system and compiler
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

# version number
set(Pong_VERSION_MAJOR 0)
set(Pong_VERSION_MINOR 0)
set(Pong_VERSION_PATCH 1)

# set paths
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")

# link the appropriate SFML libraries for the OS
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

# include TEMM include and Boost include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${Boost_INCLUDE_DIR})

# recurse into source
add_subdirectory(src/TEMM)
add_subdirectory(src/Pong)

### TESTING ###

include(CTest)

# add testing
add_subdirectory(test)
