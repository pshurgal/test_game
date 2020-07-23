#pragma once

#include <events/event_handler.h>
#include <game/game_state.h>
#include <rendering/camera.h>
#include <resources/texture_manager.h>

namespace tg
{
    class GameOverGameState: public GameState
    {
    public:
        explicit GameOverGameState(GameStateMachine& p_stateMachine, Game& p_game, bool p_win);

        void update() override;
        void render(Canvas& p_canvas) override;

    private:
        void initializeEventHandlers();

    private:
        bool m_win = false;

        TextureManager::Token m_texture;
    };
}
