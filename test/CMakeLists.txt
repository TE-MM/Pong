include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# find Boost libraries
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS unit_test_framework)

if(Boost_FOUND)

	## For each new test module defined, a new executable needs to made,
	## linked to the Boost UTF (and any other dependent libraries), and
	## registered in CTest. Follow this format:
	##     add_executable(<executable_name> PongTests/<your_cpp_file1>.cpp [PongTests/<your_cpp_file2>.cpp [PongTests/your_cpp_file3>.cpp]])
	##     target_link_libraries(<executable_name> ${BOOST_UNIT_TEST_FRAMEWORK_LIBRARY} [other library targets])
	##     add_test(<test_name> <executable_name>)

	# Boost Check
	add_executable(boostcheck PongTests/boost_check.cpp)
	target_link_libraries(boostcheck ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
	add_test(BoostCheck boostcheck)

	# SFML Check
	add_executable(sfmlcheck PongTests/sfml_check.cpp)
	target_link_libraries(sfmlcheck ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${SFML_LIBRARIES})
	add_test(SFMLCheck sfmlcheck)

	# Manager Test
	add_executable(entitytests PongTests/entity_tests.cpp)
	target_link_libraries(entitytests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${SFML_LIBRARIES} temm-entities)
	add_test(EntityTests entitytests)

	# Post-build DLL move for SFML binaries (One-time only - done after SFML Check)
	# if(WINDOWS AND NOT SFML_STATIC_LIBRARIES)
	#     foreach(sfml_lib ${SFML_LIBRARIES})
	#         add_custom_command(TARGET sfmlcheck POST_BUILD
	#                            COMMAND copy ${sfml_lib} ${EXECUTABLE_OUTPUT_PATH})
	#     endforeach(sfml_lib)
	# endif()

endif()

