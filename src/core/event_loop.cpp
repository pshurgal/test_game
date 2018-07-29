#include "event_loop.h"

// thirdparty includes
#include "SDL2/SDL_events.h"

// STL includes
#include <functional>

namespace core
{
    event_loop::event_loop()
    {
    }

    event_loop::~event_loop() = default;

    event_loop& event_loop::instance()
    {
        static event_loop _event_loop;
        return _event_loop;
    }

    void event_loop::process(std::map<uint32_t, event_handler> event_handlers, game_state_p game_state)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                game::instance().signal_shutdown();
            }
            else
            {
                auto handler = event_handlers.find(e.type);
                if(handler != event_handlers.end())
                {
                    handler->second(e, game_state);
                }
            }
        }
    }
}
