#pragma once

// project includes
#include "core/game_scene.h"
#include "core/game_state.h"
#include "core/gameplay/tile_field.h"
#include <core/gameplay/unit.h>

namespace core
{
    namespace game_scenes
    {
        class level_game_scene : public game_scene
        {
          public:
            void render(game_state_p game_state, renderer_p renderer) override;
        };
    }
}
