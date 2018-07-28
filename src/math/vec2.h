#pragma once

// STL includes
#include <cstdint>

namespace math
{
    struct vec2
    {
        int32_t x, y;

        vec2( int32_t x, int32_t y );

        int32_t cross( const vec2& other );

        int32_t cross( const vec2& zero, const vec2& other );

        bool operator==( const vec2& other );

        vec2 operator+( const vec2& other );

        vec2& operator+=( const vec2& other );
    };
}