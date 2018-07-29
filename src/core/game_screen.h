#pragma once

// project includes
#include "event_handler.h"
#include "game_scene.h"
#include "game_state.h"

// STL includes
#include <cstdint>
#include <map>
#include <memory>

namespace core
{
    class game_screen;

    typedef std::shared_ptr<game_screen> game_screen_p;

    template<class T, typename... Args>
    game_screen_p create_game_screen(Args... args)
    {
        static_assert(std::is_base_of<game_screen, T>::value);
        return game_screen_p(new T(args...));
    }

    class game_screen
    {
      public:
        game_screen(game_state_p state, game_scene_p scene);

        virtual ~game_screen();

        game_state_p state();

        game_scene_p scene();

        void add_event_handler(uint32_t event_type, event_handler handler);

        std::map<uint32_t, event_handler>& event_handlers();

      private:
        std::map<uint32_t, event_handler> _event_handlers;
        game_scene_p _scene;
        game_state_p _state;
    };
}