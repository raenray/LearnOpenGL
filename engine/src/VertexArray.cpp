#include <engine/VertexArray.h>
#include <glad/gl.h>

#include <iostream>

namespace engine
{

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    bind();
    vb.bind();

    const auto& elements = layout.elements();
    unsigned int offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& e = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.stride(), (const void*)(uintptr_t)offset);
        offset += e.count * (e.type == GL_FLOAT ? sizeof(float) : e.type == GL_UNSIGNED_INT ? sizeof(unsigned int) : sizeof(unsigned char));
    }
}

} // namespace engine
