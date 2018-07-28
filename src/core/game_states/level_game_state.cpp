#include "level_game_state.h"

// project includes
#include "core/a_star/a_start.h"
#include "core/game_screens/game_over_game_screen.h"
#include "core/game_screen_manager.h"

// STL includes
#include <chrono>

namespace core
{
    namespace game_states
    {

        const core::event_handler level_game_state::mouse_button_up_handler = []( SDL_Event& e, game_state_p state )
        {
            auto state_converted = dynamic_cast<game_states::level_game_state*>(state.get());
            if( state_converted )
            {
                if( e.button.button == SDL_BUTTON_LEFT && e.button.clicks == 1 )
                {
                    auto point = state_converted->camera.screen_coords_to_world_coords( e.button.x, e.button.y );
                    auto tile = state_converted->tile_field->click_point( point.x, point.y );

                    if( tile.x != INT32_MIN )
                    {
                        state_converted->_player_path = a_star::get_path( state_converted->player->field_position(),
                                                                          tile,
                                                                          state_converted->tile_field );
                    }
                } else if( e.button.button == SDL_BUTTON_RIGHT && e.button.clicks == 1 )
                {
                    auto point = state_converted->camera.screen_coords_to_world_coords( e.button.x, e.button.y );
                    auto tile = state_converted->tile_field->click_point( point.x, point.y );

                    state_converted->tile_field->tile( tile.x, tile.y )->switch_state();
                }
            }
        };

        level_game_state::level_game_state()
        {
            tile_field = gameplay::create_tile_field( 30, 30, "ground_tile", "lava_tile" );
            player = gameplay::create_unit( 0, 0, "player_0", "player_1", "player_2", "player_3" );

            guard = gameplay::create_unit( _guard_point_1.x, _guard_point_1.y, "guard_0", "guard_1", "guard_2",
                                           "guard_3" );

            bed = gameplay::create_unit( 29, 29, "bed", "", "", "" );

            _guard_point_current = _guard_point_2;
        }

        void level_game_state::update()
        {
            auto current_time = std::chrono::high_resolution_clock::now();
            if( std::chrono::duration_cast<std::chrono::milliseconds>( current_time - last_update_time ).count() >=
                500 )
            {
                if( is_game_over() )
                {
                    core::game_screen_manager::instance().push_game_screen(
                            create_game_screen<game_screens::game_over_game_screen>() );
                }

                if( is_win() )
                {
                    core::game_screen_manager::instance().push_game_screen(
                            create_game_screen<game_screens::game_over_game_screen>( true ) );
                }

                if( !_player_path.empty() )
                {
                    player->move( _player_path.back() );
                    _player_path.pop_back();
                }


                _guard_path = a_star::get_path( guard->field_position(), _guard_point_current, tile_field );

                if( !_guard_path.empty() )
                {
                    guard->move( _guard_path.back() );
                    _guard_path.pop_back();
                }

                if( guard->field_position() == _guard_point_1 )
                    _guard_point_current = _guard_point_2;
                else if( guard->field_position() == _guard_point_2 )
                    _guard_point_current = _guard_point_1;


                last_update_time = std::chrono::high_resolution_clock::now();
            }

            camera.move_to( -player->world_position().x,
                            -player->world_position().y );
        }

        bool level_game_state::is_game_over()
        {

            return player->field_position() == guard->field_position();
        }

        bool level_game_state::is_win()
        {
            return player->field_position() == bed->field_position();
        }
    }
}
