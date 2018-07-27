#include "tile_field.h"

namespace core
{
    namespace gameplay
    {

        tile_field::tile_field( size_t width, size_t height )
                : _width( width )
                , _height( height )
        {
            _tiles.resize( width );
            for( size_t i = 0; i < _tiles.size(); i++ )
            {
                _tiles[i].resize( height );
                for( size_t j = 0; j < _tiles[i].size(); j++ )
                {
                    _tiles[i][j] = create_tile( int32_t( i ), int32_t( j ), "ground_tile" );
                }
            }
        }

        void tile_field::render( game_state_p game_state, renderer_p renderer )
        {
            for( auto& col : _tiles )
            {
                for( auto& tile: col )
                {
                    tile->render( game_state, renderer );
                }
            }
        }

        tile_p tile_field::tile( size_t x, size_t y )
        {
            return _tiles[x][y];
        }

        size_t tile_field::height() const
        {
            return _height;
        }

        size_t tile_field::width() const
        {
            return _width;
        }

        tile_field_p create_tile_field( size_t width, size_t height )
        {
            return std::make_shared<tile_field>( width, height );
        }
    }
}