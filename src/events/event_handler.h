#pragma once

#include <events/event.h>

#include <functional>

namespace tg
{
    template<typename EventType>
    using EventHandler = std::function<void(const EventType& e)>;
}
