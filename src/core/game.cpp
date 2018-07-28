#include "game.h"

// project includes
#include "event_loop.h"
#include "sdl_types_factory.h"
#include "game_screen_manager.h"
#include "game_scene_renderer.h"
#include "core/game_screens/level_game_screen.h"
#include "logger.h"
#include "texture_manager.h"

// thirdparty includes
#define SDL_MAIN_HANDLED

#include "SDL2/SDL.h"

namespace core
{
    game::game()
    {
        SDL_Init( SDL_INIT_EVERYTHING );

        try
        {
            _window = sdl_types_factory::get_window( "The Game",
                                                     SDL_WINDOWPOS_UNDEFINED,
                                                     SDL_WINDOWPOS_UNDEFINED,
                                                     SCREEN_WIDTH,
                                                     SCREEN_HEIGHT,
                                                     SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

            _renderer = sdl_types_factory::get_renderer( _window, -1, SDL_RENDERER_ACCELERATED );

            _game_scene_renderer.set_renderer( _renderer );

            load_textures();

            game_screen_manager::instance().push_game_screen(
                    create_game_screen<game_screens::level_game_screen>() );

        } catch( std::exception& ex )
        {
            SDL_Quit();
            LOG( ERROR ) << "Game object initialize error";
            throw ex;
        }
    }

    game::~game()
    {
        SDL_Quit();
    };

    game& game::instance()
    {
        static game _game;
        return _game;
    }

    int game::exec()
    {
        while( !_shutdown_signalled )
        {
            auto screen = game_screen_manager::instance().current_screen();

            event_loop::instance().process( screen->event_handlers(), screen->state() );

            screen->state()->update();

            _game_scene_renderer.render( screen->scene(), screen->state() );
        }

        return 0;
    }

    void game::signal_shutdown()
    {
        _shutdown_signalled = true;
    }

    void game::load_textures()
    {
        texture_manager::instance().load_texture( "../share/test_game/images/ground_tile.png", "ground_tile",
                                                  _renderer );
        texture_manager::instance().load_texture( "../share/test_game/images/lava_tile.png", "lava_tile",
                                                  _renderer );

        texture_manager::instance().load_texture( "../share/test_game/images/player_0.png", "player_0", _renderer );
        texture_manager::instance().load_texture( "../share/test_game/images/player_1.png", "player_1", _renderer );
        texture_manager::instance().load_texture( "../share/test_game/images/player_2.png", "player_2", _renderer );
        texture_manager::instance().load_texture( "../share/test_game/images/player_3.png", "player_3", _renderer );
        texture_manager::instance().load_texture( "../share/test_game/images/guard_0.png", "guard_0", _renderer );
        texture_manager::instance().load_texture( "../share/test_game/images/guard_1.png", "guard_1", _renderer );
        texture_manager::instance().load_texture( "../share/test_game/images/guard_2.png", "guard_2", _renderer );
        texture_manager::instance().load_texture( "../share/test_game/images/guard_3.png", "guard_3", _renderer );

        texture_manager::instance().load_texture( "../share/test_game/images/bed.png", "bed", _renderer );

        texture_manager::instance().load_texture( "../share/test_game/images/game_over.png", "game_over", _renderer );
        texture_manager::instance().load_texture( "../share/test_game/images/you_won.png", "you_won", _renderer );
    }
}
