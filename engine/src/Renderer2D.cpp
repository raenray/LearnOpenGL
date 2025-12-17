#include <engine/Renderer2D.h>
#include <engine/Shader.h>
#include <engine/Texture.h>
#include <engine/Camera2D.h>
#include <engine/Sprite.h>

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <cstring>

namespace engine
{

Renderer2D::Renderer2D(Shader& shader)
    : m_shader(shader)
{
}

Renderer2D::~Renderer2D()
{
    shutdown();
}

void Renderer2D::init()
{
    // VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // VBO
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, MaxVertices * sizeof(QuadVertex), nullptr, GL_DYNAMIC_DRAW);

    // IBO
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    uint32_t indices[MaxIndices];
    uint32_t offset = 0;
    for (uint32_t i = 0; i < MaxIndices; i += 6)
    {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;

        offset += 4;
    }

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Vertex layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, pos));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, color));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, uv));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, texIndex));

    // CPU buffer
    m_vertexBuffer = new QuadVertex[MaxVertices];

    // White texture (slot 0)
    uint32_t white = 0xffffffff;
    m_whiteTexture = std::make_unique<Texture>(1, 1, &white);
    m_textureSlots[0] = m_whiteTexture.get();

    // Sampler array
    int samplers[MaxTextureSlots];
    for (int i = 0; i < MaxTextureSlots; i++)
        samplers[i] = i;

    m_shader.bind();
    m_shader.setIntArray("u_Textures", samplers, MaxTextureSlots);
}

void Renderer2D::shutdown()
{
    delete[] m_vertexBuffer;
    m_vertexBuffer = nullptr;

    glDeleteBuffers(1, &m_ibo);
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

void Renderer2D::begin(const Camera2D& camera)
{
    m_indexCount = 0;
    m_vertexPtr = m_vertexBuffer;
    m_textureSlotIndex = 1;

    m_shader.bind();
    m_shader.setMat4("u_ViewProjection", camera.viewProjection());
}

void Renderer2D::drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, Texture* texture)
{
    if (m_indexCount >= MaxIndices)
        return;

    float texIndex = 0.0f;

    if (texture)
    {
        for (uint32_t i = 1; i < m_textureSlotIndex; i++)
        {
            if (m_textureSlots[i]->getID() == texture->getID())
            {
                texIndex = (float)i;
                break;
            }
        }

        if (texIndex == 0.0f)
        {
            if (m_textureSlotIndex >= MaxTextureSlots)
            {
                end();
                flush();
                return;
            }

            texIndex = (float)m_textureSlotIndex;
            m_textureSlots[m_textureSlotIndex] = texture;
            m_textureSlotIndex++;
        }
    }

    // clang-format off
    glm::vec3 p0 = {pos.x,          pos.y,          0.0f};
    glm::vec3 p1 = {pos.x + size.x, pos.y,          0.0f};
    glm::vec3 p2 = {pos.x + size.x, pos.y + size.y, 0.0f};
    glm::vec3 p3 = {pos.x,          pos.y + size.y, 0.0f};
    // clang-format on

    m_vertexPtr->pos = p0;
    m_vertexPtr->color = color;
    m_vertexPtr->uv = {0.0f, 0.0f};
    m_vertexPtr->texIndex = texIndex;
    m_vertexPtr++;

    m_vertexPtr->pos = p1;
    m_vertexPtr->color = color;
    m_vertexPtr->uv = {1.0f, 0.0f};
    m_vertexPtr->texIndex = texIndex;
    m_vertexPtr++;

    m_vertexPtr->pos = p2;
    m_vertexPtr->color = color;
    m_vertexPtr->uv = {1.0f, 1.0f};
    m_vertexPtr->texIndex = texIndex;
    m_vertexPtr++;

    m_vertexPtr->pos = p3;
    m_vertexPtr->color = color;
    m_vertexPtr->uv = {0.0f, 1.0f};
    m_vertexPtr->texIndex = texIndex;
    m_vertexPtr++;

    m_indexCount += 6;
}

void Renderer2D::drawSprite(const glm::vec2& pos, const glm::vec2& size, const Sprite& sprite, const glm::vec4& color)
{
    drawQuadInternal(pos, size, sprite.uvMin, sprite.uvMax, color, sprite.texture);
}

void Renderer2D::end()
{
    GLsizeiptr size = (uint8_t*)m_vertexPtr - (uint8_t*)m_vertexBuffer;

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_vertexBuffer);
}

void Renderer2D::flush()
{
    for (uint32_t i = 0; i < m_textureSlotIndex; i++)
        m_textureSlots[i]->bind(i);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
}

float Renderer2D::resolveTextureIndex(Texture* texture)
{
    for (uint32_t i = 1; i < m_textureSlotIndex; i++)
    {
        if (*m_textureSlots[i] == *texture)
            return (float)i;
    }

    if (m_textureSlotIndex >= MaxTextureSlots)
    {
        return -1.0f;
    }

    m_textureSlots[m_textureSlotIndex] = texture;
    return (float)m_textureSlotIndex++;
}

void Renderer2D::drawQuadInternal(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& uvMin, const glm::vec2& uvMax, const glm::vec4& color, Texture* texture)
{
    float texIndex = resolveTextureIndex(texture);

    if (texIndex < 0.0f)
    {
        return;
    }

    QuadVertex* v = m_vertexPtr;

    v[0] = {{pos.x, pos.y, 0}, color, {uvMin.x, uvMin.y}, texIndex};
    v[1] = {{pos.x + size.x, pos.y, 0}, color, {uvMax.x, uvMin.y}, texIndex};
    v[2] = {{pos.x + size.x, pos.y + size.y, 0}, color, {uvMax.x, uvMax.y}, texIndex};
    v[3] = {{pos.x, pos.y + size.y, 0}, color, {uvMin.x, uvMax.y}, texIndex};

    m_vertexPtr += 4;
    m_indexCount += 6;
}

} // namespace engine
