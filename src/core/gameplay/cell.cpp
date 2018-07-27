#include <memory>

#include "cell.h"

namespace core
{
    namespace gameplay
    {
        cell::cell()
        = default;

        cell::cell( tile_p t )
                : tile( std::move( t ) )
        {

        }

        void cell::render( game_state_p game_state, renderer_p renderer )
        {
            if( tile )
                tile->render( std::move( game_state ), std::move( renderer ) );
        }

        cell_p create_cell( tile_p t )
        {
            return std::make_shared<cell>( t );
        }
    }
}
