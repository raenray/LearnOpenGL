#pragma once

#include <memory>

#include <engine/layer/Layer.h>
#include <engine/renderer/Framebuffer.h>
#include <imgui.h>

namespace engine
{

class EditorLayer : public Layer
{
public:
    EditorLayer();
    ~EditorLayer() override = default;

    void onAttach() override;
    void onDetach() override;

    void onUpdate(float dt) override;
    void onRender() override;
    void onImGuiRender() override;

private:
    void drawDockedWindows();

    void drawHierarchy();
    void drawInspector();
    void drawSceneView();

private:
    bool m_showDemoWindow = false;
    std::shared_ptr<Framebuffer> m_sceneFramebuffer;
    ImVec2 m_viewportSize = { 0, 0 };
};

} // namespace engine
