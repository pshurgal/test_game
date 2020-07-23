#include <resources/texture_manager.h>

#include <graphics/bitmap_loader.h>

using namespace tg;

TextureManager::Token TextureManager::getTexture(const std::string& p_path)
{
    auto unloader = [this](TextureHandle* p_handle) {
        auto& cacheEntry = m_cache.at(p_handle->path);

        auto& activeTokens = cacheEntry.first;

        activeTokens -= 1;

        if (activeTokens == 0)
        {
            m_backend.destroyTexture(p_handle->texture);
            m_cache.erase(p_handle->path);
        }

        delete p_handle;
    };

    auto it = m_cache.find(p_path);
    if (it != m_cache.end())
    {
        auto& cacheEntry = it->second;
        auto& activeTokens = cacheEntry.first;

        activeTokens++;

        return { new TextureHandle{ p_path, cacheEntry.second }, unloader };
    }

    auto bitmap = BitmapLoader::load(p_path + ".png");
    if (!bitmap)
    {
        return {};
    }

    auto tex = m_backend.createTexture(*bitmap);
    if (tex == Texture::INVALID)
    {
        return {};
    }

    m_cache.emplace(p_path, std::pair<std::size_t, Texture>(1, tex));

    return { new TextureHandle{ p_path, tex }, unloader };
}
