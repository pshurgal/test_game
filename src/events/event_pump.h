#pragma once

#include <events/event.h>
#include <events/event_handler.h>
#include <game/game_state.h>

#include <cstdint>
#include <memory>
#include <unordered_map>

namespace tg
{
    class Game;

    class EventPump
    {
    public:
        explicit EventPump(Game& p_game)
            : m_game(p_game)
        {}

        void pump(GameState& p_state);

    private:
        Game& m_game;
    };
}
