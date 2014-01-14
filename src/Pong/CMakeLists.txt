# Add Pong executable from dummy main
add_executable(Pong main.cpp)
target_link_libraries(Pong sfml-graphics sfml-main sfml-system sfml-window sfml-audio sfml-network)
