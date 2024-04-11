cmake_minimum_required(VERSION 3.27)
project(Shape_example)

set(CMAKE_CXX_STANDARD 23)
include(doctest.cmake)

add_executable(Run_main main.cpp)
target_link_libraries(Run_main PRIVATE doctest::doctest_with_main)

enable_testing()
add_executable(my_test number_series_test.cpp)
target_link_libraries(my_test PRIVATE doctest::doctest_with_main)
add_test(NAME my_test COMMAND my_test)