#include "game_over_game_state.h"

// project includes
#include "core/game_screen_manager.h"
#include "core/game_screens/level_game_screen.h"

namespace core
{
    namespace game_states
    {
        const core::event_handler game_over_game_state::key_up_handler = []( SDL_Event& e, game_state_p state )
        {
            game_screen_manager::instance().push_game_screen( create_game_screen<game_screens::level_game_screen>());
        };

        void game_over_game_state::update()
        {}
    }
}
