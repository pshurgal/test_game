#include "game.h"

// project includes
#include "event_loop.h"
#include "core/sdl_types_factory.h"
#include "game_screen_manager.h"
#include "game_scene_renderer.h"
#include "game_screens/level_game_screen.h"
#include "core/logger.h"

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
                                                     SDL_WINDOW_SHOWN );

            _renderer = sdl_types_factory::get_renderer( _window, -1, SDL_RENDERER_ACCELERATED );

            _game_scene_renderer.set_renderer( _renderer );

            game_screen_manager::instance().push_game_screen(
                    create_game_screen<game_screens::level_game_screen>( _renderer ) );
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

            _game_scene_renderer.render( screen->scene(), screen->state() );
        }

        return 0;
    }

    void game::signal_shutdown()
    {
        _shutdown_signalled = true;
    }
}
