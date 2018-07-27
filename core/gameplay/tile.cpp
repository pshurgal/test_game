#include "tile.h"

// project includes
#include "core/texture_manager.h"
#include "core/game_states/level_game_state.h"
#include "math/vec2.h"

namespace core
{
    namespace gameplay
    {
        tile::tile( int32_t field_x, int32_t field_y, const std::string& texture_id )
                : _field_x( field_x )
                , _field_y( field_y )
                , _world_x( (50 - 8) / 2 * field_x - (50 - 8) / 2 * field_y )
                , _world_y( (50 - 2) / 4 * field_x + (50 - 2) / 4 * field_y )
                , _texture_id( texture_id )
        {}

        void tile::render( game_state_p game_state, renderer_p renderer )
        {
            auto level_game_state = (game_states::level_game_state*)game_state.get();
            texture_manager::instance().draw( "ground_tile",
                                              level_game_state->camera.x() + _world_x,
                                              level_game_state->camera.y() + _world_y,
                                              50,
                                              50,
                                              std::move( renderer ) );
        }

        bool tile::is_in_bound( int32_t x, int32_t y )
        {
            math::vec2 a = { _world_x + 4,
                             _world_y + 1 + (50 - 2) / 4 };
            math::vec2 b = { _world_x + 4 + (50 - 8) / 2,
                             _world_y + 1 };
            math::vec2 c = { _world_x + 4 + (50 - 8),
                             _world_y + 1 + (50 - 2) / 4 };
            math::vec2 d = { _world_x + 4 + (50 - 8) / 2,
                             _world_y + 1 + (50 - 2) / 2 };

            math::vec2 point = { x, y };

            return b.cross( a, point ) >= 0 && c.cross( d, point ) <= 0 && d.cross( a, point ) <= 0 &&
                   c.cross( b, point ) >= 0;
        }

        tile_p create_tile( int32_t field_x, int32_t field_y, const std::string& texture_id )
        {
            return std::make_shared<tile>( field_x, field_y, texture_id );
        }
    }
}
