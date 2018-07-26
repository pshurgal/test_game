#include "game_screen.h"

namespace core
{
    game_screen::game_screen( game_state_p state, game_scene_p scene )
            : _state( std::move( state ) )
            , _scene( std::move( scene ) )
    {}

    game_screen::~game_screen() = default;

    game_scene_p game_screen::scene()
    {
        return _scene;
    }

    game_state_p game_screen::state()
    {
        return _state;
    }

    void game_screen::add_event_handler( uint32_t event_type, event_handler handler )
    {
        _event_handlers[event_type] = std::move( handler );
    }

    std::map<uint32_t, event_handler>& game_screen::event_handlers()
    {
        return _event_handlers;
    }
}