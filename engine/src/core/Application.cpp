#include <engine/core/Application.h>
#include <engine/Window.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <engine/Shader.h>
#include <engine/VertexArray.h>
#include <engine/VertexBuffer.h>
#include <engine/IndexBuffer.h>
#include <engine/Texture.h>
#include <engine/Renderer.h>
#include <engine/Renderer2D.h>
#include <engine/Camera2D.h>
#include <engine/Sprite.h>
#include <engine/TextureAtlas.h>

#include <engine/layer/Layer.h>
#include <engine/layer/RenderLayer.h>
#include <engine/ui/ImGuiLayer.h>
#include <engine/editor/EditorLayer.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>

namespace engine
{

void draw_ui()
{
    ImGui::Begin("Demo");
    ImGui::Text("Hello ImGui");
    ImGui::End();
}
Application::Application()
{
    m_window = std::make_unique<Window>(1280, 720, "LearnOpenGL Engine");

    // m_layerStack.pushLayer(new SceneLayer());

    m_layerStack.pushLayer(new RenderLayer());
    m_layerStack.pushLayer(new EditorLayer());

    m_imgui = new ImGuiLayer();
    m_imgui->setWindow(m_window->nativeHandle());
    m_layerStack.pushOverlay(m_imgui);

    for(auto& layer: m_layerStack)
    {
        layer->onAttach();
    }
}

Application::~Application() = default;

void Application::run()
{
    float lastTime = 0.0f;
    // while (m_running)
    while (!m_window->shouldClose())
    {
        float time = (float)glfwGetTime();
        float deltaTime = time - lastTime;
        lastTime = time;

        // Update
        for (Layer* layer : m_layerStack)
            layer->onUpdate(deltaTime);

        // Render
        for (Layer* layer : m_layerStack)
            layer->onRender();

        // ImGui
        m_imgui->beginFrame();
        m_imgui->beginDockSpace();

        for (Layer* layer : m_layerStack)
            layer->onImGuiRender();

        m_imgui->endFrame();
        m_window->swapBuffers();
        m_window->pollEvents();
    }
}

void Application::pushLayer(Layer* layer)
{
    m_layerStack.pushLayer(layer);
}

void Application::pushOverlay(Layer* overlay)
{
    m_layerStack.pushOverlay(overlay);
}

GLFWwindow* Application::nativeHandle()
{
    return m_window->nativeHandle();
}

} // namespace engine
