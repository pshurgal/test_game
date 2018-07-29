#pragma once

// project includes
#include "game_scene_renderer.h"
#include "sdl_types.h"

// STL includes
#include <cstdint>
#include <memory>

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
        void load_textures();

      private:
        bool _shutdown_signalled = false;

        window_p _window;
        renderer_p _renderer;

        game_scene_renderer _game_scene_renderer;
    };
}
