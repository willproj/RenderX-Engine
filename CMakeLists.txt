# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("RenderX")


# Include cmake files
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(global_settings)

# set config
configure_file(${CMAKE_SOURCE_DIR}/config/config.h.in ${CMAKE_SOURCE_DIR}/config/config.h)


# Include dependenciees
add_subdirectory("thirdParty/glfw")
add_subdirectory("thirdParty/glad")
add_subdirectory("thirdParty/glm")
add_subdirectory("thirdParty/stb")
add_subdirectory("thirdParty/assimp")
add_subdirectory("thirdParty/imgui")
add_subdirectory("thirdParty/spdlog")
add_subdirectory("engine/gui")
add_subdirectory("engine/event")
add_subdirectory("engine/input")
add_subdirectory("engine/log")
add_subdirectory("engine/openglCore")
add_subdirectory ("engine")

set_target_properties(glfw PROPERTIES FOLDER "thirdParty")
set_target_properties(glad PROPERTIES FOLDER "thirdParty")
set_target_properties(glm PROPERTIES FOLDER "thirdParty")
set_target_properties(stb PROPERTIES FOLDER "thirdParty")
set_target_properties(assimp PROPERTIES FOLDER "thirdParty")
set_target_properties(imgui PROPERTIES FOLDER "thirdParty")
set_target_properties(spdlog PROPERTIES FOLDER "thirdParty")
set_target_properties(uninstall PROPERTIES FOLDER "thirdParty")
set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER "thirdParty")
set_target_properties(update_mappings PROPERTIES FOLDER "thirdParty")
set_target_properties(zlibstatic PROPERTIES FOLDER "thirdParty")



