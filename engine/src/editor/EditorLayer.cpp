#include <engine/editor/EditorLayer.h>
#include <engine/Texture.h>

#include <imgui.h>

namespace engine
{

EditorLayer::EditorLayer()
    : Layer("EditorLayer")
{
}

void EditorLayer::onAttach()
{
    m_sceneFramebuffer = std::make_shared<Framebuffer>(1280, 720);
}

void EditorLayer::onDetach() {}

void EditorLayer::onUpdate(float) {}

void EditorLayer::onRender() {}

void EditorLayer::onImGuiRender()
{
    drawDockedWindows();

    if (m_showDemoWindow)
        ImGui::ShowDemoWindow(&m_showDemoWindow);
}

void EditorLayer::drawDockedWindows()
{
    drawHierarchy();
    drawInspector();
    drawSceneView();
}

void EditorLayer::drawHierarchy()
{
    ImGui::Begin("Hierarchy");

    ImGui::Text("Scene");
    ImGui::Separator();

    ImGui::Selectable("Camera");
    ImGui::Selectable("Light");
    ImGui::Selectable("Cube");

    ImGui::End();
}

void EditorLayer::drawInspector()
{
    ImGui::Begin("Inspector");

    ImGui::Text("Selected: Cube");
    ImGui::Separator();

    ImGui::Text("Transform");
    // ImGui::DragFloat3("Position", nullptr);
    // ImGui::DragFloat3("Rotation", nullptr);
    // ImGui::DragFloat3("Scale", nullptr);

    ImGui::Separator();

    ImGui::Checkbox("ImGui Demo", &m_showDemoWindow);

    ImGui::End();
}

void EditorLayer::drawSceneView()
{
    ImGui::Begin("Scene");
    static bool initialized = false;
    static Texture texture(ENGINE_ASSET_DIR "textures/test1.png");
    if (!initialized)
    {
        initialized = true;

    }

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    if (m_viewportSize.x != viewportPanelSize.x || m_viewportSize.y != viewportPanelSize.y)
    {
        m_viewportSize = viewportPanelSize;
        m_sceneFramebuffer->resize((uint32_t)m_viewportSize.x, (uint32_t)m_viewportSize.y);
    }

    // uint32_t textureID = m_sceneFramebuffer->getColorAttachment();

    // ImGui::Image((void*)(uintptr_t)textureID, ImVec2{m_viewportSize.x, m_viewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});
    ImGui::Image((void*)texture.getID(), ImVec2{m_viewportSize.x, m_viewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});
    ImGui::End();
}

} // namespace engine
