#include "vec2.h"

namespace math
{

    vec2::vec2( int32_t x, int32_t y )
            : x( x )
            , y( y )
    {
    }

    int32_t vec2::cross( const vec2& other )
    {
        return (x * other.y) - (y * other.x);
    }

    int32_t vec2::cross( const vec2& zero, const vec2& other )
    {
        vec2 a = { x - zero.x, y - zero.y };
        vec2 b = { other.x - zero.x, other.y - zero.y };
        return a.cross( b );
    }

    bool vec2::operator==( const vec2& other )
    {
        return x == other.x && y == other.y;
    }

    vec2 vec2::operator+( const vec2& other )
    {
        vec2 result = *this;
        result.x += other.x;
        result.y += other.y;
        return result;
    }
}
