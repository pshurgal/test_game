#pragma once

// project includes
#include "node.h"
#include "math/vec2.h"
#include "core/gameplay/cell_field.h"

// STL includes
#include <list>

namespace core
{
    namespace a_star
    {
        std::list<math::vec2> get_path( const math::vec2& from, const math::vec2& to,
                                               gameplay::cell_field_p cell_field );
    }
}

