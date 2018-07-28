#include <utility>

#include "level_game_state.h"

#include <mutex>
#include <chrono>

namespace core
{
    namespace game_states
    {

        void level_game_state::update()
        {
        }

        void level_game_state::set_player_path( std::list<gameplay::direction_e> path )
        {
            std::lock_guard<std::mutex> lock( _m );
            player_path = std::move( path );
        }

        void level_game_state::update_units_loop()
        {
            while( !_shutdown_signalled )
            {
                {
                    std::lock_guard<std::mutex> lock( _m );

                    if( !player_path.empty() )
                    {
                        player->move( player_path.back() );
                        player_path.pop_back();
                    }
                }

                using namespace std::chrono_literals;
                std::this_thread::sleep_for( 500ms );
            }
        }

        void level_game_state::start_update_units()
        {
            _shutdown_signalled = false;
            _units_updater_thread = std::thread( &level_game_state::update_units_loop, this );
        }

        void level_game_state::stop_update_units()
        {
            _shutdown_signalled = true;
            _units_updater_thread.join();
        }
    }
}
