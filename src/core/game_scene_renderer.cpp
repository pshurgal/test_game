#include "game_scene_renderer.h"

// thirdparty includes
#include "SDL2/SDL_video.h"

// project includes
#include "game_screen_manager.h"
#include "texture_manager.h"
#include "sdl_types_factory.h"

namespace core
{
    game_scene_renderer::game_scene_renderer()
    {
    }

    void game_scene_renderer::render( game_scene_p scene, game_state_p game_state )
    {
        if( _renderer )
        {
            SDL_RenderClear( _renderer.get() );

            scene->render( std::move( game_state ), _renderer );

            SDL_RenderPresent( _renderer.get() );
        }
    }

    void game_scene_renderer::set_renderer( renderer_p renderer )
    {
        _renderer = renderer;
    }
}
