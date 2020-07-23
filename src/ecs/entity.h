#pragma once

#include <container/sparse_map.h>
#include <utils/generic_handle.h>

#include <cstdint>
#include <functional>

namespace tg
{
    class Registry;

    class Entity: public GenericHandle<std::uint32_t, 16, 16>
    {
    public:
        static const Entity INVALID;

    public:
        constexpr Entity()
            : Entity(0xFFFF, 0xFFFF)
        {}

        constexpr Entity(const Entity& p_other)
            : Entity(p_other.handle(), p_other.generation())
        {}

    private:
        friend class Registry;
        constexpr Entity(underlying_type p_handle, underlying_type m_generation)
            : GenericHandle(p_handle, m_generation)
        {}
    };

    template<>
    struct SparseIndex<Entity>
    {
        std::size_t operator()(const Entity& p_entity) const noexcept
        {
            return static_cast<std::size_t>(p_entity.handle());
        }
    };
}

namespace std
{
    template<>
    struct hash<tg::Entity>
    {
        std::size_t operator()(const tg::Entity& p_entity) const noexcept
        {
            return hash<std::uint32_t>{}(p_entity.handle() | p_entity.generation());
        }
    };
}
