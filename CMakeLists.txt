cmake_minimum_required(VERSION 3.27)
project(sP-exam)

set(CMAKE_CXX_STANDARD 23)
include(Cmake/doctest.cmake)
include(Cmake/matplotplusplus.cmake)
include(Cmake/benchmark.cmake)
find_package(Threads REQUIRED)


add_executable(circadian_graph Executables/circadian_plot_graph.cpp
        Vessel.hpp
        symbol_table.hpp
        reactant_store.hpp
        Simulator.hpp
        Observers/Observer.hpp
        Plotter.hpp
        Examples/build_circadian_rhythm.h++
        Examples/build_circadian_rhythm.cpp
        Examples/build_seihr.h++
        Examples/build_seihr.cpp

)
target_link_libraries(circadian_graph PRIVATE doctest::doctest_with_main)
target_link_libraries(circadian_graph PUBLIC matplot)

add_executable(pretty_printing Executables/run_pretty_printing.cpp
        Vessel.hpp
        symbol_table.hpp
        reactant_store.hpp
        Examples/build_circadian_rhythm.h++
        Examples/build_circadian_rhythm.cpp
        Examples/build_seihr.h++
        Examples/build_seihr.cpp
        pretty_printing.h++
)

add_executable(make_dot_file Executables/make_dot_file.cpp
        Vessel.hpp
        symbol_table.hpp
        reactant_store.hpp
        ReactionsToDot.hpp
        Examples/build_circadian_rhythm.h++
        Examples/build_circadian_rhythm.cpp
        Examples/build_seihr.h++
        Examples/build_seihr.cpp
)

enable_testing()
add_executable(my_test Tests/vessel_test.cpp
        Vessel.hpp
        symbol_table.hpp
        Tests/symbol_table_test.cpp
        reactant_store.hpp
        Tests/reactant_store_test.cpp
        Simulator.hpp
        Observers/Observer.hpp
        ReactionsToDot.hpp
        Examples/build_circadian_rhythm.h++
        Examples/build_circadian_rhythm.cpp
        Examples/build_seihr.h++
        Examples/build_seihr.cpp
        Tests/pretty_printing_test.cpp
        Tests/pretty_printing_test.cpp
        pretty_printing.h++
)

target_link_libraries(my_test PRIVATE doctest::doctest_with_main)
#target_link_libraries(my_test PUBLIC matplot)
add_test(NAME my_test COMMAND my_test)

add_executable(seihr_peak_single_thread Executables/seihr_peak_single_thread.cpp
        Vessel.hpp
        symbol_table.hpp
        reactant_store.hpp
        Simulator.hpp
        Observers/Observer.hpp
        Plotter.hpp
        Examples/build_seihr.h++
        Examples/build_seihr.cpp
        utilities.h++
)
target_link_libraries(seihr_peak_single_thread PUBLIC matplot)

add_executable(seihr_plot_graph Executables/seihr_plot_graph.cpp
        Vessel.hpp
        symbol_table.hpp
        reactant_store.hpp
        Simulator.hpp
        Observers/Observer.hpp
        Plotter.hpp
        Examples/build_seihr.h++
        Examples/build_seihr.cpp
)
target_link_libraries(seihr_plot_graph PUBLIC matplot)

add_executable(seihr_peak_thread_pool Executables/seihr_peak_thread_pool.cpp
        Vessel.hpp
        symbol_table.hpp
        reactant_store.hpp
        Simulator.hpp
        Observers/Observer.hpp
        Plotter.hpp
        Examples/build_seihr.h++
        Examples/build_seihr.cpp
        utilities.h++
)

add_executable(bm_seihr Executables/bm_seihr.cpp
        Vessel.hpp
        symbol_table.hpp
        reactant_store.hpp
        Simulator.hpp
        Observers/Observer.hpp
        Plotter.hpp
        Examples/build_seihr.h++
        Examples/build_seihr.cpp
        utilities.h++
)

target_link_libraries(bm_seihr PRIVATE Threads::Threads benchmark::benchmark_main)
#add_test(NAME bm_seihr_single_thread COMMAND bm_seihr_single_thread)

add_executable(sample_trajectories_graph Executables/sample_trajectories.cpp
        Examples/build_sample_trejectory.h++
        Examples/build_sample_trejectory.cpp
)
target_link_libraries(sample_trajectories_graph PUBLIC matplot)

