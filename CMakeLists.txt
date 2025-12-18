cmake_minimum_required(VERSION 3.16)
project(LearnOpenGL VERSION 1.0 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glad)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glm)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/stb)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
include(${CMAKE_SOURCE_DIR}/cmake/imgui.cmake)

add_subdirectory(${CMAKE_SOURCE_DIR}/engine)
add_subdirectory(${CMAKE_SOURCE_DIR}/app)
