cmake_minimum_required(VERSION 3.25.0)
project(scene)

file(GLOB SOURCE_FILES_EXE 
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# Add header files
file(GLOB HEADER_FILES_EXE 
	 ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

add_library (scene ${HEADER_FILES_EXE} ${SOURCE_FILES_EXE})

target_include_directories(scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${CMAKE_SOURCE_DIR}/engine
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/glfw/include
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/glad/include
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/stb/include
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/glm
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/imgui/backends
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/imgui/
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/entt/include
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/assimp/include
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/yaml-cpp/include
	PUBLIC ${CMAKE_SOURCE_DIR}/config
)

# Add link directories
target_link_directories(scene PRIVATE ${CMAKE_SOURCE_DIR}/thirdParty/glfw/src
	PRIVATE ${CMAKE_SOURCE_DIR}/thirdParty/glad/src
)

target_link_directories(scene PUBLIC entt openglCore renderer glfw glad glm input utils assimp utils yaml-cpp)

set_target_properties(scene PROPERTIES FOLDER "engine")
