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
            explicit level_game_screen();

            void initialize_event_handlers();
        };
    }
}


