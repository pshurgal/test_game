#pragma once

#include <container/sparse_map.h>
#include <ecs/components_view.h>
#include <ecs/entity.h>

#include <cassert>
#include <chrono>
#include <typeindex>

namespace tg
{
    template<typename ComponentType>
    class Pool;

    class PoolBase
    {
    public:
        virtual ~PoolBase() = default;

        PoolBase() = default;

        PoolBase(const PoolBase&) = delete;
        PoolBase(PoolBase&&) = delete;

        PoolBase& operator=(const PoolBase&) = delete;
        PoolBase& operator=(PoolBase&&) = delete;
    };

    template<typename ComponentType>
    class Pool: public PoolBase
    {
    public:
        template<typename... Args>
        ComponentType& addComponent(Entity p_entity, Args&&... p_args)
        {
            return m_components.emplace(p_entity, std::forward<Args>(p_args)...).second;
        }

        ComponentType& getComponent(Entity p_entity)
        {
            assert(hasComponent(p_entity));
            return m_components.at(p_entity);
        }

        void removeComponent(Entity p_entity) { m_components.erase(p_entity); }

        bool hasComponent(Entity p_entity)
        {
            const auto it = m_components.find(p_entity);
            return it != m_components.end();
        }

        const std::vector<Entity>& entities() const { return m_components.keys(); }

    protected:
        SparseMap<Entity, ComponentType> m_components;
    };
}
