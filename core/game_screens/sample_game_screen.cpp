#include "sample_game_screen.h"

// project includes
#include "core/game_scenes/sample_game_scene.h"
#include "core/game_states/sample_game_state.h"
#include "core/logger.h"

namespace core
{
    namespace game_screens
    {
        sample_game_screen::sample_game_screen( renderer_p renderer )
                : game_screen( game_state_p( new game_states::sample_game_state ),
                               game_scene_p( new game_scenes::sample_game_scene( renderer ) ) )
        {
            add_event_handler( SDL_KEYUP, []( SDL_Event& e, game_state_p state )
            {
                if( e.key.keysym.sym == SDLK_LEFT )
                {
                    ((game_states::sample_game_state*)state.get())->x--;
                } else if( e.key.keysym.sym == SDLK_RIGHT )
                {
                    ((game_states::sample_game_state*)state.get())->x++;
                }

                LOG( INFO ) << ((game_states::sample_game_state*)state.get())->x;
            } );
        }

        void sample_game_screen::on_enter()
        {

        }

        void sample_game_screen::on_leave()
        {

        }
    }

}
