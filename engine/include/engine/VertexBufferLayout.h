#pragma once

#include <vector>

namespace engine
{

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
};

class VertexBufferLayout
{
public:
    VertexBufferLayout() = default;

    template <typename T> void push(unsigned int count);

    inline const std::vector<VertexBufferElement>& elements() const { return m_elements; }

    inline unsigned int stride() const { return m_stride; }

private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride = 0;
};

} // namespace engine
