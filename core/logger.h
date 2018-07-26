#pragma once

// project includes

// thirdparty includes
#include "g3log/g3log.hpp"
#include "g3log/logworker.hpp"

// STL includes

namespace core
{
    const LEVELS ERROR{ 700, { "ERROR" } };

    class logger
    {
        logger();

    public:
        static logger& instance();

        void init();

    private:
        std::unique_ptr <g3::LogWorker> _worker;
    };
}
