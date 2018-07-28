#pragma once

// project includes
#include <core/gameplay/player.h>
#include "core/game_state.h"
#include "core/gameplay/camera.h"
#include "core/gameplay/cell_field.h"

// STL includes
#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>

namespace core
{
    namespace game_states
    {
        class level_game_state : public game_state
        {
        public:
            void update() override;

            void start_update_units();
            void stop_update_units();

            gameplay::camera camera;
            gameplay::cell_field_p cell_field;
            gameplay::player_p player;

            void set_player_path( std::list<gameplay::direction_e> );

        private:
            void update_units_loop();

            bool _shutdown_signalled = false;
            std::thread _units_updater_thread;
            std::mutex _m;
            std::list<gameplay::direction_e> player_path;
        };
    }
}



