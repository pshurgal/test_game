#pragma once

// project includes
#include "game_state.h"
#include "sdl_types.h"

namespace core
{
    class drawable
    {
      public:
        virtual void render(game_state_p game_state, renderer_p renderer) = 0;
    };
}