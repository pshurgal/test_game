#pragma once

#include <cstdint>

namespace tg
{
    struct Health
    {
        std::uint32_t value;

        Health() = default;

        Health(std::uint32_t p_val)
            : value(p_val)
        {}
    };

    struct Damage
    {
        std::uint32_t value;

        Damage() = default;

        Damage(std::uint32_t p_val)
            : value(p_val)
        {}
    };

    class Registry;

    class DamageSystem
    {
    public:
        void update(Registry& p_registry);
    };
}
