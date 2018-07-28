#include "game_over_game_scene.h"

// project includes
#include "core/texture_manager.h"

namespace core
{
    namespace game_scenes
    {

        game_over_game_scene::game_over_game_scene( bool win )
                : _win( win )
        {}

        void game_over_game_scene::render( game_state_p game_state, renderer_p renderer )
        {
            if( _win )
            {
                texture_manager::instance().draw( "you_won",
                                                  0,
                                                  0,
                                                  1024,
                                                  768,
                                                  std::move( renderer ) );
            } else
            {
                texture_manager::instance().draw( "game_over",
                                                  0,
                                                  0,
                                                  1024,
                                                  768,
                                                  std::move( renderer ) );
            }
        }
    }
}