#pragma once

#include <cstdint>

namespace tg
{
    template<typename ValueType>
    struct Vec2
    {
        ValueType x, y;

        Vec2()
            : Vec2(0, 0)
        {}

        Vec2(ValueType p_x, ValueType p_y)
            : x(p_x)
            , y(p_y)
        {}

        ValueType cross(const Vec2& p_other) { return (x * p_other.y) - (y * p_other.x); }

        ValueType cross(const Vec2& p_zero, const Vec2& p_other)
        {
            Vec2 a = { x - p_zero.x, y - p_zero.y };
            Vec2 b = { p_other.x - p_zero.x, p_other.y - p_zero.y };
            return a.cross(b);
        }

        bool operator==(const Vec2& p_other) const { return x == p_other.x && y == p_other.y; }
        bool operator!=(const Vec2& p_other) const { return x != p_other.x || y != p_other.y; }

        Vec2 operator+(const Vec2& p_other) const
        {
            Vec2 result = *this;
            result.x += p_other.x;
            result.y += p_other.y;
            return result;
        }

        Vec2 operator-(const Vec2& p_other) const
        {
            Vec2 result = *this;
            result.x -= p_other.x;
            result.y -= p_other.y;
            return result;
        }

        template<typename ScalarType>
        Vec2 operator/(ScalarType p_scalar) const
        {
            Vec2 result = *this;
            result.x /= p_scalar;
            result.y /= p_scalar;
            return result;
        }

        template<typename ScalarType>
        Vec2 operator*(ScalarType p_scalar) const
        {
            Vec2 result = *this;
            result.x *= p_scalar;
            result.y *= p_scalar;
            return result;
        }

        Vec2& operator+=(const Vec2& p_other)
        {
            this->x += p_other.x;
            this->y += p_other.y;
            return *this;
        }
    };

    using Vec2i = Vec2<std::int32_t>;
    using Vec2f = Vec2<float>;
}
