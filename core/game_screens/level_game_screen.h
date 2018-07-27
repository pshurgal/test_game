#pragma once


// project includes
#include "core/sdl_types.h"
#include "core/game_screen.h"

namespace core
{
    namespace game_screens
    {
        class level_game_screen: public game_screen
        {
        public:
            level_game_screen( renderer_p renderer );

            void on_enter();

            void on_leave();

            void initialize_event_handlers();
        };
    }
}


