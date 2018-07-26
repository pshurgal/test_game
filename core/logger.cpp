#include "logger.h"

// STL includes
#include <iostream>

namespace core
{
    struct console_sink
    {
        void receive_log_message( g3::LogMessageMover logEntry )
        {
            auto level = logEntry.get()._level;

            std::cout << logEntry.get().toString() << std::endl;
        }
    };

    logger::logger()
            : _worker( g3::LogWorker::createLogWorker() )
    {
        _worker->addSink( std::make_unique<console_sink>(),
                          &console_sink::receive_log_message );

        g3::only_change_at_initialization::addLogLevel( ERROR );

        g3::initializeLogging( _worker.get() );
    }

    logger& logger::instance()
    {
        static logger _logger;
        return _logger;
    }

    void logger::init()
    {
        LOG( INFO ) << "Logging initialized";
    }
}
