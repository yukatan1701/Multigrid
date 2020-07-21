cmake_minimum_required(VERSION 3.0)

project(Multigrid VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D DEBUG")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -D DEBUG")

include_directories(include)

file(GLOB SOURCES source/*.cpp)

add_executable(mgm ${SOURCES})

