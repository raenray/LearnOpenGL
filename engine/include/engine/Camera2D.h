#pragma once

#include <glm/glm.hpp>

namespace engine
{

class Camera2D
{
public:
    Camera2D(float left, float right, float bottom, float top);

    void setPosition(const glm::vec2& pos);
    void setZoom(float zoom);
    void move(const glm::vec2& delta);
    void zoom(float delta);


    const glm::mat4& viewProjection() const;

private:
    void recalc();

private:
    glm::mat4 m_projection{};
    glm::mat4 m_view{};
    glm::mat4 m_viewProjection{};

    glm::vec2 m_position{0.0f, 0.0f};
    float m_zoom{1.0f};
};

} // namespace engine
