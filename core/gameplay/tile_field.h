#pragma once

// project includes
#include "tile.h"
#include "core/drawable.h"

// STL includes
#include <cstdint>
#include <memory>

namespace core
{
    namespace gameplay
    {
        class tile_field : public drawable
        {
        public:
            tile_field( size_t width, size_t height );

            void render( game_state_p game_state, renderer_p renderer ) override;

            tile_p tile( size_t x, size_t y );

            size_t width() const;

            size_t height() const;

        private:
            size_t _width;
            size_t _height;
            std::vector<std::vector<tile_p>> _tiles;
        };

        typedef std::shared_ptr<tile_field> tile_field_p;

        tile_field_p create_tile_field( size_t width, size_t height );
    }
}
