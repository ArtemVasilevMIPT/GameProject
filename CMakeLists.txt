cmake_minimum_required(VERSION 3.0)
project(AwesomeGame)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(include)
add_subdirectory(src)

add_executable(AwesomeGame main.cpp)

find_package(SFML 2.5.1 COMPONENTS graphics window REQUIRED)

target_link_libraries(AwesomeGame sfml-graphics sfml-window engine)