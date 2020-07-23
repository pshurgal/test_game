#pragma once

#include <cassert>
#include <functional>

namespace tg
{
    class RAIIGuard
    {
    public:
        using activate_func = std::function<void()>;
        using deactivate_func = std::function<void()>;

    public:
        RAIIGuard(activate_func p_activate, deactivate_func p_deactivate)
            : m_activate(std::move(p_activate))
            , m_deactivate(std::move(p_deactivate))
        {
            assert(m_activate && m_deactivate);
            m_activate();
        }

        ~RAIIGuard() { m_deactivate(); }

    private:
        activate_func   m_activate;
        deactivate_func m_deactivate;
    };
}
