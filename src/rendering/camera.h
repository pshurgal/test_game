#pragma once

#include <math/vec2.h>

#include <cstdint>

namespace tg
{
    class Camera
    {
    public:
        Camera() = default;
        explicit Camera(const Vec2i& p_pos)
            : m_pos(p_pos)
        {}

        std::int32_t x() const { return m_pos.x; }
        std::int32_t y() const { return m_pos.y; }

        const Vec2i& position() const { return m_pos; }

        void move(const Vec2i& p_offset);

        Vec2i screenToSpace(const Vec2i& p_val) const;

    private:
        Vec2i m_pos;
    };
}
