#pragma once

// project includes

// STL includes
#include <memory>

namespace core
{
    class game_state
    {
    public:
        game_state();

        virtual ~game_state();

    private:
    };

    typedef std::shared_ptr<game_state> game_state_p;
}
