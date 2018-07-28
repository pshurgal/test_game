#pragma once

#include <type_traits>

namespace core
{
    namespace gameplay
    {
        enum class direction_e
        {
            LEFT_DOWN,
            LEFT_UP,
            RIGHT_UP,
            RIGHT_DOWN
        };

        direction_e operator++( direction_e& x );

        direction_e operator*( direction_e c );

        direction_e begin( direction_e r );

        direction_e end( direction_e r );
    }
}