#pragma once

#include <math/vec2.h>

namespace tg
{
    struct Rect
    {
        Vec2i position;
        Vec2i size;

        Rect() = default;
        Rect(const Vec2i& p_position, const Vec2i& p_size)
            : position(p_position)
            , size(p_size)
        {}
    };
}