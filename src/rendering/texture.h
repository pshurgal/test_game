#pragma once

#include <utils/generic_handle.h>

#include <cstdint>
#include <functional>

namespace tg
{
    class Texture: public GenericHandle<std::uint32_t, 16, 16>
    {
    public:
        constexpr Texture()
            : Texture(0xFFFF, 0xFFFF)
        {}

        constexpr Texture(std::uint32_t p_handle, std::uint32_t p_generation)
            : GenericHandle(p_handle, p_generation)
        {}

        static const Texture INVALID;
    };
}

namespace std
{
    template<>
    struct hash<tg::Texture>
    {
        std::size_t operator()(const tg::Texture& p_texture) const noexcept
        {
            return hash<std::uint32_t>{}(p_texture.handle() | p_texture.generation());
        }
    };
}
