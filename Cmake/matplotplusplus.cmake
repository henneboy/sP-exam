include(FetchContent)
FetchContent_Declare(gnuplot
        GIT_REPOSITORY https://git.code.sf.net/p/gnuplot/gnuplot-main gnuplot-gnuplot-main
        GIT_TAG origin/master)
FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master)
FetchContent_GetProperties(matplotplusplus)
if(NOT matplotplusplus_POPULATED)
    FetchContent_Populate(matplotplusplus)
    add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()