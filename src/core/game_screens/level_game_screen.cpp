#include "level_game_screen.h"

// project includes
#include "core/a_star/a_start.h"
#include "core/game_scenes/level_game_scene.h"
#include "core/game_states/level_game_state.h"
#include "core/logger.h"
#include "core/texture_manager.h"

namespace core
{
    namespace game_screens
    {
        level_game_screen::level_game_screen()
            : game_screen(create_game_state<game_states::level_game_state>(),
                          create_game_scene<game_scenes::level_game_scene>())
        {
            initialize_event_handlers();
        }

        void level_game_screen::initialize_event_handlers()
        {
            add_event_handler(SDL_MOUSEBUTTONUP, game_states::level_game_state::mouse_button_up_handler);
            add_event_handler(SDL_KEYUP, game_states::level_game_state::key_up_handler);
        }
    }
}
