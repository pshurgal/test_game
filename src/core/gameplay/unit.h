#pragma once

// project includes
#include "core/drawable.h"
#include "math/vec2.h"
#include "direction.h"


// STL includes
#include <cstdint>
#include <string>

namespace core
{
    namespace gameplay
    {
        class unit : public drawable
        {
        public:
            unit( int32_t x,
                  int32_t y,
                  const std::string& texture_0,
                  const std::string& texture_1,
                  const std::string& texture_2,
                  const std::string& texture_3 );

            void render( game_state_p game_state, renderer_p renderer ) override;

            direction_e direction() const;

            math::vec2 field_position();

            math::vec2 world_position();

            void move( direction_e );

        private:
            math::vec2 _field_position;

            std::string _texture_0;
            std::string _texture_1;
            std::string _texture_2;
            std::string _texture_3;

            direction_e _direction = direction_e::LEFT_DOWN;

            math::vec2 _world_position;
        };

        typedef std::shared_ptr<unit> unit_p;

        unit_p create_unit( int32_t x, int32_t y, const std::string& texture_0, const std::string& texture_1,
                            const std::string& texture_2, const std::string& texture_3 );
    }
}


