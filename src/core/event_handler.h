#pragma once

// project includes
#include "game_state.h"

// thirdparty includes
#include "SDL2/SDL_events.h"

// STL includes
#include <functional>

namespace core
{
    typedef std::function<void(SDL_Event& e, game_state_p state)> event_handler;
}
