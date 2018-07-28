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
        game_screen_manager();

    public:
        static game_screen_manager& instance();

        void push_game_screen( game_screen_p screen );

        void pop_game_screen();

        void pop_all_game_screens();

        game_screen_p current_screen();

    private:
        std::stack<game_screen_p> _screens;
    };
}
