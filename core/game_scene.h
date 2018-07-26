#pragma once

// project includes
#include "sdl_types.h"
#include "game_state.h"

// STL includes
#include <memory>

namespace core
{
    class game_scene
    {
    public:
        virtual void render( game_state_p game_state, renderer_p renderer ) = 0;
    };

    typedef std::shared_ptr<game_scene> game_scene_p;
}
