#include "unit.h"

// project includes
#include "core/game_states/level_game_state.h"
#include "core/texture_manager.h"

namespace core
{
    namespace gameplay
    {
        unit::unit(int32_t x,
                   int32_t y,
                   const std::string& texture_0,
                   const std::string& texture_1,
                   const std::string& texture_2,
                   const std::string& texture_3)
            : _field_position(x, y)
            , _texture_0(texture_0)
            , _texture_1(texture_1)
            , _texture_2(texture_2)
            , _texture_3(texture_3)
            , _world_position(8 + (50 - 8) / 2 * _field_position.x - (50 - 8) / 2 * _field_position.y,
                              -30 + (50 - 2) / 4 * _field_position.x + (50 - 2) / 4 * _field_position.y)
        {
        }

        void unit::render(game_state_p game_state, renderer_p renderer)
        {
            std::string texture;

            switch(_direction)
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

            texture_manager::instance().draw(texture,
                                             game_state->camera.x() + _world_position.x,
                                             game_state->camera.y() + _world_position.y,
                                             33,
                                             50,
                                             std::move(renderer));
        }

        direction_e unit::direction() const
        {
            return _direction;
        }

        math::vec2 unit::field_position()
        {
            return _field_position;
        }

        void unit::move(direction_e d)
        {
            auto direction_vec = gameplay::direction_to_vec2(d);
            _field_position += direction_vec;

            _direction = d;

            _world_position = {8 + (50 - 8) / 2 * _field_position.x - (50 - 8) / 2 * _field_position.y,
                               -30 + (50 - 2) / 4 * _field_position.x + (50 - 2) / 4 * _field_position.y};
        }

        math::vec2 unit::world_position()
        {
            return _world_position;
        }

        direction_e& unit::direction()
        {
            return _direction;
        }

        unit_p create_unit(int32_t x,
                           int32_t y,
                           const std::string& texture_0,
                           const std::string& texture_1,
                           const std::string& texture_2,
                           const std::string& texture_3)
        {
            return std::make_shared<unit>(x, y, texture_0, texture_1, texture_2, texture_3);
        }
    }
}
