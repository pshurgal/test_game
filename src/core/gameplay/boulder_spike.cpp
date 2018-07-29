#include "boulder_spike.h"

namespace core
{
    namespace gameplay
    {
        boulder_spike::boulder_spike(direction_e direction,
                                     int32_t x,
                                     int32_t y,
                                     const std::string& texture_0,
                                     const std::string& texture_1,
                                     const std::string& texture_2,
                                     const std::string& texture_3)
            : unit(x, y, texture_0, texture_1, texture_2, texture_3)
        {
            unit::direction() = direction;
        }

        void boulder_spike::move(direction_e direction)
        {
            unit::move(direction);
        }

        void boulder_spike::move()
        {
            move(direction());
        }
    }
}