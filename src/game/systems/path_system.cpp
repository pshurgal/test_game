#include <game/systems/path_system.h>

#include <ecs/registry.h>
#include <game/systems/movement_system.h>

using namespace tg;

void PathSystem::update(Registry& p_registry)
{
    auto view = p_registry.view<Path, Direction, Position>();
    for (auto [_, path, direction, position] : view)
    {
        if (path.value.empty())
        {
            direction.value = Vec2i{ 0, 0 };
            continue;
        }

        direction.value = path.value.back() - position.value;
        path.value.pop_back();
    }
}
