#pragma once

// project includes
#include "sdl_types.h"

// STL includes
#include <string>

namespace core
{
    class sdl_types_factory
    {
      public:
        static window_p get_window(std::string name, int32_t x, int32_t y, int32_t w, int32_t h, uint32_t flags);

        static renderer_p get_renderer(window_p window, int32_t index, uint32_t flags);

        static surface_p get_surface(std::string path);

        static texture_p get_texture(renderer_p renderer, surface_p surface);
    };
}
