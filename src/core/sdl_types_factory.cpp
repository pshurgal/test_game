#include "sdl_types_factory.h"

// thirdparty includes
#include "SDL2/SDL_image.h"

namespace core
{
    window_p sdl_types_factory::get_window(std::string name, int32_t x, int32_t y, int32_t w, int32_t h, uint32_t flags)
    {
        auto window = window_p(SDL_CreateWindow(name.c_str(), x, y, w, h, flags), window_destroyer);

        if(!window)
        {
            throw std::exception();
        }
        return window;
    }

    renderer_p sdl_types_factory::get_renderer(window_p window, int32_t index, uint32_t flags)
    {
        auto renderer = renderer_p(SDL_CreateRenderer(window.get(), index, flags), renderer_destroyer);

        if(!renderer)
        {
            throw std::exception();
        }
        return renderer;
    }

    surface_p sdl_types_factory::get_surface(std::string path)
    {
        auto surface = surface_p(IMG_Load(path.c_str()));

        if(!surface)
        {
            throw std::exception();
        }
        return surface;
    }

    texture_p sdl_types_factory::get_texture(renderer_p renderer, surface_p surface)
    {
        texture_p texture = texture_p(SDL_CreateTextureFromSurface(renderer.get(), surface.get()), texture_destroyer);

        if(!texture)
        {
            throw std::exception();
        }
        return texture;
    }
}
