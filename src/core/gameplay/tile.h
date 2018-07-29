#pragma once

// project includes
#include "core/drawable.h"
#include "math/vec2.h"

// STL includes
#include <cstdint>
#include <string>

namespace core
{
    namespace gameplay
    {
        class tile : public drawable
        {
          public:
            tile(int32_t field_x,
                 int32_t field_y,
                 bool reachable,
                 const std::string& ground_texture_id,
                 const std::string& lava_texture_id);

            void render(game_state_p game_state, renderer_p renderer) override;

            bool is_clicked(int32_t x, int32_t y);

            bool reachable = true;

            void switch_state();
            void switch_ground();
            void switch_lava();
            void switch_empty();

          private:
            math::vec2 _field_pos;
            math::vec2 _world_pos;

            std::string _ground_texture_id;
            std::string _lava_texture_id;
            std::string _texture_id;
        };

        typedef std::shared_ptr<tile> tile_p;

        tile_p create_tile(int32_t field_x,
                           int32_t field_y,
                           bool reachable,
                           const std::string& ground_texture_id,
                           const std::string& lava_texture_id);
    }
}
