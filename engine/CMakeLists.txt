add_library(engine STATIC)

target_sources(engine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/layer/LayerStack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/layer/RenderLayer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/ImGuiLayer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/editor/EditorLayer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/Framebuffer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VertexBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VertexBufferLayout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VertexArray.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IndexBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Camera2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TextureAtlas.cpp
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
