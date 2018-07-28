#include "game_over_game_screen.h"

// project includes
#include "core/game_scenes/game_over_game_scene.h"
#include "core/game_states/game_over_game_state.h"
#include "core/event_handler.h"

namespace core
{
    namespace game_screens
    {

        game_over_game_screen::game_over_game_screen( bool win )
                : game_screen( create_game_state<game_states::game_over_game_state>(),
                               create_game_scene<game_scenes::game_over_game_scene>( win ) )
        {
            initialize_event_handlers();
        }

        void game_over_game_screen::initialize_event_handlers()
        {
            add_event_handler( SDL_KEYUP, game_states::game_over_game_state::key_up_handler );
        }
    }
}
