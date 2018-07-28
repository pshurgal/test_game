#include "a_start.h"

// project includes
#include "core/gameplay/direction.h"

// STL includes
#include <cmath>
#include <map>

namespace core
{
    namespace a_star
    {
        node_p find_node( const node_set& set, const math::vec2& coordinates )
        {
            node_p result;
            for( auto& node : set )
            {
                if( node->coordinates == coordinates )
                    result = node;
            }

            return result;
        }

        bool detect_collision( const gameplay::tile_field_p& tile_field, const math::vec2& coordinates )
        {
            return coordinates.x < 0 ||
                   coordinates.y < 0 ||
                   coordinates.x >= tile_field->width() ||
                   coordinates.y >= tile_field->height() ||
                   !tile_field->tile_reachable( size_t( coordinates.x ), size_t( coordinates.y ) );
        }

        uint32_t heuristic( const math::vec2& from, const math::vec2& to )
        {
            auto delta = math::vec2{ std::abs( to.x - from.x ), std::abs( to.y - from.y ) };
            return uint32_t( std::sqrt( std::pow( delta.x, 2 ) + std::pow( delta.y, 2 ) ) );
        }

        std::list<gameplay::direction_e> get_path( const math::vec2& from, const math::vec2& to,
                                                   gameplay::tile_field_p tile_field )
        {
            node_p current = nullptr;
            node_set open_set, closed_set;

            open_set.insert( create_node( from ) );

            while( !open_set.empty() )
            {
                current = *open_set.begin();
                for( const auto& node : open_set )
                {
                    if( node->get_score() <= current->get_score() )
                    {
                        current = node;
                    }
                }

                if( current->coordinates == to )
                {
                    break;
                }

                closed_set.insert( current );
                open_set.erase( std::find( open_set.begin(), open_set.end(), current ) );

                for( const auto& direction : gameplay::direction_array )
                {
                    math::vec2 new_coordinates = current->coordinates + gameplay::direction_to_vec2( direction );
                    if( detect_collision( tile_field, new_coordinates ) ||
                        find_node( closed_set, new_coordinates ) )
                    {
                        continue;
                    }

                    uint32_t total_cost = current->G;

                    node_p successor = find_node( open_set, new_coordinates );
                    if( successor == nullptr )
                    {
                        successor = create_node( new_coordinates, current );
                        successor->direction = direction;
                        successor->G = total_cost;
                        successor->H = heuristic( successor->coordinates, to );
                        open_set.insert( successor );
                    } else if( total_cost < successor->G )
                    {
                        successor->parent = current;
                        successor->G = total_cost;
                    }
                }
            }

            std::list<gameplay::direction_e> path;
            while( current != nullptr )
            {
                path.push_back( current->direction );
                current = current->parent;
            }
            path.pop_back();

            return path;
        }
    }
}