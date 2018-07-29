#pragma once

#include <math/vec2.h>
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

        static const direction_e direction_array[] = {direction_e::LEFT_DOWN,
                                                      direction_e::LEFT_UP,
                                                      direction_e::RIGHT_UP,
                                                      direction_e::RIGHT_DOWN};

        math::vec2 direction_to_vec2(direction_e d);
    }
}