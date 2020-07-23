#pragma once

#include <algorithm/a_start.h>
#include <ecs/registry.h>
#include <events/event_handler.h>
#include <game/field/tile_field.h>
#include <game/game_state.h>
#include <game/game_state_machine.h>
#include <game/systems/damage_system.h>
#include <game/systems/despawn_system.h>
#include <game/systems/movement_system.h>
#include <game/systems/path_system.h>
#include <game/systems/patrol_system.h>
#include <game/systems/visual_system.h>
#include <rendering/camera.h>
#include <resources/texture_manager.h>

#include <list>
#include <memory>
#include <vector>

namespace tg
{
    class LevelGameState: public GameState
    {
    public:
        explicit LevelGameState(GameStateMachine& p_stateMachine, Game& p_game);

        void update() override;
        void render(Canvas& p_canvas) override;

    private:
        void initializeEventHandlers();

        bool isLoss();
        bool isWin();

        std::vector<Vec2i> findPath(const Vec2i& p_from, const Vec2i p_to);

        void handleMouseButton(EMouseButton p_button, const Vec2i& p_clickPoint);
        void handleKeyboardKey(EKeyboardKey p_key);

    private:
        Camera m_camera;

        TileField m_tileField;

        Registry m_registry;

        MovementSystem m_movementSystem;
        PathSystem     m_pathSystem;
        DespawnSystem  m_despawnSystem;
        VisualSystem   m_visualSystem;
        DamageSystem   m_damageSystem;
        PatrolSystem   m_patrolSystem;

        Entity m_player;
        Entity m_guard;
        Entity m_bed;

        Vec2i m_playerDestinationPoint;

        std::vector<TextureManager::Token> m_playerTextures;
        std::vector<TextureManager::Token> m_guardTextures;
        std::vector<TextureManager::Token> m_spikedBallTextures;
        TextureManager::Token              m_bedTexture;
    };
}
