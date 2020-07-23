#pragma once

#include <graphics/bitmap.h>
#include <math/rect.h>
#include <rendering/texture.h>

#include <cstdint>
#include <memory>
#include <string_view>

namespace tg
{
    class RenderingBackend
    {
    public:
        RenderingBackend();
        ~RenderingBackend();

        bool initialize(std::string_view p_windowName, const Vec2i& p_windowSize);

        Texture createTexture(const Bitmap& p_bitmap);
        void    destroyTexture(Texture p_texture);

        void draw(Texture p_texture, const Rect& p_rect);

        void clear();
        void present();

    private:
        class impl;
        std::unique_ptr<impl> m_impl;
    };
}
