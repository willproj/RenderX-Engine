cmake_minimum_required(VERSION 3.25.0)
project(input)


file(GLOB_RECURSE SOURCE_FILES_EXE 
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.c
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES_EXE 
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.h
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_library (input ${HEADER_FILES_EXE} ${SOURCE_FILES_EXE})

target_include_directories(input 
	PUBLIC ${CMAKE_SOURCE_DIR}/engine
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/glm
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(input PRIVATE glm event)

set_target_properties(input PROPERTIES FOLDER "engine")
