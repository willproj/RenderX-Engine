cmake_minimum_required(VERSION 3.25.0)
project(gui)

file(GLOB_RECURSE SOURCE_FILES_EXE 
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.c
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES_EXE 
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.h
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_library (gui ${HEADER_FILES_EXE} ${SOURCE_FILES_EXE})

target_include_directories(gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${CMAKE_SOURCE_DIR}/engine
	PUBLIC ${CMAKE_SOURCE_DIR}/config
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/imgui
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/imgui/backends
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/glad/include
)

target_link_libraries(gui PRIVATE imgui openglCore)

set_target_properties(gui PROPERTIES FOLDER "engine")