#include "level_game_state.h"

// project includes
#include "core/a_star/a_start.h"
#include "core/game_screens/game_over_game_screen.h"
#include "core/game_screen_manager.h"
#include "core/gameplay/boulder_spike.h"

// STL includes
#include <random>

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

                    if( tile.x != INT32_MIN )
                    {
                        state_converted->tile_field->tile( tile.x, tile.y )->switch_state();
                    }
                }
            }
        };

        const core::event_handler level_game_state::key_up_handler = []( SDL_Event& e, game_state_p state )
        {
            auto state_converted = dynamic_cast<game_states::level_game_state*>(state.get());
            if( state_converted )
            {
                math::vec2 offset( 0, 0 );
                if( e.key.keysym.sym == SDLK_RIGHT )
                {
                    offset.x = -10;
                } else if( e.key.keysym.sym == SDLK_LEFT )
                {
                    offset.x = 10;
                } else if( e.key.keysym.sym == SDLK_UP )
                {
                    offset.y = 10;
                } else if( e.key.keysym.sym == SDLK_DOWN )
                {
                    offset.y = -10;
                }
                state_converted->camera.move_rel( offset.x, offset.y );
            }
        };

        level_game_state::level_game_state()
        {
            std::srand( unsigned( std::time( 0 ) ) );

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

            if( std::chrono::duration_cast<std::chrono::milliseconds>(
                    current_time - last_boulder_spikes_update_time ).count() >=
                1500 )
            {
                create_random_boulder_spike();
                last_boulder_spikes_update_time = std::chrono::high_resolution_clock::now();
            }

            if( std::chrono::duration_cast<std::chrono::milliseconds>(
                    current_time - last_units_update_time ).count() >=
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

                for( auto& boulder_spike : boulder_spikes )
                {
                    auto boulder_spike_converted = dynamic_cast<gameplay::boulder_spike*>(boulder_spike.get());
                    boulder_spike_converted->move();
                }

                boulder_spikes.remove_if(
                        [ & ]( gameplay::unit_p boulder_spike )
                        {
                            auto field_position = boulder_spike->field_position();

                            return field_position.x < 0 ||
                                   field_position.y < 0 ||
                                   field_position.x >= tile_field->width() ||
                                   field_position.y >= tile_field->height();
                        } );

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


                last_units_update_time = std::chrono::high_resolution_clock::now();
            }
        }

        bool level_game_state::is_game_over()
        {
            auto result = player->field_position() == guard->field_position();
            for( auto& boulder_spike : boulder_spikes )
            {
                result |= boulder_spike->field_position() == player->field_position();
            }

            return result;
        }

        bool level_game_state::is_win()
        {
            return player->field_position() == bed->field_position();
        }

        void level_game_state::create_random_boulder_spike()
        {
            gameplay::direction_e direction;
            math::vec2 start_position( 0, 0 );

            switch( std::rand() % 4 )
            {
                case 0:
                    direction = gameplay::direction_e::LEFT_DOWN;
                    break;
                case 1:
                    direction = gameplay::direction_e::LEFT_UP;
                    break;
                case 2:
                    direction = gameplay::direction_e::RIGHT_UP;
                    break;
                case 3:
                    direction = gameplay::direction_e::RIGHT_DOWN;
                    break;
            }

            switch( direction )
            {
                case gameplay::direction_e::LEFT_DOWN:
                    start_position = math::vec2( rand() % tile_field->width(),
                                                 0 );
                    break;
                case gameplay::direction_e::LEFT_UP:
                    start_position = math::vec2( tile_field->width() - 1,
                                                 rand() % tile_field->height() );
                    break;
                case gameplay::direction_e::RIGHT_UP:
                    start_position = math::vec2( rand() % tile_field->width(),
                                                 tile_field->height() - 1 );
                    break;
                case gameplay::direction_e::RIGHT_DOWN:
                    start_position = math::vec2( 0,
                                                 rand() % tile_field->width() );
                    break;
            }

            boulder_spikes.push_back( gameplay::create_unit<gameplay::boulder_spike>(
                    direction,
                    start_position.x,
                    start_position.y,
                    "boulder_spike_0",
                    "boulder_spike_1",
                    "boulder_spike_2",
                    "boulder_spike_3"
            ) );
        }
    }
}
