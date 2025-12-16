#include <engine/Renderer.h>
#include <glad/gl.h>

namespace engine
{

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& vao, const IndexBuffer& ib) const
{
    vao.bind();
    ib.bind();
    glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr);
}

} // namespace engine
