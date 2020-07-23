#include <rendering/camera.h>

using namespace tg;

void Camera::move(const Vec2i& p_offset)
{
    m_pos += p_offset;
}

Vec2i tg::Camera::screenToSpace(const Vec2i& p_val) const
{
    return p_val - m_pos;
}
