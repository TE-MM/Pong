#######################################################
### Pong will generate library files. Many of the Pong
### classes can be reused outside of Pong.
#######################################################

include_directories(${PROJECT_SOURCE_DIR}/src)

# Set library output
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

# Add subdirectories for each library
add_subdirectory(TEMM/Entities)

#######################################################
### The Pong game itself is an executable.
#######################################################

# Set executable output
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

add_subdirectory(Pong)
