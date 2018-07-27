#pragma once

// thirdparty includes
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_video.h"

// STL includes
#include <functional>
#include <memory>

namespace core
{
    const static std::function<void( SDL_Renderer * )> renderer_destroyer =
            []( SDL_Renderer* renderer )
            {
                SDL_DestroyRenderer( renderer );
            };

    typedef std::shared_ptr<SDL_Renderer> renderer_p;

    const static std::function<void( SDL_Window * )> window_destroyer =
            []( SDL_Window* window )
            {
                SDL_DestroyWindow( window );
            };

    typedef std::shared_ptr<SDL_Window> window_p;

    const static std::function<void( SDL_Surface * )> surface_destroyer =
            []( SDL_Surface* surface )
            {
                SDL_FreeSurface( surface );
            };

    typedef std::shared_ptr<SDL_Surface> surface_p;

    const static std::function<void( SDL_Texture * )> texture_destroyer =
            []( SDL_Texture* texture )
            {
                SDL_DestroyTexture( texture );
            };

    typedef std::shared_ptr<SDL_Texture> texture_p;
}
