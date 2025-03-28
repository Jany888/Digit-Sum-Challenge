cmake_minimum_required(VERSION 3.16..3.24)
project(Digit-Sum-Challenge
	VERSION 0.0.1
	DESCRIPTION ""
	LANGUAGES CXX)

include(CTest)
add_subdirectory(lib)
add_executable(main main.cpp)

if(BUILD_TESTING)
	add_executable(tests tests.cpp)
	target_link_libraries(tests PRIVATE GTest::gtest_main)

	include(GoogleTest)
	gtest_discover_tests(tests)
endif()