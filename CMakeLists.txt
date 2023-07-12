cmake_minimum_required(VERSION 3.14)

project(track2d VERSION 1.0 DESCRIPTION "a simple 2d trajectory estimator")

if (NOT CMAKE_CXX_FLAGS) 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra")
endif()

if (NOT CMAKE_CXX_FLAGS_DEBUG) 
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()

if (NOT CMAKE_CXX_FLAGS_RELEASE) 
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_library(track2d SHARED
    include/track2d.hpp
    src/include/global_average_estimator.hpp
    src/track2d.cpp
    src/statistics.cpp
    src/global_average_estimator.cpp
)

