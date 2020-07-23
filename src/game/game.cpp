#include <game/game.h>

#include <game/states/level.h>
#include <rendering/canvas.h>

#include <vector>

using namespace tg;

namespace
{
    const auto s_windowSize = Vec2i{ 1024, 768 };
}

Game::Game()
    : m_eventPump(*this)
    , m_renderingBackend()
    , m_textureManager(m_renderingBackend)
    , m_stateMachine(*this)
{}

int Game::exec()
{
    if (!m_renderingBackend.initialize("Test Game", s_windowSize))
    {
        return -1;
    }

    m_stateMachine.pushState<LevelGameState>();

    Canvas canvas(m_renderingBackend);

    while (!m_shutdown)
    {
        auto& state = m_stateMachine.currentState();

        m_eventPump.pump(state);

        using namespace std::chrono;

        const auto now = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
        const auto elapsed = now - m_lastUpdateTime;

        if (elapsed >= 500ms)
        {
            state.update();
            m_lastUpdateTime = now;
        }

        canvas.begin();

        state.render(canvas);

        canvas.end();
    }

    return 0;
}

void Game::shutdown()
{
    m_shutdown = true;
}

const Vec2i& Game::windowSize() const
{
    return s_windowSize;
}
