cmake_minimum_required(VERSION 3.25.0)
project(openglCore)

file(GLOB_RECURSE SOURCE_FILES_EXE 
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# Add header files
file(GLOB_RECURSE HEADER_FILES_EXE 
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

add_library (openglCore ${HEADER_FILES_EXE} ${SOURCE_FILES_EXE})


target_include_directories(openglCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${CMAKE_SOURCE_DIR}/engine
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/glfw/include
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/glad/include
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/stb/include
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/glm
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/imgui/backends
	PUBLIC ${CMAKE_SOURCE_DIR}/assets
	PUBLIC ${CMAKE_SOURCE_DIR}/config
)

# Add link directories
target_link_directories(openglCore PRIVATE ${CMAKE_SOURCE_DIR}/thirdParty/glfw/src
	PRIVATE ${CMAKE_SOURCE_DIR}/thirdParty/glad/src
)


# Add link library
target_link_libraries(openglCore PRIVATE glfw glad glm stb event input gui)

set_target_properties(openglCore PROPERTIES FOLDER "engine")
