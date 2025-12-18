#pragma once

#include <engine/layer/Layer.h>

struct GLFWwindow;

namespace engine
{

class ImGuiLayer final : public Layer
{
public:
    ImGuiLayer();
    ~ImGuiLayer() override;

    void onAttach() override;
    void onDetach() override;

    void setWindow(GLFWwindow* window);

    void beginFrame();
    void endFrame();

    void beginDockSpace();

private:
    GLFWwindow* m_window = nullptr;
    bool m_initialized = false;
};

} // namespace engine
