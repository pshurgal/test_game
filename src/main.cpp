#include "core/game.h"
#include "core/logger.h"

#include <iostream>

using namespace std;
using namespace core;

int
    main()
{
    int result = 0;

    try
    {
        logger::instance().init();
        result = game::instance().exec();
    }
    catch(std::exception& e)
    {
        LOG(FATAL) << e.what();
    }

    return result;
}
