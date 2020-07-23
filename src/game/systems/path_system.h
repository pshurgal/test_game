#pragma once

#include <math/vec2.h>

#include <vector>

namespace tg
{
    struct Path
    {
        std::vector<Vec2i> value;

        Path() = default;

        Path(const std::vector<Vec2i>& p_val)
            : value(p_val)
        {}
    };

    class Registry;

    class PathSystem
    {
    public:
        void update(Registry& p_registry);
    };
}
