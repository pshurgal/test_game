#include "level_game_state.h"

namespace core
{
    namespace game_states
    {

        void level_game_state::update()
        {
            if(!player_path.empty())
            {
                player->move(gameplay::direction_e::LEFT_DOWN);
                player_path.pop_back();
            }
        }
    }
}
