cmake_minimum_required(VERSION 3.27)
project(sP-exam)

set(CMAKE_CXX_STANDARD 23)
include(doctest.cmake)
include(matplotplusplus.cmake)


add_executable(Run_main main.cpp
        Vessel.hpp
        symbol_table.hpp
        reactant-store.hpp
        Simulator.hpp
        Observer.hpp
)
target_link_libraries(Run_main PRIVATE doctest::doctest_with_main)
target_link_libraries(Run_main PUBLIC matplot)

enable_testing()
add_executable(my_test vessel-test.cpp
        Vessel.hpp
        symbol_table.hpp
        symbol_table_test.cpp
        reactant-store.hpp
        reactant_store_test.cpp
        printingVisitor.h++
        PrintingVisitorTest.cpp
        Simulator.hpp
        Observer.hpp
)
target_link_libraries(my_test PRIVATE doctest::doctest_with_main)
#target_link_libraries(my_test PUBLIC matplot)

add_test(NAME my_test COMMAND my_test)