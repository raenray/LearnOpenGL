#include <engine/TextureAtlas.h>

namespace engine
{

TextureAtlas::TextureAtlas(Texture* texture, uint32_t w, uint32_t h)
    : m_texture(texture)
    , m_invW(1.0f / w)
    , m_invH(1.0f / h)
{
}

glm::vec2 TextureAtlas::uvMin(uint32_t x, uint32_t y) const
{
    return {x * m_invW, y * m_invH};
}

glm::vec2 TextureAtlas::uvMax(uint32_t x, uint32_t y, uint32_t w, uint32_t h) const
{
    return {(x + w) * m_invW, (y + h) * m_invH};
}

} // namespace engine
