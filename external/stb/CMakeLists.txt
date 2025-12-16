add_library(stb INTERFACE)  # INTERFACE 表示这个库没有源文件

# 添加头文件目录
target_include_directories(stb INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
