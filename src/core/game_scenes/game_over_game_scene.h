#pragma once

// project includes
#include "core/game_scene.h"
#include "core/game_state.h"

namespace core
{
    namespace game_scenes
    {
        class game_over_game_scene : public game_scene
        {
        public:
            explicit game_over_game_scene( bool win = false);

            void render( game_state_p game_state, renderer_p renderer ) override;

        private:
            bool _win = false;
        };
    }
}
