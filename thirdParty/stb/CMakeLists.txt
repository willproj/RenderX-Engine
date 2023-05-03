cmake_minimum_required(VERSION 3.25.0)
project(stb)

add_library(stb include/stb/stb_image.h include/stb/stb_image.cpp)
target_include_directories(stb PUBLIC include/)