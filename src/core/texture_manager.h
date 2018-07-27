#pragma once

// project includes
#include "sdl_types.h"

// thirdparty includes
#include "SDL2/SDL_render.h"

// STL includes
#include <map>
#include <string>

namespace core
{
    class texture_manager
    {
    private:
        texture_manager();

    public:
        static texture_manager& instance();

        void load_texture( std::string path, std::string id, renderer_p renderer );

        void draw( std::string id, int x, int y, int width, int height, renderer_p renderer,
                   SDL_RendererFlip flip = SDL_FLIP_NONE );

    private:
        std::map<std::string, texture_p> _textures;
    };
}
