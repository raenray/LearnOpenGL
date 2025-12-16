#include <engine/Camera2D.h>

#include <glm/gtc/matrix_transform.hpp>

namespace engine
{

Camera2D::Camera2D(float left, float right, float bottom, float top)
{
    m_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    recalc();
}

void Camera2D::setPosition(const glm::vec2& pos)
{
    m_position = pos;
    recalc();
}

void Camera2D::setZoom(float zoom)
{
    m_zoom = zoom;
    recalc();
}

void Camera2D::move(const glm::vec2& delta)
{
    m_position += delta;
    recalc();
}

void Camera2D::zoom(float delta)
{
    m_zoom += delta;
    if (m_zoom < 0.1f)
        m_zoom = 0.1f;
    recalc();
}

const glm::mat4& Camera2D::viewProjection() const
{
    return m_viewProjection;
}

void Camera2D::recalc()
{
    m_view = glm::translate(glm::mat4(1.0f), glm::vec3(-m_position, 0.0f));
    m_view = glm::scale(m_view, glm::vec3(m_zoom, m_zoom, 1.0f));

    m_viewProjection = m_projection * m_view;
}

} // namespace engine
