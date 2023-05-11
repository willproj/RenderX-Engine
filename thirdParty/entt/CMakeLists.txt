cmake_minimum_required(VERSION 3.25.0)
project(entt)

add_library(entt include/entt/entt.hpp include/entt/entt.cpp)
target_include_directories(entt PUBLIC include/)