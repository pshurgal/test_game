#pragma once

// project includes
#include "core/sdl_types.h"
#include "core/game_screen.h"

namespace core
{
    namespace game_screens
    {
        class sample_game_screen: public game_screen
        {
        public:
            sample_game_screen( renderer_p renderer );

            void on_enter();

            void on_leave();
        };
    }
}
