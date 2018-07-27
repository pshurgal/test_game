#pragma once

// project includes
#include "core/sdl_types.h"
#include "core/game_scene_renderer.h"

// STL includes
#include <memory>
#include <cstdint>

namespace core
{
    class game
    {
    private:
        game();

        ~game();

    public:
        static game& instance();

        int exec();

        void signal_shutdown();

    public:
        static const size_t SCREEN_WIDTH = 1024;
        static const size_t SCREEN_HEIGHT = 768;

    private:
        bool _shutdown_signalled = false;

        window_p _window;
        renderer_p _renderer;

        game_scene_renderer _game_scene_renderer;
    };
}
