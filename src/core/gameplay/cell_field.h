#pragma once

// project includes
#include "cell.h"
#include "core/gameplay/tile_field.h"

// STL includes
#include <vector>

namespace core
{
    namespace gameplay
    {
        class cell_field
        {
        public:
            cell_field( tile_field_p tile_field );

            math::vec2 click_point( int32_t x, int32_t y );

            cell_p cell( size_t x, size_t y );

            size_t width() const;

            size_t height() const;

        private:
            size_t _width;
            size_t _height;
            std::vector<std::vector<cell_p>> _cells;
        };

        typedef std::shared_ptr<cell_field> cell_field_p;

        cell_field_p create_cell_field( tile_field_p tile_field );
    }
}
