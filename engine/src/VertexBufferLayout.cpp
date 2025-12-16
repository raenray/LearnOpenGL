#include <engine/VertexBufferLayout.h>
#include <glad/gl.h>

namespace engine
{

template <> void VertexBufferLayout::push<float>(unsigned int count)
{
    m_elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_stride += count * sizeof(float);
}

template <> void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
    m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_stride += count * sizeof(unsigned int);
}

template <> void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
    m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_stride += count * sizeof(unsigned char);
}

} // namespace engine
