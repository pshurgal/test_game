#include <game/game_state.h>

using namespace tg;

void GameState::addEventHandlerImpl(std::type_index p_type, EventHandler<Event> p_handler)
{
    m_eventHandlers.emplace(p_type, std::move(p_handler));
}

void GameState::handleEventImpl(std::type_index p_type, const Event& p_event)
{
    auto it = m_eventHandlers.find(p_type);
    if (it == m_eventHandlers.end())
    {
        return;
    }

    it->second(p_event);
}
