#pragma once

#include <glm/glm.hpp>

namespace engine
{

class Texture;

struct Sprite
{
    Texture* texture = nullptr;
    glm::vec2 uvMin{0.0f, 0.0f};
    glm::vec2 uvMax{1.0f, 1.0f};
};

} // namespace engine
