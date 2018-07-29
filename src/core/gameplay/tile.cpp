#include "tile.h"

// project includes
#include "core/game_states/level_game_state.h"
#include "core/texture_manager.h"
#include "math/vec2.h"

namespace core
{
    namespace gameplay
    {
        tile::tile(int32_t field_x,
                   int32_t field_y,
                   bool reachable,
                   const std::string& ground_texture_id,
                   const std::string& lava_texture_id)
            : reachable(reachable)
            , _field_pos(field_x, field_y)
            , _world_pos((50 - 8) / 2 * field_x - (50 - 8) / 2 * field_y,
                         (50 - 2) / 4 * field_x + (50 - 2) / 4 * field_y)
            , _ground_texture_id(ground_texture_id)
            , _lava_texture_id(lava_texture_id)
            , _texture_id(ground_texture_id)
        {
        }

        void tile::render(game_state_p game_state, renderer_p renderer)
        {
            texture_manager::instance().draw(_texture_id,
                                             game_state->camera.x() + _world_pos.x,
                                             game_state->camera.y() + _world_pos.y,
                                             50,
                                             50,
                                             std::move(renderer));
        }

        bool tile::is_clicked(int32_t x, int32_t y)
        {
            math::vec2 a = {_world_pos.x + 4, _world_pos.y + 1 + (50 - 2) / 4};
            math::vec2 b = {_world_pos.x + 4 + (50 - 8) / 2, _world_pos.y + 1};
            math::vec2 c = {_world_pos.x + 4 + (50 - 8), _world_pos.y + 1 + (50 - 2) / 4};
            math::vec2 d = {_world_pos.x + 4 + (50 - 8) / 2, _world_pos.y + 1 + (50 - 2) / 2};

            math::vec2 point = {x, y};

            return b.cross(a, point) >= 0 && c.cross(d, point) <= 0 && d.cross(a, point) <= 0 && c.cross(b, point) >= 0;
        }

        void tile::switch_ground()
        {
            reachable = true;
            _texture_id = _ground_texture_id;
        }

        void tile::switch_lava()
        {
            reachable = false;
            _texture_id = _lava_texture_id;
        }

        void tile::switch_empty()
        {
            reachable = false;
            _texture_id = "";
        }

        void tile::switch_state()
        {
            if(_texture_id == _ground_texture_id)
                switch_lava();
            else if(_texture_id == _lava_texture_id)
                switch_empty();
            else
                switch_ground();
        }

        tile_p create_tile(int32_t field_x,
                           int32_t field_y,
                           bool reachable,
                           const std::string& ground_texture_id,
                           const std::string& lava_texture_id)
        {
            return std::make_shared<tile>(field_x, field_y, reachable, ground_texture_id, lava_texture_id);
        }
    }
}
