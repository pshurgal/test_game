#pragma once

// project includes
#include "core/event_handler.h"
#include "core/game_state.h"
#include "core/gameplay/camera.h"
#include "core/gameplay/tile_field.h"
#include "core/gameplay/unit.h"

// STL includes
#include <chrono>
#include <list>
#include <map>

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

            std::list<gameplay::unit_p> boulder_spikes;

            static const core::event_handler mouse_button_up_handler;

            static const core::event_handler key_up_handler;

          private:
            void create_random_boulder_spike();

            bool is_game_over();
            bool is_win();

          private:
            std::list<gameplay::direction_e> _guard_path;
            std::list<gameplay::direction_e> _player_path;

            math::vec2 _guard_point_1 = {10, 29};
            math::vec2 _guard_point_2 = {15, 0};
            math::vec2 _guard_point_current = _guard_point_2;

            std::chrono::high_resolution_clock::time_point last_units_update_time =
                std::chrono::high_resolution_clock::now();
            std::chrono::high_resolution_clock::time_point last_boulder_spikes_update_time =
                std::chrono::high_resolution_clock::now();
        };
    }
}
