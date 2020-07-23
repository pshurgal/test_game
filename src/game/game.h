#pragma once

#include <events/event_pump.h>
#include <game/game_state_machine.h>
#include <math/vec2.h>
#include <rendering/rendering_backend.h>
#include <resources/texture_manager.h>

#include <chrono>
#include <cstddef>
#include <memory>

namespace tg
{
    class Game
    {
    public:
        Game();

        int  exec();
        void shutdown();

        TextureManager& textureManager() { return m_textureManager; };

        const Vec2i& windowSize() const;

    private:
        EventPump        m_eventPump;
        RenderingBackend m_renderingBackend;
        TextureManager   m_textureManager;
        GameStateMachine m_stateMachine;

        std::chrono::milliseconds m_lastUpdateTime;

        bool m_shutdown = false;
    };
}
