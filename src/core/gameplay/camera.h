#pragma once

// project includes
#include "math/vec2.h"

// STL includes
#include <cstdint>

namespace core
{
    namespace gameplay
    {
        class camera
        {
        public:
            int32_t x();

            int32_t y();

            void move_to( int32_t x, int32_t y );

            void move_rel( int32_t x, int32_t y );


            math::vec2 screen_coords_to_world_coords( int32_t x, int32_t y );

        private:
            int32_t _x = 0;
            int32_t _y = 0;
        };
    }
}



