#include <game/systems/damage_system.h>

#include <ecs/registry.h>
#include <game/systems/movement_system.h>

using namespace tg;

void DamageSystem::update(Registry& p_registry)
{
    auto healthView = p_registry.view<Position, Health>();
    auto damageView = p_registry.view<Position, Damage>();

    for (auto [_, healthPosition, health] : healthView)
    {
        for (auto [__, damagePosition, damage] : damageView)
        {
            if (healthPosition.value != damagePosition.value)
                continue;

            health.value -= damage.value;
        }
    }
}
