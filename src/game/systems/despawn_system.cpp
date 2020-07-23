#include <game/systems/despawn_system.h>

#include <ecs/registry.h>
#include <game/systems/movement_system.h>

using namespace tg;

void DespawnSystem::update(Registry& p_registry)
{
    std::vector<Entity> candidates;

    auto view = p_registry.view<Position>();

    for (auto [entity, position] : view)
    {
        if (position.value.x < 0 || position.value.y < 0 || position.value.x >= m_fieldSize.x
            || position.value.y >= m_fieldSize.y)
        {
            candidates.push_back(entity);
        }
    }

    for (auto entity : candidates)
    {
        p_registry.destroyEntity(entity);
    }
}
