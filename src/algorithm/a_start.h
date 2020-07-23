#pragma once

#include <math/vec2.h>

#include <functional>
#include <stack>
#include <unordered_set>
#include <vector>

namespace tg
{
    class AStar
    {
    public:
        static std::vector<Vec2i> findPath(const Vec2i&                      p_from,
                                           const Vec2i&                      p_to,
                                           std::function<bool(const Vec2i&)> p_isReachable);

    private:
        AStar() = delete;
    };
}
