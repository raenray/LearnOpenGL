#pragma once

#include <engine/layer/LayerStack.h>

#include <memory>

struct GLFWwindow;

namespace engine
{

class Window;
class ImGuiLayer;
class RenderLayer;

class Application
{
public:
    Application();
    ~Application();
    
    void run();

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* overlay);

    GLFWwindow* nativeHandle();
private:
    std::unique_ptr<Window> m_window;
    ImGuiLayer* m_imgui = nullptr;
    bool m_running = true;
    LayerStack m_layerStack;
    
};

} // namespace engine
