#pragma once

// project includes
#include "tile.h"
#include "core/drawable.h"
#include "unit.h"

namespace core
{
    namespace gameplay
    {
        class cell : public drawable
        {
        public:
            cell();

            cell( tile_p t );

            void render( game_state_p game_state, renderer_p renderer ) override;

            tile_p tile;
            std::shared_ptr<core::gameplay::unit> unit;

        private:

        };

        typedef std::shared_ptr<cell> cell_p;

        cell_p create_cell( tile_p t );
    }
}
