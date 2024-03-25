# CMakeList.txt : CMake project for OriSpanner, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)
project(OriSpanner)
# Add source to this project's executable.
add_subdirectory(src)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT OriSpanner)
set_property(TARGET OriSpanner PROPERTY CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/modules)
message("$(CMAKE_MODULE_PATH)")
