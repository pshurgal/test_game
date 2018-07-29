#include "direction.h"

// STL includes
#include <type_traits>

namespace core
{
    namespace gameplay
    {
        math::vec2 direction_to_vec2(direction_e d)
        {
            switch(d)
            {
            case gameplay::direction_e::LEFT_DOWN:
                return {0, 1};
            case gameplay::direction_e::LEFT_UP:
                return {-1, 0};
            case gameplay::direction_e::RIGHT_UP:
                return {0, -1};
            case gameplay::direction_e::RIGHT_DOWN:
                return {1, 0};
            }
        };
    }
}