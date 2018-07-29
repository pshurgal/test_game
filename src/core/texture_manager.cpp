#include "texture_manager.h"

// project includes
#include "logger.h"
#include "sdl_types_factory.h"

namespace core
{
    texture_manager::texture_manager()
    {
    }

    texture_manager& texture_manager::instance()
    {
        static texture_manager _texture_manager;
        return _texture_manager;
    }

    void texture_manager::load_texture( std::string path, std::string id, renderer_p renderer )
    {
        try
        {
            auto surface = sdl_types_factory::get_surface( path );

            _textures[id] = sdl_types_factory::get_texture( renderer, surface );

            LOG( INFO ) << "Texture file loaded: " << path;
        } catch( std::exception& e )
        {
            LOG( ERROR ) << SDL_GetError();
            throw e;
        }
    }

    void texture_manager::draw( std::string id, int x, int y, int width, int height, renderer_p renderer,
                                SDL_RendererFlip flip )
    {
        SDL_Rect src_rect;
        SDL_Rect dest_rect;

        src_rect.x = 0;
        src_rect.y = 0;
        src_rect.w = width;
        src_rect.h = height;

        dest_rect.x = x;
        dest_rect.y = y;
        dest_rect.w = width;
        dest_rect.h = height;

        SDL_RenderCopyEx( renderer.get(), _textures[id].get(), &src_rect, &dest_rect, 0, nullptr, flip );
    }
}
