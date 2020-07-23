#include <game/systems/visual_system.h>

#include <ecs/registry.h>
#include <game/systems/movement_system.h>

using namespace tg;

void VisualSystem::update(Registry& p_registry)
{
    auto view = p_registry.view<Direction, Visual>();
    for (auto [_, direction, visual] : view)
    {
        if (direction.value == Vec2i{ 0, 1 })
        {
            visual.current = visual.textures[0];
        }
        else if (direction.value == Vec2i{ -1, 0 })
        {
            visual.current = visual.textures[1];
        }
        else if (direction.value == Vec2i{ 0, -1 })
        {
            visual.current = visual.textures[2];
        }
        else if (direction.value == Vec2i{ 1, 0 })
        {
            visual.current = visual.textures[3];
        }
    }
}
