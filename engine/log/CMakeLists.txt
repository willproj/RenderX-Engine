cmake_minimum_required(VERSION 3.25.0)
project(log)

add_library (log log.h log.cpp)

target_include_directories(log PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/spdlog/include
	PUBLIC ${CMAKE_SOURCE_DIR}/engine
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(log PRIVATE spdlog)

set_target_properties(log PROPERTIES FOLDER "engine")