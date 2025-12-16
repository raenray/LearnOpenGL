#pragma once

#include <engine/VertexArray.h>
#include <engine/IndexBuffer.h>

namespace engine
{

class Renderer
{
public:
    void clear() const;
    void draw(const VertexArray& vao, const IndexBuffer& ib) const;
};

} // namespace engine
