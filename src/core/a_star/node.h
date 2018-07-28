#pragma once

// project includes
#include "math/vec2.h"

// STL includes
#include <memory>
#include <set>

namespace core
{
    namespace a_star
    {
        struct node;
        typedef std::shared_ptr<node> node_p;
        typedef std::set<node_p> node_set;

        struct node
        {
            math::vec2 coordinates;
            node_p parent;

            uint32_t G;
            uint32_t H;

            explicit node( const math::vec2& coordinates, node_p parent = node_p() );

            uint32_t get_score();
        };

        node_p create_node( const math::vec2& coordinates, node_p parent = node_p() );
    }
}
