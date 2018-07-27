#pragma once

// project includes
#include <core/gameplay/player.h>
#include "core/game_scene.h"
#include "core/game_state.h"
#include "core/gameplay/tile_field.h"

namespace core
{
    namespace game_scenes
    {
        class level_game_scene : public game_scene
        {
        public:
            level_game_scene( renderer_p renderer );

            void render( game_state_p game_state, renderer_p renderer  );

            gameplay::tile_field_p tile_field;
            gameplay::player_p player;
        };
    }
}



