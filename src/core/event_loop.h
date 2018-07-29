#pragma once

// project includes
#include "event_handler.h"
#include "game.h"
#include "game_state.h"

// STL includes
#include <map>
#include <memory>

namespace core
{
    class event_loop
    {
      private:
        event_loop();

        ~event_loop();

      public:
        static event_loop& instance();

        void process(std::map<uint32_t, event_handler> event_handlers, game_state_p game_state);

      private:
    };
}
