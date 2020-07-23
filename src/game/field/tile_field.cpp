#include <game/field/tile_field.h>

#include <cstdint>

using namespace tg;

TileField::TileField(const Vec2i& p_size, TextureManager& p_textureManager)
    : m_size(p_size)
{
    m_grassTexture = p_textureManager.getTexture("images/ground_tile");
    m_lavaTexture = p_textureManager.getTexture("images/lava_tile");

    m_tiles.reserve(m_size.x);
    for (std::int32_t i = 0; i < m_size.x; ++i)
    {
        auto& col = m_tiles.emplace_back();
        col.reserve(m_size.y);
        for (std::int32_t j = 0; j < m_size.y; ++j)
        {
            col.emplace_back(Vec2i{ i, j }, Tile::EState::GRASS, m_grassTexture->texture, m_lavaTexture->texture);
        }
    }
}

void TileField::render(Canvas& p_canvas) const
{
    for (const auto& col : m_tiles)
    {
        for (const auto& tile : col)
        {
            tile.render(p_canvas);
        }
    }
}

const Tile* tg::TileField::tile(std::int32_t p_x, std::int32_t p_y) const
{
    if (p_x < 0 || p_x >= m_size.x || p_y < 0 || p_y >= m_size.y)
    {
        return nullptr;
    }

    return &(m_tiles[p_x][p_y]);
}

Tile* TileField::tile(std::int32_t p_x, std::int32_t p_y)
{
    if (p_x < 0 || p_x >= m_size.x || p_y < 0 || p_y >= m_size.y)
    {
        return nullptr;
    }

    return &(m_tiles[p_x][p_y]);
}

bool TileField::tileReachable(std::int32_t p_x, std::int32_t p_y) const
{
    auto t = tile(p_x, p_y);
    return t && t->reachable();
}

Tile* TileField::clickPoint(std::int32_t p_x, std::int32_t p_y)
{
    for (auto& col : m_tiles)
    {
        for (auto& tile : col)
        {
            if (tile.isClicked(p_x, p_y))
            {
                return &tile;
            }
        }
    }

    return nullptr;
}
