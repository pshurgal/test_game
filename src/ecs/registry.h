#pragma once

#include <ecs/components_view.h>
#include <ecs/entity.h>
#include <ecs/pool.h>

#include <array>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace tg
{
    template<typename... ComponentTypes>
    class ComponentsView;

    class Registry
    {
        struct PoolData
        {
            std::unique_ptr<PoolBase>              pool;
            std::function<void(PoolBase&, Entity)> removeComponent;
        };

    public:
        Entity createEntity()
        {
            if (m_freeIDs.empty())
            {
                const auto id = static_cast<std::uint16_t>(m_generations.size());
                m_generations.push_back(0);
                return { id, 0 };
            }

            const auto id = *(m_freeIDs.begin());
            m_freeIDs.erase(id);

            return { id, m_generations[id] };
        }

        void destroyEntity(Entity p_entity)
        {
            assert(valid(p_entity));
            if (!valid(p_entity))
            {
                return;
            }

            for (auto& [_, poolData] : m_pools)
            {
                poolData.removeComponent(*(poolData.pool), p_entity);
            }

            m_freeIDs.insert(p_entity.handle());
            ++m_generations[p_entity.handle()];
        }

        bool valid(Entity p_entity) const
        {
            return p_entity.handle() < m_generations.size()
                   && p_entity.generation() == m_generations[p_entity.handle()];
        }

        template<typename ComponentType, typename... Args>
        ComponentType& addComponent(Entity p_entity, Args&&... p_args)
        {
            assert(valid(p_entity));
            return getPool<ComponentType>().addComponent(p_entity, std::forward<Args>(p_args)...);
        }

        template<typename ComponentType>
        void removeComponent(Entity p_entity)
        {
            assert(valid(p_entity));
            auto it = m_pools.find(typeid(ComponentType));
            if (it == m_pools.end())
            {
                return;
            }

            it->second.removeComponent(*(it->second.pool), p_entity);
        }

        template<typename ComponentType>
        bool hasComponent(Entity p_entity)
        {
            assert(valid(p_entity));
            auto it = m_pools.find(typeid(ComponentType));
            if (it == m_pools.end())
            {
                return false;
            }

            return getPool<ComponentType>().hasComponent(p_entity);
        }

        template<typename ComponentType>
        ComponentType& getComponent(Entity p_entity)
        {
            assert(valid(p_entity));
            return getPool<ComponentType>().getComponent(p_entity);
        }

        template<typename... ComponentTypes>
        std::tuple<ComponentTypes&...> getComponents(Entity p_entity)
        {
            static_assert(sizeof...(ComponentTypes) > 1);
            assert(valid(p_entity));
            return { getPool<ComponentTypes>().getComponent(p_entity)... };
        }

        template<typename... ComponentTypes>
        ComponentsView<ComponentTypes...> view()
        {
            static_assert(sizeof...(ComponentTypes) > 0, "ComponentTypes must contain at lease one type");
            auto view = candidates<ComponentTypes...>();
            return { std::move(view), { getPool<ComponentTypes>()... } };
        }

    private:
        template<typename ComponentType>
        Pool<ComponentType>& getPool()
        {
            auto it = m_pools.find(typeid(ComponentType));
            if (it != m_pools.end())
            {
                return static_cast<Pool<ComponentType>&>(*(it->second.pool));
            }

            PoolData data;
            data.pool = std::make_unique<Pool<ComponentType>>();
            data.removeComponent = [](PoolBase& p_pool, Entity p_entity) {
                static_cast<Pool<ComponentType>&>(p_pool).removeComponent(p_entity);
            };

            auto pair = m_pools.emplace(typeid(ComponentType), std::move(data));
            return static_cast<Pool<ComponentType>&>(*(pair.first->second.pool));
        }

        template<typename... ComponentTypes>
        std::vector<Entity> candidates()
        {
            return intersect(getPool<ComponentTypes>().entities()...);
        }

        template<typename... Args>
        std::vector<Entity> intersect(Args&&... p_args)
        {
            auto keys = { std::reference_wrapper<const std::vector<Entity>>(std::forward<Args>(p_args))... };

            auto it = std::begin(keys);
            auto end = std::end(keys);

            std::vector<Entity> result;
            result.reserve(it->get().size());

            result.insert(result.end(), it->get().begin(), it->get().end());

            ++it;

            for (; it != end; ++it)
            {
                std::vector<Entity> intersection;
                intersection.reserve(result.size());

                std::set_intersection(
                    result.begin(),
                    result.end(),
                    it->get().begin(),
                    it->get().end(),
                    std::back_inserter(intersection),
                    [](const auto& p_left, const auto& p_right) { return p_left.handle() < p_right.handle(); });

                result.clear();
                result.insert(result.end(), intersection.begin(), intersection.end());
            }

            return result;
        }

    private:
        std::vector<std::uint16_t>        m_generations;
        std::unordered_set<std::uint16_t> m_freeIDs;

        std::unordered_map<std::type_index, PoolData> m_pools;
    };
}
