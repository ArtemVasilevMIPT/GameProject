cmake_minimum_required(VERSION 3.0)

project(engine)
include_directories(../include)

set(SOURCE_LIBS core.cpp graphics.cpp general.cpp gui.cpp entities.cpp pathfinding.cpp)
add_library(engine SHARED ${SOURCE_LIBS})