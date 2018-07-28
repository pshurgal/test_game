#include "game_screen_manager.h"

namespace core
{
    game_screen_manager::game_screen_manager()
    {
    }

    game_screen_manager& game_screen_manager::instance()
    {
        static game_screen_manager _game_state_machine;
        return _game_state_machine;
    }

    void game_screen_manager::push_game_screen( game_screen_p screen )
    {
        _screens.push( screen );
        screen->on_enter();
    }

    void game_screen_manager::pop_game_screen()
    {
        _screens.top()->on_leave();
        _screens.pop();
    }

    game_screen_p game_screen_manager::current_screen()
    {
        return _screens.top();
    }

    void game_screen_manager::pop_all_game_screens()
    {
        while(!_screens.empty())
            pop_game_screen();
    }
}
