#pragma once

// project includes
#include "core/gameplay/unit.h"
#include "core/game_state.h"
#include "core/gameplay/camera.h"
#include "core/event_handler.h"
#include "core/gameplay/tile_field.h"

// STL includes
#include <list>
#include <map>
#include <chrono>

namespace core
{
    namespace game_states
    {
        class level_game_state : public game_state
        {
        public:
            level_game_state();

            void update() override;

            gameplay::tile_field_p tile_field;

            gameplay::unit_p player;

            gameplay::unit_p guard;

            gameplay::unit_p bed;

            static const core::event_handler mouse_button_up_handler;

        private:
            bool is_game_over();
            bool is_win();

        private:
            std::list<gameplay::direction_e> _guard_path;
            std::list<gameplay::direction_e> _player_path;

            math::vec2 _guard_point_1 = {10,29};
            math::vec2 _guard_point_2 = {15, 0};
            math::vec2 _guard_point_current = _guard_point_2;

            std::chrono::high_resolution_clock::time_point last_update_time = std::chrono::high_resolution_clock::now();;
        };
    }
}



