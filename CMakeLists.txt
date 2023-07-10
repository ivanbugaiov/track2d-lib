cmake_minimum_required(VERSION 3.14)

project(track2d VERSION 1.0 DESCRIPTION "a simple 2d trajectory estimator")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra")

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_library(track2d SHARED
    include/track2d.hpp
    src/include/instant_linear_estimator.hpp

    src/track2d.cpp
    src/instant_linear_estimator.cpp
)

set_target_properties(track2d PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1    
    PUBLIC_HEADER include/track2d.hpp
)

