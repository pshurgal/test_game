#include <rendering/canvas.h>

using namespace tg;

void Canvas::draw(Texture p_tex, const Vec2i& p_position)
{
    if (m_camera)
    {
        m_backend.draw(p_tex, { m_camera->position() + p_position, { -1, -1 } });
    }
    else
    {
        m_backend.draw(p_tex, { p_position, { -1, -1 } });
    }
}

void Canvas::draw(Texture p_tex, const Rect& p_rect)
{
    if (m_camera)
    {
        m_backend.draw(p_tex, { m_camera->position() + p_rect.position, p_rect.size });
    }
    else
    {
        m_backend.draw(p_tex, p_rect);
    }
}

void Canvas::begin()
{
    m_backend.clear();
}

void Canvas::end()
{
    m_backend.present();
}
