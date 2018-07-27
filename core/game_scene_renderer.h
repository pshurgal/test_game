#pragma once

// project includes
#include "game_scene.h"
#include "sdl_types.h"
#include "drawable.h"

// STL includes
#include <functional>
#include <memory>

namespace core
{
    class game_scene_renderer
    {
    public:
        game_scene_renderer();

        void set_renderer( renderer_p renderer );

        void render( game_scene_p scene, game_state_p game_state );

    private:
        renderer_p _renderer;
    };
}
