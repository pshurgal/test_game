#include "level_game_scene.h"

// project includes
#include "core/texture_manager.h"
#include "core/game_states/level_game_state.h"
#include "core/gameplay/tile.h"

// STL includes
#include <vector>
#include <list>

namespace core
{
    namespace game_scenes
    {
        void level_game_scene::render( game_state_p game_state, renderer_p renderer )
        {
            auto state_converted = dynamic_cast<game_states::level_game_state*>(game_state.get());
            if( state_converted )
            {
                state_converted->tile_field->render(game_state,renderer);

                std::vector<std::list<gameplay::unit_p>> rendering_order(state_converted->tile_field->height());

                rendering_order[ state_converted->bed->field_position().y ].push_back(state_converted->bed);
                rendering_order[ state_converted->player->field_position().y ].push_back(state_converted->player);
                rendering_order[ state_converted->guard->field_position().y ].push_back(state_converted->guard);
                
                for( auto& boulder_spike : state_converted->boulder_spikes )
                {
                    rendering_order[ boulder_spike->field_position().y ].push_back(boulder_spike);
                }

                for( auto& list: rendering_order )
                {
                    list.sort([](gameplay::unit_p a, gameplay::unit_p b){
                        return a->field_position().x < b->field_position().x;
                    });

                    for(auto& unit : list )
                    {
                        unit->render(game_state,renderer);
                    }
                }
            }
        }
    }
}