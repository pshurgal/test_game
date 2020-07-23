#include <game/field/tile.h>

using namespace tg;

Tile::Tile(Vec2i p_fieldPos, EState p_state, Texture p_grassTexture, Texture p_lavaTexture)
    : m_fieldPos(p_fieldPos)
    , m_worldPos((50 - 8) / 2 * p_fieldPos.x - (50 - 8) / 2 * p_fieldPos.y,
                 (50 - 2) / 4 * p_fieldPos.x + (50 - 2) / 4 * p_fieldPos.y)
    , m_state(p_state)
    , m_grassTexture(p_grassTexture)
    , m_lavaTexture(p_lavaTexture)
{
    update();
}

void Tile::render(Canvas& p_canvas) const
{
    if (m_state == EState::EMPTY)
    {
        return;
    }

    p_canvas.draw(m_currentTexture, m_worldPos);
}

bool Tile::isClicked(std::int32_t p_x, std::int32_t p_y) const
{
    Vec2i a = { m_worldPos.x + 4, m_worldPos.y + 1 + (50 - 2) / 4 };
    Vec2i b = { m_worldPos.x + 4 + (50 - 8) / 2, m_worldPos.y + 1 };
    Vec2i c = { m_worldPos.x + 4 + (50 - 8), m_worldPos.y + 1 + (50 - 2) / 4 };
    Vec2i d = { m_worldPos.x + 4 + (50 - 8) / 2, m_worldPos.y + 1 + (50 - 2) / 2 };

    Vec2i point = { p_x, p_y };

    return b.cross(a, point) >= 0 && c.cross(d, point) <= 0 && d.cross(a, point) <= 0 && c.cross(b, point) >= 0;
}

bool Tile::reachable() const
{
    return m_state == EState::GRASS;
}

void Tile::switchState()
{
    switch (m_state)
    {
    case EState::GRASS:
        m_state = EState::LAVA;
        break;

    case EState::LAVA:
        m_state = EState::EMPTY;
        break;

    case EState::EMPTY:
        [[fallthrough]];

    default:
        m_state = EState::GRASS;
        break;
    }

    update();
}

void Tile::update()
{
    switch (m_state)
    {
    case EState::GRASS:
        m_currentTexture = m_grassTexture;
        break;

    case EState::LAVA:
        m_currentTexture = m_lavaTexture;
        break;

    case EState::EMPTY:
        [[fallthrough]];

    default:
        m_currentTexture = Texture::INVALID;
        break;
    }
}
