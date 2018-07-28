#pragma once

// project includes
#include "node.h"
#include "math/vec2.h"
#include "core/gameplay/tile_field.h"

// STL includes
#include <list>

namespace core
{
    namespace a_star
    {
        std::list<gameplay::direction_e> get_path( const math::vec2& from, const math::vec2& to,
                                               gameplay::tile_field_p tile_field );
    }
}

