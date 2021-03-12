cmake_minimum_required(VERSION 3.17)

project(engine)
include_directories(../include)

set(SOURCE_LIBS core.cpp graphics.cpp general.cpp)
add_library(engine SHARED ${SOURCE_LIBS})