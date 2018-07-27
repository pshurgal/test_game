#pragma once

// project includes
#include "core/sdl_types.h"
#include "core/game_state.h"

namespace core
{
    class drawable
    {
    public:
        virtual void render( game_state_p game_state, renderer_p renderer ) = 0;
    };
}