cmake_minimum_required(VERSION 3.27)
project(Shape_example)

set(CMAKE_CXX_STANDARD 23)
include(doctest.cmake)

add_executable(Run_main main.cpp
        Vessel.hpp
        symbol_table.hpp
        reactant-store.hpp
)
target_link_libraries(Run_main PRIVATE doctest::doctest_with_main)

enable_testing()
add_executable(my_test vessel-test.cpp
        Vessel.hpp
        symbol_table.hpp
        symbol_table_test.cpp
        reactant-store.hpp
        reactant_store_test.cpp
        printingVisitor.h++
        PrintingVisitorTest.cpp
)
target_link_libraries(my_test PRIVATE doctest::doctest_with_main)
add_test(NAME my_test COMMAND my_test)