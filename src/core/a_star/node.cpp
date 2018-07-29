#include "node.h"

namespace core
{
    namespace a_star
    {
        node::node(const math::vec2& coordinates, core::a_star::node_p parent)
            : coordinates(coordinates)
            , parent(std::move(parent))
            , G(0)
            , H(0)
        {
        }

        uint32_t node::get_score()
        {
            return G + H;
        }

        node_p create_node(const math::vec2& coordinates, node_p parent)
        {
            return std::make_shared<node>(coordinates, std::move(parent));
        }
    }
}
