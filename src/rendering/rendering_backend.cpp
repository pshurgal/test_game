#include <rendering/rendering_backend.h>

#include <utils/raii_guard.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <cassert>
#include <unordered_set>

using namespace tg;

namespace
{
    RAIIGuard s_sdlEnabler{ [] { SDL_Init(SDL_INIT_VIDEO); }, [] { SDL_Quit(); } };

    bool s_instanceExists = false;
}

class RenderingBackend::impl
{
public:
    impl()
    {
        assert(!s_instanceExists && "Only one instance of tg::rendering_backend can exist at one time!");
        s_instanceExists = true;
    }

    ~impl()
    {
        if (m_renderer)
        {
            SDL_DestroyRenderer(m_renderer);
        }

        if (m_window)
        {
            SDL_DestroyWindow(m_window);
        }

        s_instanceExists = false;
    }

    bool initialize(std::string_view p_windowName, const Vec2i& p_windowSize)
    {
        m_window = SDL_CreateWindow(p_windowName.data(),
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    p_windowSize.x,
                                    p_windowSize.y,
                                    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (!m_window)
        {
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
        if (!m_renderer)
        {
            return false;
        }

        return true;
    }

    Texture createTexture(const Bitmap& p_bitmap)
    {
        assert(m_renderer);

        auto tex = SDL_CreateTexture(m_renderer,
                                     p_bitmap.format() == Bitmap::EPixelFormat::RGB ? SDL_PIXELFORMAT_RGB24
                                                                                    : SDL_PIXELFORMAT_RGBA32,
                                     SDL_TEXTUREACCESS_STATIC,
                                     p_bitmap.cols(),
                                     p_bitmap.rows());

        if (!tex)
        {
            return Texture::INVALID;
        }

        if (SDL_UpdateTexture(tex, nullptr, p_bitmap.data(), static_cast<int>(p_bitmap.stride())))
        {
            SDL_DestroyTexture(tex);
            return Texture::INVALID;
        }

        if (p_bitmap.format() == Bitmap::EPixelFormat::RGBA && SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND))
        {
            SDL_DestroyTexture(tex);
            return Texture::INVALID;
        }

        if (m_freeIDs.empty())
        {
            const auto id = static_cast<std::uint16_t>(m_textures.size());
            m_textures.push_back(tex);
            m_generations.push_back(0);
            return { id, 0 };
        }

        const auto id = *m_freeIDs.begin();
        m_textures[id] = tex;

        return { id, m_generations[id] };
    }

    void destroyTexture(Texture p_texture)
    {
        if (!valid(p_texture))
        {
            return;
        }

        auto& tex = m_textures[p_texture.handle()];
        SDL_DestroyTexture(tex);
        tex = nullptr;

        ++m_generations[p_texture.handle()];
    }

    bool valid(Texture p_texture)
    {
        return p_texture.handle() < m_textures.size() && p_texture.generation() == m_generations[p_texture.handle()];
    }

    void draw(Texture p_texture, const Rect& p_rect)
    {
        assert(m_renderer);

        if (!valid(p_texture))
        {
            return;
        }

        auto& tex = m_textures[p_texture.handle()];

        SDL_Rect destRect;

        SDL_QueryTexture(tex, nullptr, nullptr, &destRect.w, &destRect.h);

        destRect.x = p_rect.position.x;
        destRect.y = p_rect.position.y;

        if (p_rect.size.x != -1)
        {
            destRect.w = p_rect.size.x;
        }

        if (p_rect.size.y != -1)
        {
            destRect.h = p_rect.size.y;
        }

        SDL_RenderCopyEx(m_renderer, tex, nullptr, &destRect, 0, nullptr, SDL_FLIP_NONE);
    }

    void clear()
    {
        assert(m_renderer);

        SDL_RenderClear(m_renderer);
    }

    void present()
    {
        assert(m_renderer);

        SDL_RenderPresent(m_renderer);
    }

private:
    SDL_Window*   m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    std::vector<SDL_Texture*>         m_textures;
    std::vector<std::uint16_t>        m_generations;
    std::unordered_set<std::uint16_t> m_freeIDs;
};

RenderingBackend::RenderingBackend()
    : m_impl(std::make_unique<impl>())
{}

RenderingBackend::~RenderingBackend()
{}

bool RenderingBackend::initialize(std::string_view p_windowName, const Vec2i& p_windowSize)
{
    return m_impl->initialize(p_windowName, p_windowSize);
}

Texture RenderingBackend::createTexture(const Bitmap& p_bitmap)
{
    return m_impl->createTexture(p_bitmap);
}

void RenderingBackend::destroyTexture(Texture p_texture)
{
    m_impl->destroyTexture(p_texture);
}

void RenderingBackend::draw(Texture p_texture, const Rect& p_rect)
{
    m_impl->draw(p_texture, p_rect);
}

void tg::RenderingBackend::clear()
{
    m_impl->clear();
}

void tg::RenderingBackend::present()
{
    m_impl->present();
}
