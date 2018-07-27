#pragma once

//project includes
#include "unit.h"

namespace core
{
    namespace gameplay
    {
        class player : public unit
        {
        public:
            player( int32_t x,
                    int32_t y,
                    const std::string& texture_0,
                    const std::string& texture_1,
                    const std::string& texture_2,
                    const std::string& texture_3 );

            void render( game_state_p game_state, renderer_p renderer ) override;

            void change_direction( int8_t direction );

            int8_t direction() const;

        private:
            int32_t _field_x;
            int32_t _field_y;

            std::string _texture_0;
            std::string _texture_1;
            std::string _texture_2;
            std::string _texture_3;

            int8_t _direction = 0;

            int32_t _world_x;
            int32_t _world_y;
        };

        typedef std::shared_ptr<player> player_p;

        player_p create_player( int32_t x,
                                int32_t y,
                                const std::string& texture_0,
                                const std::string& texture_1,
                                const std::string& texture_2,
                                const std::string& texture_3 );
    }
}
