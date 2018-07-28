#include "direction.h"

// STL includes
#include <type_traits>

namespace core
{
    namespace gameplay
    {
        direction_e operator++( direction_e& x )
        {
            return x = (direction_e)(std::underlying_type<direction_e>::type( x ) + 1);
        }

        direction_e operator*( direction_e c )
        {
            return c;
        }

        direction_e begin( direction_e r )
        {
            return direction_e::LEFT_DOWN;
        }

        direction_e end( direction_e r )
        {
            return (direction_e)(std::underlying_type<direction_e>::type( direction_e::RIGHT_DOWN ) + 1);;
        }
    }
}