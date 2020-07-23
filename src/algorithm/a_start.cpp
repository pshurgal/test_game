#include <algorithm/a_start.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <memory>
#include <queue>
#include <unordered_set>

using namespace tg;

namespace
{
    const std::vector<Vec2i> s_directions = { { 0, 1 }, { -1, 0 }, { 0, -1 }, { 1, 0 } };

    struct Node
    {
        Vec2i         coordinates;
        std::int32_t  parent;
        std::uint32_t G;
        std::uint32_t H;

        Node(Vec2i p_coord, std::int32_t p_parent, std::uint32_t p_g = 0, std::uint32_t p_h = 0)
            : coordinates(p_coord)
            , parent(p_parent)
            , G(p_g)
            , H(p_h)
        {}

        std::uint32_t score() const { return G + H; }
    };

    Node* findNode(std::vector<Node>&                      p_allNodes,
                   const std::unordered_set<std::int32_t>& p_nodesSet,
                   const Vec2i&                            p_coordinates)
    {
        auto it =
            std::find_if(p_nodesSet.begin(), p_nodesSet.end(), [&p_allNodes, &p_coordinates](std::int32_t p_index) {
                return p_allNodes[p_index].coordinates == p_coordinates;
            });

        return it != p_nodesSet.end() ? &p_allNodes[*it] : nullptr;
    }

    std::uint32_t heuristic(const Vec2i& p_from, const Vec2i& p_to)
    {
        auto delta = Vec2i{ std::abs(p_to.x - p_from.x), std::abs(p_to.y - p_from.y) };
        return std::uint32_t(std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2)));
    }
}

std::vector<Vec2i> AStar::findPath(const Vec2i&                      p_from,
                                   const Vec2i&                      p_to,
                                   std::function<bool(const Vec2i&)> p_isReachable)
{
    std::int32_t                     current = -1;
    std::vector<Node>                allNodes;
    std::unordered_set<std::int32_t> openSet;
    std::unordered_set<std::int32_t> closedSet;

    auto& n = allNodes.emplace_back(p_from, -1);

    openSet.insert(static_cast<std::int32_t>(allNodes.size() - 1));

    while (!openSet.empty())
    {
        current = *openSet.begin();

        for (auto& nodeIndex : openSet)
        {
            auto& node = allNodes[nodeIndex];
            if (node.score() <= allNodes[current].score())
            {
                current = nodeIndex;
            }
        }

        if (allNodes[current].coordinates == p_to)
        {
            break;
        }

        closedSet.insert(current);
        openSet.erase(current);

        for (const auto& direction : s_directions)
        {
            Vec2i newCoordinates = allNodes[current].coordinates + direction;
            if (!p_isReachable(newCoordinates) || findNode(allNodes, closedSet, newCoordinates))
            {
                continue;
            }

            std::uint32_t totalCost = allNodes[current].G;

            auto successor = findNode(allNodes, openSet, newCoordinates);
            if (!successor)
            {
                auto& newNode =
                    allNodes.emplace_back(newCoordinates, current, totalCost, heuristic(newCoordinates, p_to));

                openSet.insert(static_cast<std::int32_t>(allNodes.size() - 1));

                continue;
            }

            if (totalCost < successor->G)
            {
                successor->parent = current;
                successor->G = totalCost;
            }
        }
    }

    std::vector<Vec2i> path;
    while (current != -1)
    {
        path.push_back(allNodes[current].coordinates);
        current = allNodes[current].parent;
    }
    path.pop_back();

    return path;
}
