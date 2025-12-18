#include <engine/core/Application.h>
#include <engine/layer/Layer.h>
#include <engine/ui/ImGuiLayer.h>

#include <imgui.h>

#include <print>

class TestLayer : public engine::Layer
{
public:
    TestLayer() : Layer("TestLayer") {}

    void onImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Layer system works");
        ImGui::End();
    }
};

int main()
{
    engine::Application app;

    try{
        // app.pushLayer(new TestLayer());

        app.run();
    }catch(const std::exception& e)
    {
        std::println("Application error: {}", e.what());
        return -1;
    }
    return 0;
}
