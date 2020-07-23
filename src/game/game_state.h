#pragma once

#include <events/event.h>
#include <events/event_handler.h>
#include <rendering/canvas.h>

#include <memory>
#include <type_traits>
#include <typeindex>
#include <unordered_map>

namespace tg
{
    class Game;
    class GameStateMachine;

    class GameState
    {
    public:
        explicit GameState(GameStateMachine& p_stateMachine, Game& p_game)
            : m_gameStateMachine(p_stateMachine)
            , m_game(p_game)
        {}

        virtual ~GameState() = default;

        virtual void update() = 0;
        virtual void render(Canvas& p_canvas) = 0;

        template<typename EventType>
        void addEventHandler(EventHandler<EventType> p_handler)
        {
            static_assert(std::is_base_of<Event, EventType>::value,
                          "The type 'EventType' must be inherited from Event type!");
            addEventHandlerImpl(typeid(EventType), [handler = std::move(p_handler)](const Event& p_event) {
                handler(static_cast<const EventType&>(p_event));
            });
        }

        template<typename EventType>
        void handleEvent(const EventType& p_event)
        {
            static_assert(std::is_base_of<Event, EventType>::value,
                          "The type 'EventType' must be inherited from Event type!");
            handleEventImpl(typeid(EventType), p_event);
        }

    protected:
        GameStateMachine& stateMachine() { return m_gameStateMachine; }
        Game&             game() { return m_game; }

    private:
        void addEventHandlerImpl(std::type_index p_type, EventHandler<Event> p_handler);
        void handleEventImpl(std::type_index p_type, const Event& p_event);

    private:
        GameStateMachine& m_gameStateMachine;
        Game&             m_game;

        std::unordered_map<std::type_index, EventHandler<Event>> m_eventHandlers;
    };
}
