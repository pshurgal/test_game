#include "sample_game_scene.h"

// project includes
#include "core/texture_manager.h"

namespace core
{
    namespace game_scenes
    {
        void sample_game_scene::render( game_state_p game_state, renderer_p renderer )
        {
            texture_manager::instance().draw( "template", 0, 0, 1473, 1854, renderer );
        }

        sample_game_scene::sample_game_scene( renderer_p renderer )
        {
            texture_manager::instance().load_texture( "resources/images/template.png", "template", renderer );
        }
    }
}
