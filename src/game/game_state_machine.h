#pragma once

#include <game/game_state.h>

#include <memory>
#include <type_traits>

namespace tg
{
    class Game;

    class GameStateMachine
    {
    public:
        explicit GameStateMachine(Game& p_game)
            : m_game(p_game)
        {}

        template<typename StateType, typename... Args>
        void pushState(Args... p_args)
        {
            static_assert(std::is_base_of<GameState, StateType>::value,
                          "The type 'StateType' must be a child of GameState");
            pushStateImpl(std::make_unique<StateType>(*this, m_game, std::forward<Args>(p_args)...));
        }

        GameState& currentState() { return *m_currentState; };

    private:
        void pushStateImpl(std::unique_ptr<GameState> p_state);

    private:
        Game& m_game;

        std::unique_ptr<GameState> m_currentState;
        std::unique_ptr<GameState> m_prevState;
    };
}
