#pragma once

#include <rendering/texture.h>

#include <array>

namespace tg
{
    struct Visual
    {
        Texture                current;
        std::array<Texture, 4> textures;

        Visual() = default;

        Visual(Texture p_current, std::array<Texture, 4> p_textures)
            : current(p_current)
            , textures(std::move(p_textures))
        {}
    };

    class Registry;

    class VisualSystem
    {
    public:
        void update(Registry& p_registry);
    };
}
