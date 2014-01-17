# Find Boost installation. This is defined in the CMake installation.
# If Boost isn't found, the test executable won't be built.
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
if(Boost_FOUND)
    enable_testing()
    include_directories(${Boost_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
    add_executable(boostcheck PongTests/boost_check.cpp)
    target_link_libraries(boostcheck ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    add_test(BoostCheck boostcheck)
endif()
