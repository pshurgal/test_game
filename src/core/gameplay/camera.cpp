#include "camera.h"

// project includes
#include "core/game.h"

namespace core
{
    namespace gameplay
    {
        int32_t camera::x()
        {
            return _x + game::SCREEN_WIDTH / 2;
        }

        int32_t camera::y()
        {
            return _y + game::SCREEN_HEIGHT / 2;
        }

        void camera::move_to(int32_t x, int32_t y)
        {
            _x = x;
            _y = y;
        }

        void camera::move_rel(int32_t x, int32_t y)
        {
            _x += x;
            _y += y;
        }

        math::vec2 camera::screen_coords_to_world_coords(int32_t x, int32_t y)
        {
            return {x - camera::x(), y - camera::y()};
        }
    }
}
