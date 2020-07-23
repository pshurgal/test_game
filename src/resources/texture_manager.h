#pragma once

#include <rendering/rendering_backend.h>
#include <rendering/texture.h>

#include <filesystem>
#include <string>
#include <unordered_map>
#include <utility>

namespace tg
{
    class TextureManager
    {
    public:
        struct TextureHandle
        {
            std::string path;
            Texture     texture;
        };

        using Token = std::shared_ptr<TextureHandle>;

    public:
        explicit TextureManager(RenderingBackend& p_backend)
            : m_backend(p_backend)
        {}

        Token getTexture(const std::string& p_path);

    private:
        RenderingBackend& m_backend;

        std::unordered_map<std::string, std::pair<std::size_t, Texture>> m_cache;
    };
}
