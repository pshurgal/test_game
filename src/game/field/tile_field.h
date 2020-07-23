#pragma once

#include <game/field/tile.h>
#include <math/vec2.h>
#include <rendering/canvas.h>
#include <resources/texture_manager.h>

#include <cstdint>
#include <memory>
#include <vector>

namespace tg
{
    class TileField
    {
    public:
        TileField(const Vec2i& p_size, TextureManager& p_textureManager);

        void render(Canvas& p_canvas) const;

        const Tile* tile(std::int32_t p_x, std::int32_t p_y) const;
        Tile*       tile(std::int32_t p_x, std::int32_t p_y);

        const Vec2i& size() const { return m_size; }

        bool tileReachable(std::int32_t p_x, std::int32_t p_y) const;

        Tile* clickPoint(std::int32_t p_x, std::int32_t p_y);

    private:
        Vec2i                          m_size;
        std::vector<std::vector<Tile>> m_tiles;

        TextureManager::Token m_grassTexture;
        TextureManager::Token m_lavaTexture;
    };
}
