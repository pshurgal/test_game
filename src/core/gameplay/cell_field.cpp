#include "cell_field.h"

namespace core
{
    namespace gameplay
    {
        cell_field::cell_field( tile_field_p tile_field )
        {
            _cells.resize( tile_field->width() );
            for( size_t i = 0; i < _cells.size(); i++ )
            {
                _cells[i].resize( tile_field->height() );
                for( size_t j = 0; j < _cells[i].size(); j++ )
                {
                    _cells[i][j] = create_cell( tile_field->tile( i, j ) );
                }
            }

        }

        SDL_Point cell_field::click_point( int32_t x, int32_t y )
        {
            SDL_Point result = { INT32_MIN, INT32_MIN };
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

        cell_field_p create_cell_field( tile_field_p tile_field )
        {
            return std::make_shared<cell_field>( tile_field );
        }
    }
}
