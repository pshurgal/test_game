#pragma once

#include <math/vec2.h>
#include <rendering/canvas.h>
#include <resources/texture_manager.h>

#include <cstdint>
#include <string>

namespace tg
{
    class Tile
    {
    public:
        enum class EState
        {
            GRASS,
            LAVA,
            EMPTY
        };

    public:
        Tile(Vec2i p_fieldpos, EState p_state, Texture p_grassTexture, Texture p_lavaTexture);

        void render(Canvas& p_canvas) const;

        bool isClicked(std::int32_t p_x, std::int32_t p_y) const;

        bool reachable() const;

        Vec2i fieldPos() const { return m_fieldPos; }

        void switchState();

    private:
        void update();

    private:
        Vec2i m_fieldPos;
        Vec2i m_worldPos;

        EState m_state;

        Texture m_grassTexture;
        Texture m_lavaTexture;
        Texture m_currentTexture;
    };
}
