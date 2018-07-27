#include "player.h"

// project includes
#include "core/game_states/level_game_state.h"
#include "core/texture_manager.h"

namespace core
{
    namespace gameplay
    {

        player::player( int32_t x, int32_t y, const std::string& texture_0, const std::string& texture_1,
                        const std::string& texture_2, const std::string& texture_3 )
                : _field_x( x )
                , _field_y( y )
                , _texture_0( texture_0 )
                , _texture_1( texture_1 )
                , _texture_2( texture_2 )
                , _texture_3( texture_3 )
                , _world_x( 8 )
                , _world_y( -30 )
        {

        }

        void player::render( game_state_p game_state, renderer_p renderer )
        {
            std::string texture;

            switch( _direction )
            {
                case 0:
                    texture = _texture_0;
                    break;
                case 1:
                    texture = _texture_1;
                    break;
                case 2:
                    texture = _texture_2;
                    break;
                case 3:
                    texture = _texture_3;
                    break;
            }

            auto level_game_state = (game_states::level_game_state*)game_state.get();
            texture_manager::instance().draw( texture,
                                              level_game_state->camera.x() + _world_x,
                                              level_game_state->camera.y() + _world_y,
                                              33,
                                              50,
                                              std::move( renderer ) );
        }

        int8_t player::direction() const
        {
            return _direction;
        }

        void player::change_direction( int8_t direction )
        {
            _direction = int8_t( (direction + 4) % 4 );
        }

        player_p create_player( int32_t x, int32_t y, const std::string& texture_0, const std::string& texture_1,
                                const std::string& texture_2, const std::string& texture_3 )
        {
            return std::make_shared<player>( x, y, texture_0, texture_1, texture_2, texture_3 );
        }
    }
}