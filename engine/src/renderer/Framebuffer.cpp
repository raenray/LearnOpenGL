#include <engine/renderer/Framebuffer.h>
#include <engine/Texture.h>

#include <glad/gl.h>

#include <iostream>
#include <vector>

namespace engine
{

Framebuffer::Framebuffer(uint32_t width, uint32_t height)
    : m_width(width)
    , m_height(height)
{
    invalidate();
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &m_fbo);
    // glDeleteTextures(1, &m_colorAttachment);
    glDeleteRenderbuffers(1, &m_rbo);
}

void Framebuffer::invalidate()
{
    if (m_fbo)
    {
        glDeleteFramebuffers(1, &m_fbo);
        glDeleteRenderbuffers(1, &m_rbo);
    }

    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // color texture
    std::vector<uint32_t> data(m_width * m_height, 0xffffffff);
    m_colorAttachment = std::make_unique<Texture>(m_width, m_height, data.data());

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment->getID(), 0);

    // depth-stencil
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "Framebuffer incomplete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_width, m_height);
}

void Framebuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::resize(uint32_t width, uint32_t height)
{
    if (width == 0 || height == 0)
        return;

    m_width = width;
    m_height = height;
    invalidate();
}

unsigned int Framebuffer::getColorAttachment() const
{
    return m_colorAttachment->getID();
}

} // namespace engine
