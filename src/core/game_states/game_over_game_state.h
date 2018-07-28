#pragma once

// project includes
#include "core/game_state.h"
#include "core/event_handler.h"

namespace core
{
    namespace game_states
    {
        class game_over_game_state : public game_state
        {
        public:
            void update() override;

            static const core::event_handler key_up_handler;
        };
    }
}

