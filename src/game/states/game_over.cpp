#include <game/states/game_over.h>

#include <events/event.h>
#include <game/game.h>
#include <game/game_state_machine.h>
#include <game/states/level.h>
#include <input/keyboard_key.h>
#include <rendering/camera.h>

using namespace tg;

GameOverGameState::GameOverGameState(GameStateMachine& p_stateMachine, Game& p_game, bool p_win)
    : GameState(p_stateMachine, p_game)
    , m_win(p_win)
{
    auto& textureManager = p_game.textureManager();
    m_texture = textureManager.getTexture(m_win ? "images/you_won" : "images/game_over");

    initializeEventHandlers();
}

void GameOverGameState::update()
{}

void GameOverGameState::render(Canvas& p_canvas)
{
    p_canvas.draw(m_texture->texture, Rect{ { 0, 0 }, game().windowSize() });
}

void GameOverGameState::initializeEventHandlers()
{
    addEventHandler<KeyboardKey>([this](const KeyboardKey& p_event) {
        if (p_event.key == EKeyboardKey::ESC)
        {
            game().shutdown();
            return;
        }

        stateMachine().pushState<LevelGameState>();
    });
}
