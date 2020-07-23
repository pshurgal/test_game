#include <game/systems/movement_system.h>

#include <ecs/registry.h>

using namespace tg;

void MovementSystem::update(Registry& p_registry)
{
    auto view = p_registry.view<Position, Direction>();
    for (auto [_, position, direction] : view)
    {
        position.value += direction.value;
    }
}
