#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>

namespace tg
{
    template<typename UnderlyingType, std::size_t HandleSize, std::size_t GenerationSize>
    class GenericHandle
    {
        static_assert(std::is_integral<UnderlyingType>::value);
        static_assert((HandleSize + GenerationSize) / 8 == sizeof(UnderlyingType));

    public:
        using underlying_type = UnderlyingType;

    public:
        constexpr GenericHandle()
            : GenericHandle(0, 0)
        {}

        constexpr GenericHandle(underlying_type p_handle, underlying_type p_generation)
            : m_handle(p_handle)
            , m_generation(p_generation)
        {}

        constexpr GenericHandle(const GenericHandle& p_other)
            : GenericHandle(p_other.m_handle, p_other.m_generation)
        {}

        constexpr GenericHandle& operator=(const GenericHandle& p_other)
        {
            m_handle = p_other.m_handle;
            m_generation = p_other.m_generation;
            return *this;
        }

        constexpr bool operator==(const GenericHandle& p_other) const
        {
            return m_handle == p_other.m_handle && m_generation == p_other.m_generation;
        }

        constexpr bool operator!=(const GenericHandle& p_other) const
        {
            return m_handle != p_other.m_handle || m_generation != p_other.m_generation;
        }

        constexpr underlying_type handle() const { return m_handle; }
        constexpr underlying_type generation() const { return m_generation; }

    private:
        underlying_type m_handle: HandleSize;
        underlying_type m_generation: GenerationSize;
    };
}

namespace std
{
    template<typename UnderlyingType, std::size_t HandleSize, std::size_t GenerationSize>
    struct hash<tg::GenericHandle<UnderlyingType, HandleSize, GenerationSize>>
    {
        std::size_t operator()(
            const tg::GenericHandle<UnderlyingType, HandleSize, GenerationSize>& p_handle) const noexcept
        {
            return hash<std::uint32_t>{}(p_handle.handle() | p_handle.generation());
        }
    };
}
