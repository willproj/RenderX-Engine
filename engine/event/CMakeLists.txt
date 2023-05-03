cmake_minimum_required(VERSION 3.25.0)
project(event)

file(GLOB SOURCE_FILES_EXE 
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.c
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Add header files
file(GLOB HEADER_FILES_EXE 
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.h
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_library (event ${HEADER_FILES_EXE} ${SOURCE_FILES_EXE})

target_include_directories(event PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${CMAKE_SOURCE_DIR}/engine
)

set_target_properties(event PROPERTIES FOLDER "engine")