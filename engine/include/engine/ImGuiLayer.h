#pragma once

struct GLFWwindow;

namespace engine
{

class ImGuiLayer
{
public:
    ImGuiLayer() = default;
    ~ImGuiLayer() = default;

    ImGuiLayer(const ImGuiLayer&) = delete;
    ImGuiLayer& operator=(const ImGuiLayer&) = delete;

    void init(GLFWwindow* window);
    void shutdown();

    void beginFrame();
    void endFrame();

    void setDarkTheme();

private:
    bool m_initialized = false;
};

} // namespace engine
