#pragma once

#include <math/rect.h>
#include <math/vec2.h>
#include <rendering/camera.h>
#include <rendering/rendering_backend.h>
#include <rendering/texture.h>

#include <cstdint>

namespace tg
{
    class Canvas
    {
    public:
        Canvas(RenderingBackend& p_backend)
            : m_backend(p_backend)
            , m_camera(nullptr)
        {}

        void draw(Texture p_tex, const Vec2i& p_position);
        void draw(Texture p_tex, const Rect& p_rect);

        void setCamera(Camera* p_camera) { m_camera = p_camera; }

        void begin();
        void end();

    private:
        RenderingBackend& m_backend;

        Camera* m_camera;
    };
}
