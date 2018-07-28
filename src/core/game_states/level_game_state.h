#pragma once

// project includes
#include <core/gameplay/player.h>
#include "core/game_state.h"
#include "core/gameplay/camera.h"
#include "core/gameplay/cell_field.h"

// STL includes
#include <list>

namespace core
{
    namespace game_states
    {
        class level_game_state : public game_state
        {
        public:
            void update() override;

            gameplay::camera camera;
            gameplay::cell_field_p cell_field;
            gameplay::player_p player;

            std::list<math::vec2> player_path;
        };
    }
}



