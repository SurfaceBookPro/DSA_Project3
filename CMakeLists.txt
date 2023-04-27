
cmake_minimum_required(VERSION 3.25)
project(DSA_Project3)

set(CMAKE_CXX_STANDARD 17)

add_executable(DSA_Project3 HierarchicalClustering.h HierarchicalClustering.cpp K_MeansClustering.h K_MeansClustering.cpp main.cpp)

include(FetchContent)
FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master)

FetchContent_GetProperties(matplotplusplus)
if(NOT matplotplusplus_POPULATED)
    FetchContent_Populate(matplotplusplus)
    add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(DSA_Project3 PUBLIC matplot)
