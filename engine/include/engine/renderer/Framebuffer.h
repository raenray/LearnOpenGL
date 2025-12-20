#pragma once

#include <cstdint>
#include <memory>

namespace engine
{

class Texture;

class Framebuffer
{
public:
    Framebuffer(uint32_t width, uint32_t height);
    ~Framebuffer();

    void bind();
    void unbind();

    void resize(uint32_t width, uint32_t height);

    unsigned int getColorAttachment() const;

private:
    void invalidate();

private:
    uint32_t m_fbo = 0;
    std::unique_ptr<Texture> m_colorAttachment;
    
    uint32_t m_rbo = 0;

    uint32_t m_width = 0;
    uint32_t m_height = 0;
};

} // namespace engine
