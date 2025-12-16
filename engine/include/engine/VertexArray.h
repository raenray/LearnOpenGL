#pragma once

#include <engine/VertexBuffer.h>
#include <engine/VertexBufferLayout.h>

namespace engine
{

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void bind() const;
    void unbind() const;

    // private:
    unsigned int m_id{};
};

} // namespace engine
