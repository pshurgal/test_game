#include <game/game_state_machine.h>

using namespace tg;

void GameStateMachine::pushStateImpl(std::unique_ptr<GameState> p_state)
{
    m_prevState = std::move(m_currentState);
    m_currentState = std::move(p_state);
}
