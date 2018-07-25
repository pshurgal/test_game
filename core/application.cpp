#include "application.h"

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

#include <functional>
#include <map>
#include <cstdint>

class Application::impl
{
public:
    impl();
    ~impl();

    int exec();

private:
    std::function<void(SDL_Window* window)> _window_destroyer_lambda =
            [](SDL_Window* window) {
        if( window )
            SDL_DestroyWindow(window);
    };
    std::unique_ptr<SDL_Window, decltype (_window_destroyer_lambda) > _window;

    bool _shutdown_signalled = false;

};

Application::impl::impl()
{
    SDL_Init(SDL_INIT_VIDEO);

    _window =
            std::unique_ptr<SDL_Window, decltype (_window_destroyer_lambda) >(
                SDL_CreateWindow(
                    "SDL2 Hello Window",
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    1024,
                    768,
                    SDL_WINDOW_SHOWN ),
                _window_destroyer_lambda );

    if( !_window ){
        SDL_Quit();
        throw std::exception();
    }
}

Application::impl::~impl()
{
    SDL_Quit();
}

int Application::impl::exec()
{
    while( !_shutdown_signalled )
    {
        SDL_Event e;
        while( SDL_PollEvent(&e) )
        {
            if (e.type==SDL_QUIT)
               _shutdown_signalled = true;
         }
    }

    return 0;
}

Application::Application()
    : _impl( std::make_unique<Application::impl>() )
{}

Application::~Application() = default;

int Application::exec()
{
    _impl->exec();
}
