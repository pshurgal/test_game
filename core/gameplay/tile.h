#pragma once

// project includes
#include "core/drawable.h"

// STL includes
#include <cstdint>
#include <string>

namespace core
{
    namespace gameplay
    {
        class tile : public drawable
        {
        public:
            tile( int32_t field_x, int32_t field_y, const std::string& texture_id );

            void render( game_state_p game_state, renderer_p renderer ) override;

            bool is_in_bound( int32_t x, int32_t y );

        private:
            int32_t _field_x;
            int32_t _field_y;
            int32_t _world_x;
            int32_t _world_y;
            std::string _texture_id;
        };

        typedef std::shared_ptr<tile> tile_p;

        tile_p create_tile( int32_t field_x, int32_t field_y, const std::string& texture_id );
    }
}
