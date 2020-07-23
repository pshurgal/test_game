#include <events/event_pump.h>

#include <game/game.h>

#include <SDL_events.h>

#include <functional>
#include <optional>

using namespace tg;

namespace
{
    void processMouseEvent(const SDL_Event& p_event, GameState& p_state)
    {
        std::optional<MouseButton> event;
        if (p_event.button.button == SDL_BUTTON_LEFT)
        {
            event = { EMouseButton::LEFT, Vec2i{ p_event.button.x, p_event.button.y } };
        }
        else if (p_event.button.button == SDL_BUTTON_RIGHT)
        {
            event = { EMouseButton::RIGHT, Vec2i{ p_event.button.x, p_event.button.y } };
        }

        if (!event)
        {
            return;
        }

        p_state.handleEvent(*event);
    }

    void processKeyboardEvent(const SDL_Event& p_event, GameState& p_state)
    {
        std::optional<KeyboardKey> event;
        if (p_event.key.keysym.sym == SDLK_RIGHT)
        {
            event = { EKeyboardKey::ARROW_RIGHT };
        }
        else if (p_event.key.keysym.sym == SDLK_LEFT)
        {
            event = { EKeyboardKey::ARROW_LEFT };
        }
        else if (p_event.key.keysym.sym == SDLK_UP)
        {
            event = { EKeyboardKey::ARROW_UP };
        }
        else if (p_event.key.keysym.sym == SDLK_DOWN)
        {
            event = { EKeyboardKey::ARROW_DOWN };
        }
        else if (p_event.key.keysym.sym == SDLK_ESCAPE)
        {
            event = { EKeyboardKey::ESC };
        }
        else
        {
            event = { EKeyboardKey::UNKNOWN };
        }

        if (!event)
        {
            return;
        }

        p_state.handleEvent(*event);
    }
}

void EventPump::pump(GameState& p_state)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            m_game.shutdown();
        }
        else
        {
            switch (e.type)
            {
            case SDL_MOUSEBUTTONUP:
                processMouseEvent(e, p_state);
                break;

            case SDL_KEYUP:
                processKeyboardEvent(e, p_state);
                break;
            }
        }
    }
}
