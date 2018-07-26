#pragma once

// project includes
#include "core/game_scene.h"
#include "core/game_state.h"

namespace core
{
    namespace game_scenes
    {
        class sample_game_scene : public game_scene
        {
        public:
            sample_game_scene( renderer_p renderer );

            void render( game_state_p game_state, renderer_p renderer  );
        };
    }
}
