#pragma once

// project includes

// STL includes
#include <memory>

namespace core
{
    class game_state;

    typedef std::shared_ptr<game_state> game_state_p;

    template< class T, typename... Args >
    game_state_p create_game_state( Args... args )
    {
        static_assert( std::is_base_of<game_state, T>::value );
        return game_state_p( new T( args... ) );
    }

    class game_state
    {
    public:
        game_state();

        virtual ~game_state();

        virtual void update() = 0;

    private:
    };
}
