#pragma once

#include <glm/glm.hpp>

namespace engine
{

class Texture;

class TextureAtlas
{
public:
    TextureAtlas(Texture* texture, uint32_t atlasWidth, uint32_t atlasHeight);

    glm::vec2 uvMin(uint32_t x, uint32_t y, uint32_t w, uint32_t h) const;
    glm::vec2 uvMax(uint32_t x, uint32_t y, uint32_t w, uint32_t h) const;

    Texture* texture() const { return m_texture; }

private:
    Texture* m_texture;
    float m_invW;
    float m_invH;
};

} // namespace engine
