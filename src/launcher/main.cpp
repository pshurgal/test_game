#include <launcher/main.h>

#include <ecs/registry.h>
#include <game/game.h>

#include <iostream>

using namespace tg;

int tg::Main(int argc, char* argv[])
{
    int result = 0;

    try
    {
        result = Game{}.exec();
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
    }

    return result;

    return 0;
}
