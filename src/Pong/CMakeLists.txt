set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

# Add Pong executable from dummy main
add_executable(Pong main.cpp)

# Link the appropriate libraries for the OS
if(WINDOWS)
    if(ARCH_32BITS)
        set(SFML_ROOT "C:\\Program Files (x86)\\SFML")
    elseif(ARCH_64BITS)
        set(SFML_ROOT "C:\\Program Files\\SFML")
    endif()
    find_package(SFML 2 COMPONENTS window graphics system main REQUIRED)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Pong ${SFML_LIBRARIES})
else()
    find_package(SFML 2 COMPONENTS window graphics system REQUIRED)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Pong ${SFML_LIBRARIES})
endif()
