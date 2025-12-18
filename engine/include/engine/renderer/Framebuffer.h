#pragma once

#include <cstdint>

namespace engine
{

class Framebuffer
{
public:
    Framebuffer(uint32_t width, uint32_t height);
    ~Framebuffer();

    void bind();
    void unbind();

    void resize(uint32_t width, uint32_t height);

    uint32_t getColorAttachment() const { return m_colorAttachment; }

private:
    void invalidate();

private:
    uint32_t m_fbo = 0;
    uint32_t m_colorAttachment = 0;
    uint32_t m_rbo = 0;

    uint32_t m_width = 0;
    uint32_t m_height = 0;
};

} // namespace engine
