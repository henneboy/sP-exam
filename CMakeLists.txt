cmake_minimum_required(VERSION 3.27)
project(sP-exam)

set(CMAKE_CXX_STANDARD 23)
include(Cmake/doctest.cmake)
include(Cmake/matplotplusplus.cmake)


add_executable(Run_main Executables/main.cpp
        Vessel.hpp
        symbol_table.hpp
        reactant-store.hpp
        Simulator.hpp
        Observer.hpp
        Plotter.hpp
        build_circadian_rhythm.cpp
        Meta/canAcceptVisitor.hpp
)
target_link_libraries(Run_main PRIVATE doctest::doctest_with_main)
target_link_libraries(Run_main PUBLIC matplot)

add_executable(pretty_printing Executables/run_pretty_printing.cpp
        Vessel.hpp
        symbol_table.hpp
        reactant-store.hpp
        build_circadian_rhythm.cpp
)

enable_testing()
add_executable(my_test Tests/vessel-test.cpp
        Vessel.hpp
        symbol_table.hpp
        Tests/symbol_table_test.cpp
        reactant-store.hpp
        Tests/reactant_store_test.cpp
        printingVisitor.h++
        Simulator.hpp
        Observer.hpp
        Plotter.hpp
        build_circadian_rhythm.cpp
        Meta/canAcceptVisitor.hpp
)
target_link_libraries(my_test PRIVATE doctest::doctest_with_main)
#target_link_libraries(my_test PUBLIC matplot)

add_test(NAME my_test COMMAND my_test)