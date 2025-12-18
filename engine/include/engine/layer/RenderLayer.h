#pragma once

#include <memory>

#include <engine/layer/Layer.h>
#include <engine/renderer/Framebuffer.h>

namespace engine
{

class RenderLayer : public Layer
{
public:
    RenderLayer();
    ~RenderLayer() override = default;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(float dt) override;
    void onRender() override;

    std::shared_ptr<Framebuffer> getSceneFramebuffer() const { return m_framebuffer; }

private:
    std::shared_ptr<Framebuffer> m_framebuffer;
};

} // namespace engine
