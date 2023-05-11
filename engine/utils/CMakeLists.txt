cmake_minimum_required(VERSION 3.25.0)
project(utils)

file(GLOB SOURCE_FILES_EXE 
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# Add header files
file(GLOB HEADER_FILES_EXE 
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

add_library (utils ${HEADER_FILES_EXE} ${SOURCE_FILES_EXE})


target_include_directories(utils 
	PUBLIC ${CMAKE_SOURCE_DIR}/engine
	PUBLIC ${CMAKE_SOURCE_DIR}/config
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/glad/include
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/glfw/include
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/yaml-cpp/include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(utils PRIVATE glfw glad openglCore yaml-cpp scene)

set_target_properties(utils PROPERTIES FOLDER "engine")