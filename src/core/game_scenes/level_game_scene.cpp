#include "level_game_scene.h"

// project includes
#include "core/texture_manager.h"
#include "core/game_states/level_game_state.h"
#include "core/gameplay/tile.h"

namespace core
{
    namespace game_scenes
    {
        level_game_scene::level_game_scene( renderer_p renderer )
        {
            texture_manager::instance().load_texture( "../share/test_game/images/ground_tile.png", "ground_tile", renderer );
            texture_manager::instance().load_texture( "../share/test_game/images/player_0.png", "player_0", renderer );
            texture_manager::instance().load_texture( "../share/test_game/images/player_1.png", "player_1", renderer );
            texture_manager::instance().load_texture( "../share/test_game/images/player_2.png", "player_2", renderer );
            texture_manager::instance().load_texture( "../share/test_game/images/player_3.png", "player_3", renderer );
        }

        void level_game_scene::render( game_state_p game_state, renderer_p renderer )
        {
            if( tile_field )
                tile_field->render( game_state, renderer );

            if( player )
                player->render( game_state, renderer );
        }
    }
}