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
                case direction_e::LEFT_DOWN:
                    texture = _texture_0;
                    break;
                case direction_e::LEFT_UP:
                    texture = _texture_1;
                    break;
                case direction_e::RIGHT_UP:
                    texture = _texture_2;
                    break;
                case direction_e::RIGHT_DOWN:
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

        direction_e player::direction() const
        {
            return _direction;
        }

        math::vec2 player::position()
        {
            return math::vec2( _field_x, _field_y );
        }

        void player::move( direction_e )
        {

        }

        player_p create_player( int32_t x, int32_t y, const std::string& texture_0, const std::string& texture_1,
                                const std::string& texture_2, const std::string& texture_3 )
        {
            return std::make_shared<player>( x, y, texture_0, texture_1, texture_2, texture_3 );
        }
    }
}