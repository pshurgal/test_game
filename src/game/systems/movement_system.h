#pragma once

#include <math/vec2.h>

namespace tg
{
    struct Position
    {
        Vec2i value;

        Position() = default;

        Position(const Vec2i& p_val)
            : value(p_val)
        {}
    };

    struct Direction
    {
        Vec2i value;

        Direction() = default;

        Direction(const Vec2i& p_val)
            : value(p_val)
        {}
    };

    class Registry;

    class MovementSystem
    {
    public:
        void update(Registry& p_registry);
    };
}
