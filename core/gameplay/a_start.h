#pragma once

#include "math/vec2.h"
#include "cell_field.h"
#include <list>
#include <unordered_map>

namespace core
{
    namespace gameplay
    {
        class a_start
        {
        public:
            static std::list<math::vec2> get_path( const math::vec2& from, const math::vec2& to,
                                                   cell_field_p cell_field );

        private:
//            static std::unordered_map<   a_star( const math::vec2& from, const math::vec2& to,
//                                                            cell_field_p cell_field );
//            static std::list<math::vec2> restore_path( const std::map<math::vec2, math::vec2>& came_from);
        };
    }
}

