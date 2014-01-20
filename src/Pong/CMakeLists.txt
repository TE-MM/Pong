#######################################################
### The Pong game itself is an executable.
#######################################################

# Set executable output
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

# Add Pong executable from dummy main (changed later)
add_executable(Pong main.cpp)
target_link_libraries(Pong ${SFML_LIBRARIES})

