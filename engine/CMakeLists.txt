cmake_minimum_required(VERSION 3.25.0)
project(common)



add_library(common common.h common.cpp)

add_subdirectory("renderxApp")

set_target_properties(common PROPERTIES FOLDER "engine")



