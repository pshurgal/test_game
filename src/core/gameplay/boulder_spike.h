#pragma once

// project includes
#include "core/gameplay/unit.h"

namespace core
{
    namespace gameplay
    {
        class boulder_spike : public unit
        {
        public:
            boulder_spike( direction_e direction,
                           int32_t x,
                           int32_t y,
                           const std::string& texture_0,
                           const std::string& texture_1,
                           const std::string& texture_2,
                           const std::string& texture_3 );

            void move();

        private:
            void move( direction_e );
        };
    }
}


