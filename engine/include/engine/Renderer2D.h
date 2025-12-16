#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <cstdint>

namespace engine
{

class Shader;
class Texture;
class Camera2D;
class Sprite;

class Renderer2D final
{
public:
public:
    explicit Renderer2D(Shader& shader);
    ~Renderer2D();

    void init();
    void shutdown();

    void begin(const Camera2D& camera);
    void drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color = {1, 1, 1, 1}, Texture* texture = nullptr);
    void drawSprite(const glm::vec2& pos, const glm::vec2& size, const Sprite& sprite, const glm::vec4& tint = {1, 1, 1, 1});

    void end();
    void flush();

private:
    struct QuadVertex
    {
        glm::vec3 pos;
        glm::vec4 color;
        glm::vec2 uv;
        float texIndex;
    };

private:
    static constexpr uint32_t MaxQuads = 1000;
    static constexpr uint32_t MaxVertices = MaxQuads * 4;
    static constexpr uint32_t MaxIndices = MaxQuads * 6;
    static constexpr uint32_t MaxTextureSlots = 16;

private:
    void drawQuadInternal(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& uvMin, const glm::vec2& uvMax, const glm::vec4& color, Texture* texture);

    float resolveTextureIndex(Texture* texture);

private:
    Shader& m_shader;

    uint32_t m_vao = 0;
    uint32_t m_vbo = 0;
    uint32_t m_ibo = 0;

    uint32_t m_indexCount = 0;

    QuadVertex* m_vertexBuffer = nullptr;
    QuadVertex* m_vertexPtr = nullptr;

    Texture* m_textureSlots[MaxTextureSlots]{};
    uint32_t m_textureSlotIndex = 1;

    std::unique_ptr<Texture> m_whiteTexture;
};

} // namespace engine
