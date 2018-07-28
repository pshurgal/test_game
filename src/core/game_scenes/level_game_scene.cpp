#include "level_game_scene.h"

// project includes
#include "core/texture_manager.h"
#include "core/game_states/level_game_state.h"
#include "core/gameplay/tile.h"

namespace core
{
    namespace game_scenes
    {
        void level_game_scene::render( game_state_p game_state, renderer_p renderer )
        {
            auto state_converted = dynamic_cast<game_states::level_game_state*>(game_state.get());
            if( state_converted )
            {
                if( state_converted->tile_field )
                    state_converted->tile_field->render( game_state, renderer );

                if( state_converted->bed )
                    state_converted->bed->render( game_state, renderer );

                if( state_converted->player )
                    state_converted->player->render( game_state, renderer );

                if( state_converted->guard )
                    state_converted->guard->render( game_state, renderer );
            }
        }
    }
}