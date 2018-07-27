#include <core/game_states/level_game_state.h>
#include "level_game_screen.h"

// project includes
#include "core/game_scenes/level_game_scene.h"
#include "core/game_states/level_game_state.h"
#include "core/logger.h"

namespace core
{
    namespace game_screens
    {
        level_game_screen::level_game_screen( renderer_p renderer )
                : game_screen( create_game_state<game_states::level_game_state>(),
                               create_game_scene<game_scenes::level_game_scene>( renderer ) )
        {
            auto tile_field = gameplay::create_tile_field( 30, 30 );
            auto cell_field = gameplay::create_cell_field( tile_field );
            auto player = gameplay::create_player( 0, 0, "player_0", "player_1", "player_2",
                                                   "player_3" );

            ((game_scenes::level_game_scene*)scene().get())->tile_field = tile_field;
            ((game_scenes::level_game_scene*)scene().get())->player = player;

            ((game_states::level_game_state*)state().get())->cell_field = cell_field;
            ((game_states::level_game_state*)state().get())->player = player;


            initialize_event_handlers();

        }

        void level_game_screen::initialize_event_handlers()
        {
            add_event_handler( SDL_MOUSEMOTION, []( SDL_Event& e, game_state_p state )
            {
                if( e.motion.state == SDL_BUTTON_RMASK )
                {
                    ((game_states::level_game_state*)state.get())->camera.move_rel( e.motion.xrel, e.motion.yrel );
                }

            } );

            add_event_handler( SDL_KEYUP, []( SDL_Event& e, game_state_p state )
            {
                auto state_converted = ((game_states::level_game_state*)state.get());

                if( e.key.keysym.sym == SDLK_RIGHT )
                {
                    state_converted->player->change_direction( state_converted->player->direction() + 1 );
                }

                if( e.key.keysym.sym == SDLK_LEFT )
                {
                    state_converted->player->change_direction( state_converted->player->direction() - 1 );
                }

            } );

            add_event_handler( SDL_MOUSEBUTTONUP, []( SDL_Event& e, game_state_p state )
            {
                if( e.button.button == SDL_BUTTON_LEFT && e.button.clicks == 1 )
                {
                    auto state_converted = ((game_states::level_game_state*)state.get());

                    auto point = state_converted->camera.screen_coords_to_world_coords( e.button.x, e.button.y );
                    auto tile = state_converted->cell_field->click_point( point.x, point.y );

                    LOG( DEBUG ) << "screen: (" << e.button.x << ", " << e.button.y << ") world: (" << point.x << ", "
                                 << point.y << ")";
                    LOG( DEBUG ) << "tail: (" << tile.x << ", " << tile.y << ")";
                }
            } );
        }

        void level_game_screen::on_enter()
        {

        }

        void level_game_screen::on_leave()
        {

        }
    }
}
