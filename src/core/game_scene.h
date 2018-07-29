#pragma once

// project includes
#include "drawable.h"

// STL includes
#include <memory>

namespace core
{
    class game_scene;

    typedef std::shared_ptr<game_scene> game_scene_p;

    template<class T, typename... Args>
    game_scene_p create_game_scene(Args... args)
    {
        static_assert(std::is_base_of<game_scene, T>::value);
        return game_scene_p(new T(args...));
    }

    class game_scene : public drawable
    {
    };
}
