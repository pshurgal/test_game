#include <game/states/level.h>

#include <algorithm/a_start.h>
#include <events/event.h>
#include <game/game.h>
#include <game/game_state_machine.h>
#include <game/states/game_over.h>
#include <input/keyboard_key.h>
#include <input/mouse_button.h>
#include <utils/raii_guard.h>

#include <array>
#include <cstdint>
#include <random>

using namespace tg;

namespace
{
    std::random_device                          s_randomDevice;
    std::uniform_int_distribution<std::int32_t> s_randomInt(0, 99);

    const Vec2i s_tileFieldSize = { 30, 30 };

    Entity spawnPlayer(Registry& p_registry, const Vec2i& p_position, std::array<Texture, 4> p_textures)
    {
        auto player = p_registry.createEntity();

        p_registry.addComponent<Position>(player, p_position);
        p_registry.addComponent<Direction>(player);
        p_registry.addComponent<Path>(player);
        p_registry.addComponent<Visual>(player, p_textures[0], std::move(p_textures));
        p_registry.addComponent<Health>(player, 1);

        return player;
    }

    Entity sparnGuard(Registry&              p_registry,
                      const Vec2i&           p_position,
                      std::array<Vec2i, 2>   p_patrolPoints,
                      std::array<Texture, 4> p_textures)
    {
        auto guard = p_registry.createEntity();

        p_registry.addComponent<Position>(guard, p_position);
        p_registry.addComponent<Direction>(guard);
        p_registry.addComponent<Path>(guard);
        p_registry.addComponent<Visual>(guard, p_textures[0], std::move(p_textures));
        p_registry.addComponent<Path>(guard);
        p_registry.addComponent<Patrol>(guard, std::move(p_patrolPoints), 1);
        p_registry.addComponent<Damage>(guard, 1);

        return guard;
    }

    Entity spawnTarget(Registry& p_registry, const Vec2i& p_position, std::array<Texture, 4> p_textures)
    {
        auto target = p_registry.createEntity();

        p_registry.addComponent<Position>(target, p_position);
        p_registry.addComponent<Visual>(target, p_textures[0], std::move(p_textures));

        return target;
    }

    Entity spawnSpikedBall(Registry& p_registry, const TileField& p_tileField, std::array<Texture, 4> p_textures)
    {
        Vec2i   direction;
        Vec2i   position;
        Texture startTexture;

        switch (s_randomInt(s_randomDevice) % 4)
        {
        case 0:
            direction = { 0, 1 };
            position = { s_randomInt(s_randomDevice) % p_tileField.size().x, 0 };
            startTexture = p_textures[0];
            break;
        case 1:
            direction = { -1, 0 };
            position = { p_tileField.size().x - 1, s_randomInt(s_randomDevice) % p_tileField.size().y };
            startTexture = p_textures[1];
            break;
        case 2:
            direction = { 0, -1 };
            position = { s_randomInt(s_randomDevice) % p_tileField.size().x, p_tileField.size().y - 1 };
            startTexture = p_textures[2];
            break;
        case 3:
            direction = { 1, 0 };
            position = { 0, s_randomInt(s_randomDevice) % p_tileField.size().x };
            startTexture = p_textures[3];
            break;
        }

        auto entity = p_registry.createEntity();

        p_registry.addComponent<Position>(entity, position);
        p_registry.addComponent<Direction>(entity, direction);
        p_registry.addComponent<Visual>(entity, startTexture, std::move(p_textures));
        p_registry.addComponent<Damage>(entity, 1);

        return entity;
    }
}

LevelGameState::LevelGameState(GameStateMachine& p_stateMachine, Game& p_game)
    : GameState(p_stateMachine, p_game)
    , m_camera(p_game.windowSize() / 2)
    , m_tileField(s_tileFieldSize, p_game.textureManager())
    , m_despawnSystem(s_tileFieldSize)
    , m_patrolSystem([this](const auto& p_from, const auto& p_to) { return findPath(p_from, p_to); })
{
    auto& textureManager = p_game.textureManager();

    m_playerTextures = { textureManager.getTexture("images/player_0"),
                         textureManager.getTexture("images/player_1"),
                         textureManager.getTexture("images/player_2"),
                         textureManager.getTexture("images/player_3") };

    m_guardTextures = { textureManager.getTexture("images/guard_0"),
                        textureManager.getTexture("images/guard_1"),
                        textureManager.getTexture("images/guard_2"),
                        textureManager.getTexture("images/guard_3") };

    m_spikedBallTextures = { textureManager.getTexture("images/spiked_ball_0"),
                             textureManager.getTexture("images/spiked_ball_1"),
                             textureManager.getTexture("images/spiked_ball_2"),
                             textureManager.getTexture("images/spiked_ball_3") };

    m_bedTexture = textureManager.getTexture("images/bed");

    m_bed = spawnTarget(m_registry,
                        { 29, 29 },
                        { m_bedTexture->texture, m_bedTexture->texture, m_bedTexture->texture, m_bedTexture->texture });

    m_player = spawnPlayer(m_registry,
                           { 0, 0 },
                           { m_playerTextures[0]->texture,
                             m_playerTextures[1]->texture,
                             m_playerTextures[2]->texture,
                             m_playerTextures[3]->texture });

    m_guard = sparnGuard(m_registry,
                         { 10, 29 },
                         { Vec2i{ 10, 29 }, Vec2i{ 10, 0 } },
                         { m_guardTextures[0]->texture,
                           m_guardTextures[1]->texture,
                           m_guardTextures[2]->texture,
                           m_guardTextures[3]->texture });

    m_registry.getComponent<Path>(m_guard).value = findPath(Vec2i{ 10, 29 }, Vec2i{ 10, 0 });

    initializeEventHandlers();
}

void LevelGameState::update()
{
    if (isLoss())
    {
        stateMachine().pushState<GameOverGameState>(false);
        return;
    }

    if (isWin())
    {
        stateMachine().pushState<GameOverGameState>(true);
        return;
    }

    m_movementSystem.update(m_registry);
    m_damageSystem.update(m_registry);
    m_despawnSystem.update(m_registry);
    m_visualSystem.update(m_registry);
    m_pathSystem.update(m_registry);
    m_patrolSystem.update(m_registry);

    if (s_randomInt(s_randomDevice) > 70)
    {
        spawnSpikedBall(m_registry,
                        m_tileField,
                        { m_spikedBallTextures[0]->texture,
                          m_spikedBallTextures[1]->texture,
                          m_spikedBallTextures[2]->texture,
                          m_spikedBallTextures[3]->texture });
    }
}

void LevelGameState::render(Canvas& p_canvas)
{
    RAIIGuard m_cameraGuard([this, &p_canvas] { p_canvas.setCamera(&m_camera); },
                            [&p_canvas] { p_canvas.setCamera(nullptr); });

    m_tileField.render(p_canvas);

    struct RenderCommand
    {
        Texture tex;
        Vec2i   coord;

        RenderCommand(Texture p_tex, Vec2i p_coord)
            : tex(p_tex)
            , coord(p_coord)
        {}
    };

    SparseMap<std::size_t, SparseMap<std::size_t, std::list<RenderCommand>>> renderingMatrix;

    auto view = m_registry.view<Position, Visual>();
    for (auto [_, position, visual] : view)
    {
        const auto coord = Vec2i{ 8 + (50 - 8) / 2 * position.value.x - (50 - 8) / 2 * position.value.y,
                                  -30 + (50 - 2) / 4 * position.value.x + (50 - 2) / 4 * position.value.y };

        renderingMatrix[position.value.y][position.value.x].emplace_back(visual.current, coord);
    }

    for (auto& row : renderingMatrix.values())
    {
        for (auto& col : row.values())
        {
            for (auto& elem : col)
            {
                p_canvas.draw(elem.tex, elem.coord);
            }
        }
    }
}

bool LevelGameState::isLoss()
{
    const auto& playerHealth = m_registry.getComponent<Health>(m_player);
    return playerHealth.value == 0;
}

bool LevelGameState::isWin()
{
    const auto& playerPosition = m_registry.getComponent<Position>(m_player);
    const auto& bedPosition = m_registry.getComponent<Position>(m_bed);

    return playerPosition.value == bedPosition.value;
}

std::vector<Vec2i> LevelGameState::findPath(const Vec2i& p_from, const Vec2i p_to)
{
    return AStar::findPath(
        p_from, p_to, [this](const Vec2i& p_coord) { return m_tileField.tileReachable(p_coord.x, p_coord.y); });
}

void LevelGameState::handleMouseButton(EMouseButton p_button, const Vec2i& p_clickPoint)
{
    if (p_button == EMouseButton::LEFT)
    {
        auto point = m_camera.screenToSpace(p_clickPoint);
        auto tile = m_tileField.clickPoint(point.x, point.y);

        if (!tile)
        {
            return;
        }

        m_playerDestinationPoint = tile->fieldPos();
    }
    else if (p_button == EMouseButton::RIGHT)
    {
        auto point = m_camera.screenToSpace(p_clickPoint);
        auto tile = m_tileField.clickPoint(point.x, point.y);

        if (!tile)
        {
            return;
        }

        tile->switchState();

        auto [position, path, patrol] = m_registry.getComponents<Position, Path, Patrol>(m_guard);
        path.value = findPath(position.value, patrol.points[patrol.destination]);
    }

    auto [position, path] = m_registry.getComponents<Position, Path>(m_player);
    path.value = findPath(position.value, m_playerDestinationPoint);
}

void LevelGameState::handleKeyboardKey(EKeyboardKey p_key)
{
    Vec2i offset;

    if (p_key == EKeyboardKey::ARROW_RIGHT)
    {
        offset.x = -10;
    }
    else if (p_key == EKeyboardKey::ARROW_LEFT)
    {
        offset.x = 10;
    }
    else if (p_key == EKeyboardKey::ARROW_UP)
    {
        offset.y = 10;
    }
    else if (p_key == EKeyboardKey::ARROW_DOWN)
    {
        offset.y = -10;
    }
    else if (p_key == EKeyboardKey::ESC)
    {
        game().shutdown();
    }

    m_camera.move(offset);
}

void LevelGameState::initializeEventHandlers()
{
    addEventHandler<MouseButton>(
        [this](const MouseButton& p_event) { handleMouseButton(p_event.button, p_event.clickPoint); });

    addEventHandler<KeyboardKey>([this](const KeyboardKey& p_event) { handleKeyboardKey(p_event.key); });
}
