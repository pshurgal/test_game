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

            SDL_Point click_point( int32_t x, int32_t y );

        private:
            std::vector<std::vector<cell_p>> _cells;
        };

        typedef std::shared_ptr<cell_field> cell_field_p;

        cell_field_p create_cell_field( tile_field_p tile_field );
    }
}
