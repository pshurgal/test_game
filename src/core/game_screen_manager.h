#pragma once

// project includes
#include "game_screen.h"
#include "sdl_types.h"

// STL includes
#include <stack>

namespace core
{
    class game_screen_manager
    {
      private:
        game_screen_manager() = default;

      public:
        static game_screen_manager& instance();

        void push_game_screen(game_screen_p screen);

        game_screen_p current_screen();

      private:
        game_screen_p _screens;
    };
}
