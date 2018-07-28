#include <math/vec2.h>
#include "cell_field.h"

namespace core
{
    namespace gameplay
    {
        cell_field::cell_field( tile_field_p tile_field )
                : _width( tile_field->width() )
                , _height( tile_field->height() )
        {
            _cells.resize( _width );
            for( size_t i = 0; i < _cells.size(); i++ )
            {
                _cells[i].resize( _height );
                for( size_t j = 0; j < _cells[i].size(); j++ )
                {
                    _cells[i][j] = create_cell( tile_field->tile( i, j ) );
                }
            }

        }

        math::vec2 cell_field::click_point( int32_t x, int32_t y )
        {
            math::vec2 result = { INT32_MIN, INT32_MIN };
            for( int32_t i = 0; i < _cells.size(); i++ )
            {
                for( int32_t j = 0; j < _cells[i].size(); j++ )
                {
                    if( _cells[i][j]->tile && _cells[i][j]->tile->is_in_bound( x, y ) )
                        result = { i, j };
                }
            }

            return result;
        }

        cell_p cell_field::cell( size_t x, size_t y )
        {
            return _cells[x][y];
        }

        size_t cell_field::width() const
        {
            return _width;
        }

        size_t cell_field::height() const
        {
            return _height;
        }

        cell_field_p create_cell_field( tile_field_p tile_field )
        {
            return std::make_shared<cell_field>( tile_field );
        }
    }
}
