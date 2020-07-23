#pragma once

#include <math/vec2.h>

#include <array>
#include <cstdint>
#include <functional>
#include <vector>

namespace tg
{
    struct Patrol
    {
        std::array<Vec2i, 2> points;
        std::int32_t         destination;


        Patrol(std::array<Vec2i, 2> p_points, std::int32_t p_destination)
            : points(p_points)
            , destination(p_destination)
        {}
    };

    class Registry;

    class PatrolSystem
    {
    public:
        using FindPathFunc = std::function<std::vector<Vec2i>(const Vec2i&, const Vec2i&)>;

    public:
        PatrolSystem(FindPathFunc p_findPath)
            : m_findPath(std::move(p_findPath))
        {}

        void update(Registry& p_registry);

    private:
        FindPathFunc m_findPath;
    };
}
