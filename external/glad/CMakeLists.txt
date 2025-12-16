cmake_minimum_required(VERSION 3.10)
project(Glad VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(glad STATIC
    src/gl.c
)

target_include_directories(glad PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)