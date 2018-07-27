#pragma once

// thirdparty includes
#include "SDL2/SDL_rect.h"

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


            SDL_Point screen_coords_to_world_coords( int32_t x, int32_t y );

        private:
            int32_t _x = 0;
            int32_t _y = 0;
        };
    }
}



