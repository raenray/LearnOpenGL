#pragma once

#include <memory>

namespace engine
{

class Window;
class ImGuiLayer;

class Application
{
public:
    Application();
    ~Application();
    void run();

private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<ImGuiLayer> imgui;
};

} // namespace engine
