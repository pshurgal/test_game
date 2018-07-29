#pragma once

// project includes
#include "core/game_screen.h"
#include "core/sdl_types.h"

namespace core
{
    namespace game_screens
    {
        class game_over_game_screen : public game_screen
        {
          public:
            explicit game_over_game_screen(bool win = false);

          private:
            void initialize_event_handlers();
        };
    }
}
