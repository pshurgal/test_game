#pragma once

// STL includes
#include <cstdint>

namespace math
{
    struct vec2
    {
        int32_t x, y;

        vec2( int32_t x, int32_t y )
                : x( x )
                , y( y )
        {
        }

        int32_t cross( const vec2& other )
        {
            return (x * other.y) - (y * other.x);
        }

        int32_t cross( const vec2& zero, const vec2& other )
        {
            vec2 a = { x - zero.x, y - zero.y };
            vec2 b = { other.x - zero.x, other.y - zero.y };
            return a.cross( b );
        }
    };
}