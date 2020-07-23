#pragma once

#include <container/sparse_map.h>
#include <ecs/entity.h>
#include <ecs/pool.h>

#include <tuple>

namespace tg
{
    template<typename... ComponentTypes>
    class ComponentsViewIterator
    {
    public:
        ComponentsViewIterator(typename std::vector<Entity>::iterator p_it,
                               std::tuple<Pool<ComponentTypes>&...>   p_pools)
            : m_it(std::move(p_it))
            , m_pools(std::move(p_pools))
        {}

        ComponentsViewIterator(const ComponentsViewIterator& p_other)
            : ComponentsViewIterator(p_other.m_it, p_other.m_pools)
        {}

        bool operator!=(const ComponentsViewIterator& p_other) const { return m_it != p_other.m_it; }

        [[nodiscard]] std::tuple<Entity, ComponentTypes&...> operator*() const
        {
            const auto entity = *m_it;
            return { entity, std::get<Pool<ComponentTypes>&>(m_pools).getComponent(entity)... };
        }

        ComponentsViewIterator& operator++()
        {
            ++m_it;
            return *this;
        }

    private:
        typename std::vector<Entity>::iterator m_it;
        std::tuple<Pool<ComponentTypes>&...>   m_pools;
    };

    template<typename... ComponentTypes>
    class ComponentsView
    {
    public:
        using iterator = ComponentsViewIterator<ComponentTypes...>;

    public:
        ComponentsView(std::vector<Entity> p_candidates, std::tuple<Pool<ComponentTypes>&...> p_pools)
            : m_candidates(std::move(p_candidates))
            , m_pools(p_pools)
        {}

        iterator begin() { return { m_candidates.begin(), m_pools }; }
        iterator end() { return { m_candidates.end(), m_pools }; }

        std::size_t size() const { return m_candidates.size(); }

    private:
        std::vector<Entity>                  m_candidates;
        std::tuple<Pool<ComponentTypes>&...> m_pools;
    };
}
