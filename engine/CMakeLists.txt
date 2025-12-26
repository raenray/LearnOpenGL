add_library(engine STATIC)

target_sources(engine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Log.cpp

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
    EnTT::EnTT
    spdlog::spdlog
)

target_compile_definitions(engine PUBLIC
    ENGINE_ASSET_DIR="${CMAKE_SOURCE_DIR}/assets/"
)
