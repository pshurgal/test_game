#pragma once

#include <math/vec2.h>

namespace tg
{
    class Registry;

    class DespawnSystem
    {
    public:
        DespawnSystem(const Vec2i& p_fieldSize)
            : m_fieldSize(p_fieldSize)
        {}

        void update(Registry& p_registry);

    private:
        Vec2i m_fieldSize;
    };
}
