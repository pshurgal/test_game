#include <game/systems/patrol_system.h>

#include <ecs/registry.h>
#include <game/systems/movement_system.h>
#include <game/systems/path_system.h>

using namespace tg;

void tg::PatrolSystem::update(Registry& p_registry)
{
    auto view = p_registry.view<Patrol, Position, Path>();
    for (auto [_, patrol, position, path] : view)
    {
        if (position.value != patrol.points[patrol.destination])
            continue;

        const auto currentPoint = patrol.destination;
        patrol.destination = (patrol.destination + 1) % 2;
        path.value = m_findPath(patrol.points[currentPoint], patrol.points[patrol.destination]);
    }
}
