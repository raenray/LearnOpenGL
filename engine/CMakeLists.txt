add_library(engine STATIC)

target_sources(engine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Application.cpp

)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(engine PUBLIC
    glfw
    glad
    glm
    stb
    imgui
)

target_compile_definitions(engine PUBLIC
    ENGINE_ASSET_DIR="${CMAKE_SOURCE_DIR}/assets/"
)
