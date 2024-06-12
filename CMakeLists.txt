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
        Meta/canAcceptVisitor.hpp
        Examples/build_circadian_rhythm.h++
        Examples/build_circadian_rhythm.cpp
        Examples/build_seihr.h++
        Examples/build_seihr.cpp

)
target_link_libraries(Run_main PRIVATE doctest::doctest_with_main)
target_link_libraries(Run_main PUBLIC matplot)

add_executable(pretty_printing Executables/run_pretty_printing.cpp
        Vessel.hpp
        symbol_table.hpp
        reactant-store.hpp
        Examples/build_circadian_rhythm.h++
        Examples/build_circadian_rhythm.cpp
        Examples/build_seihr.h++
        Examples/build_seihr.cpp
)

add_executable(make_dot_file Executables/make_dot_file.cpp
        Vessel.hpp
        symbol_table.hpp
        reactant-store.hpp
        ReactionsToDot.hpp
        Examples/build_circadian_rhythm.h++
        Examples/build_circadian_rhythm.cpp
        Examples/build_seihr.h++
        Examples/build_seihr.cpp
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
        Meta/canAcceptVisitor.hpp
        ReactionsToDot.hpp
        Examples/build_circadian_rhythm.h++
        Examples/build_circadian_rhythm.cpp
        Examples/build_seihr.h++
        Examples/build_seihr.cpp
)

target_link_libraries(my_test PRIVATE doctest::doctest_with_main)
#target_link_libraries(my_test PUBLIC matplot)
add_test(NAME my_test COMMAND my_test)
