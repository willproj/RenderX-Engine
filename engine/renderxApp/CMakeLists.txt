cmake_minimum_required(VERSION 3.25.0)
project(RenderX)

set(APP_ICON_RESOURCE_WINDOWS ${CMAKE_SOURCE_DIR}/assets/logo/renderx.rc)

add_executable (RenderX renderxApp.h renderxApp.cpp main.cpp ${APP_ICON_RESOURCE_WINDOWS})

target_include_directories(RenderX PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${CMAKE_SOURCE_DIR}/engine
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/imgui
	PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/imgui/backends
	PUBLIC ${CMAKE_SOURCE_DIR}/assets
	PUBLIC ${CMAKE_SOURCE_DIR}/config
)

# Add link directories
target_link_directories(RenderX PRIVATE ${CMAKE_SOURCE_DIR}/thirdParty/glfw/src
	PRIVATE ${CMAKE_SOURCE_DIR}/thirdParty/glad/src
)


# Add link library
target_link_libraries(RenderX PUBLIC openglCore imgui gui)

set_target_properties(RenderX
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

install(TARGETS RenderX DESTINATION ${CMAKE_SOURCE_DIR}/out/install)
